QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Launcher/launcher.cpp \
    Core/main.cpp \
    SkillPackEditor/skillpackeditor.cpp \
    Structures/SkillPack/skill.cpp \
    Structures/SkillPack/skillpack.cpp

HEADERS += \
    Launcher/launcher.h \
    SkillPackEditor/skillpackeditor.h \
    Structures/SkillPack/skill.h \
    Structures/SkillPack/skillpack.h

FORMS += \
    Launcher/launcher.ui \
    SkillPackEditor/skillpackeditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Resources/Resources.qrc