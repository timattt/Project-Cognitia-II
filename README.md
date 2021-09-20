# РИДМИ В ПРОЦЕССЕ РЕФАКТОРИНГА!!! НЕ ЧИТАТЬ!!! ОПАСНО ДЛЯ ЖИЗНИ!!! НЕ ВЛЕЗАЙ - УБЬЕТ!!! НО ЕСЛИ ОЧЕНЬ ХОЧЕТСЯ - СМОТРИТЕ ОПИСАНИЕ ТЗ ПРОТОТИПА!!! ОНО В САМОМ НИЗУ!!! 

# Cognitia II

Программа предназначена для оптимизации учебного процесса.
Итак, у нас есть три возможных пользователя: методист, ментор, студент.
**Перечислим их:**

* Методист - отвечает за организацию учебного процесса.
* Ментор - преподаватель, который проверяет задания студентов, а также работает с каждым студентом индивидуально.
* Студент - человек, который хочет получить новые знания быстро, эффективно и интересно.

**Процесс обучения обычно выглядит так:**

1. Методист создает учебный курс
2. Лектор читает лекции по теме.
3. Студенты выполняют задания.
4. Менторы проверяют задания студентов, критикуют, выставляют оценки.

Идея в том, чтобы оптимизировать вышеперечисленное. Какая конечная цель образования? Чтобы студент был компетентен в соответсвующей области. Поэтому задача - правильно собирать информацию о навыках студентов в процессе обучения. Вот прослушали вы лекцию, решили задачу - стали в чем-то умнее, а в чем именно - вот вопрос. 
Начнем с действий методиста.

![](https://github.com/timattt/Project-Cognitia-II/blob/main/About/Logo.png)

## Prototype

Риализован прототип программы.
Техническое задание и описание можно найти [тут](https://github.com/timattt/Project-Cognitia-II/blob/main/About/PrototypeTechnicalTask/PrototypeTechnicalTask.md)

# Установка
Исполняемые файлы можно найти [тут](https://github.com/timattt/Project-Cognitia-II/releases).

# Сборка
## QT Creator
1. Устанавливаем **git** [отсюда](https://git-scm.com/).
2. Устанавливаем **Qt** [отсюда](https://www.qt.io/).
3. Клонируем репозиторий, переходим в папку с ним и далее в папку Sources.
4. Открываем файл Cognitia-II.pro.
5. Собрать и запустить теперь можно с помощью **QT Creator**.

## MinGW
1. Устанавливаем **git** [отсюда](https://git-scm.com/).
2. Устанавливаем **Qt** [отсюда](https://www.qt.io/).
3. Теперь идем в папку, куда установился QT, добавляем 3 папки bin в PATH.
4. Клонируем репозиторий, переходим в папку с ним и далее в папку Sources.
5. Открываем терминал из этой папки и используем следующие команды:
 ```
mkdir build
cd build
qmake ..
mingw32-make.exe all
```
6. Теперь в папке build есть исполняемые файлы.
