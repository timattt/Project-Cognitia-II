#include "studentclient.h"
#include "ui_studentclient.h"

StudentClient::StudentClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentClient)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);
    chooseserv = new ChooseServ(this);
    skillpack = new SkillPack(this);
    courseUnit = new CourseUnit(this);
    connect(mSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(mSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(mSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), SLOT(slotError(QAbstractSocket::SocketError)));
    connect(chooseserv, SIGNAL(onServConnectclicked()), SLOT(startConnection()));
    connect(chooseserv, SIGNAL(chooseServClosed()), SLOT(onChooseServClosed()));
    connect(ui->courseUnitViewer, SIGNAL(nodeSelected(Node*)), ui->flower, SLOT(unpack(Node*)));
    connect(ui->flower, SIGNAL(skillLevelChanged(QString, double)), ui->courseUnitViewer, SLOT(makeProgressToSelected(QString, double)));

    ui->flower->setEditable(false);
    ui->courseUnitViewer->setEditable(false);
}

StudentClient::~StudentClient()
{
    delete ui;
}

void StudentClient::on_actionChange_Server_triggered()
{
    ui->statusbar->showMessage("Changing server");
    if (inworkingrepository){
        QDir::setCurrent("../");
        inworkingrepository = false;
    }
    this -> setEnabled(false);
    chooseserv -> setEnabled(true);
    chooseserv -> show();
}


void StudentClient::onChooseServClosed(){
    this -> setEnabled(true);
    ui->statusbar->showMessage("Server isnt connected, Please connect to the server");
}



void StudentClient::onStart(){
    this -> setEnabled(false);
    chooseserv -> setEnabled(true);
    chooseserv -> show();
    this -> show();
    ui->statusbar->showMessage("Server isnt connected");
}

void StudentClient::startConnection(){
    QString IP = chooseserv -> getIP();
    unsigned Port = (chooseserv -> getPort()).toUInt();

    if(mSocket -> state() == QAbstractSocket::ConnectedState){
        mSocket -> close();
    }
    mSocket -> connectToHost(IP, Port);

}

void StudentClient::slotConnected(){

    qDebug() << "connected to serv";
    StudentName = chooseserv -> getName();

    QDir dir = QDir();
    if (!inworkingrepository)
    {
        dir.mkdir(StudentName + chooseserv -> getIP());
        QDir::setCurrent(StudentName + chooseserv -> getIP());
        inworkingrepository = true;
        this -> sendToServer(static_cast<quint16>(getUserName), "");
    }



}

void StudentClient::slotError(QAbstractSocket::SocketError error){
    QString strEr = "Error: " +
            (error == QAbstractSocket::HostNotFoundError ?
                 "The host was not found" :
                 error == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed" :
                     error == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused" :
                         QString(mSocket -> errorString()));

    QMessageBox::critical(this, "Failing", strEr);
    mSocket -> close();
}

void StudentClient::slotReadyRead(){
    QDataStream in(mSocket);

    for(;;){
        if(!nextBlockSize){
            if(mSocket -> bytesAvailable() < sizeof(quint32))
                break;
            in >> nextBlockSize;
        }

        if(mSocket -> bytesAvailable() < nextBlockSize)
            break;

        qDebug() << "nextblock size " << nextBlockSize;
        qDebug() << "bytes available " << mSocket -> bytesAvailable();
        datafromServer = mSocket -> read(nextBlockSize);
        qDebug() << "receiving " << datafromServer;
        endReception();
        nextBlockSize = 0;
    }
}



void StudentClient::handleincFile(QDataStream& in){

     QString filename;
     in >> filename;
     qDebug() << "handling file" << filename ;
     QFile file(filename);

     if (file.open(QIODevice::WriteOnly)){
         QTextStream out(&file);
         QByteArray filecont;
         in >> filecont;
         qDebug() << filecont;
         out << filecont;
         file.write(in.device()->readAll());
     }
     else
     {
         qDebug() << "Cant handle inc file " << filename ;
     }

}



void StudentClient::endReception(){

    QDataStream in(datafromServer);
    in >> respCode;

    switch (respCode) {
    case retrieveCourseUnit:
    case retrieveSkillpack:
    case retrieveStudentProgress:
        handleincFile(in);
        break;
    case retrieveFailAutorisation:
    case firstConnectionSuccess:
        qDebug() << "confirm connection";
        confirmConnection();
        break;
    case retrieveFail:
        QMessageBox::critical(this, "Failing", "Last operation wasnt complited");
        break;
    default:
        qDebug() << "cant understand the code";
        break;
    }

}


void StudentClient::confirmConnection(){
    if (respCode == retrieveFailAutorisation){
        QMessageBox::critical(this, "Failing", "Wrong Name");
        mSocket -> close();
        QDir::setCurrent("../");
        QDir dir = QDir();
        dir.rmdir(StudentName + chooseserv -> getIP());
        inworkingrepository = false;
        return;
    }

    chooseserv -> hide();
    this -> setEnabled(true);
    ui -> StudentName -> setText(chooseserv -> getName());

    OpenCourse();
}



void StudentClient::LoadCourse(){
    QDir curdir = QDir();
    QStringList filters;
    filters << "*.mainCourseUnit";
    curdir.setNameFilters(filters);

    QFile fileMain( curdir.entryList()[0]);


    if (fileMain.open(QIODevice::ReadOnly)){

        QString filename(fileMain.readAll());

        QFile course(filename);
        try {
            courseUnit -> loadCourseUnit(&course);
        }
        catch (QString message){
            qDebug() << message;
        }
    } else {
        qDebug() << "cant open course main file";
    }

}


void StudentClient::LoadSkillpack(){
    QDir curdir = QDir();
    QFile pack(curdir.entryList(QStringList() << "*.cognitiaSkillPack")[0]);
    try {
        skillpack -> load(&pack);
    }
    catch(QString message){
        qDebug() << message;
    }
}


void StudentClient::LoadStudentsProgresses(){
    QDir curdir = QDir();

    QFile prog(curdir.entryList(QStringList() << "*.StudentProgress")[0]);
    try {
        progress -> load(&prog);
    }
    catch(QString message){
        qDebug() << message;
    }
}


void StudentClient::OpenCourse(){

    LoadCourse();
    LoadSkillpack();
    LoadStudentsProgresses();

    display();

}


void StudentClient::display(){
	ui->courseUnitViewer->clearAllScene();
	if (!courseUnit) {
		qInfo() << "Course unit is null!";
	} else {
		ui->courseUnitViewer->unpack(courseUnit);
	}
	if (!progress) {
		qInfo() << "Student progress is null!";
	} else {
		ui->courseUnitViewer->unpack(progress);
    }
}

void StudentClient::sendToServer(quint16 code, const QString& str){

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    out << quint32(0) << StudentName << code << str;
    out.device()->seek(0);
    out << quint32(arrBlock.size() - sizeof(quint32));

    mSocket -> write(arrBlock);
    qDebug() << "sendind to server " << arrBlock;
}


void StudentClient::on_actionSave_all_and_send_triggered()
{
     if(!inworkingrepository){
         ui->statusbar->showMessage("Please, connect to server");
         return;
     }

     ui->statusbar->showMessage("Save");
}




void StudentClient::on_actionReturn_to_Launcher_triggered()
{
    emit onClose();
}

