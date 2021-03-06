# Информация для участников проекта

Тут представлены правила и рекомендации для разработчиков, тестировщиков и дизайнеров.

## Содержание
1. [**Для разработчиков**](https://github.com/timattt/Project-Cognitia-II/blob/main/About/forContributors.md#%D0%B4%D0%BB%D1%8F-%D1%80%D0%B0%D0%B7%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%87%D0%B8%D0%BA%D0%BE%D0%B2)
* [Система логирования](https://github.com/timattt/Project-Cognitia-II/blob/main/About/forContributors.md#%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%B0-%D0%BB%D0%BE%D0%B3%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F)
* [Правила написания кода](https://github.com/timattt/Project-Cognitia-II/blob/main/About/forContributors.md#%D0%BF%D1%80%D0%B0%D0%B2%D0%B8%D0%BB%D0%B0-%D0%BD%D0%B0%D0%BF%D0%B8%D1%81%D0%B0%D0%BD%D0%B8%D1%8F-%D0%BA%D0%BE%D0%B4%D0%B0)
2. [**Для тех, кто делает pullrequest**](https://github.com/timattt/Project-Cognitia-II/blob/main/About/forContributors.md#%D0%B4%D0%BB%D1%8F-%D1%82%D0%B5%D1%85-%D0%BA%D1%82%D0%BE-%D0%B4%D0%B5%D0%BB%D0%B0%D0%B5%D1%82-pullrequest)
3. [**Для тестировщиков**](https://github.com/timattt/Project-Cognitia-II/blob/main/About/forContributors.md#%D0%B4%D0%BB%D1%8F-%D1%82%D0%B5%D1%81%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D1%89%D0%B8%D0%BA%D0%BE%D0%B2)

## Для разработчиков

### Система логирования

Для всех информационных сообщений сделана система логирования. Подключайте файл **logger.h** из папки **Core** и используйте:

* **ASSERT(COND)** - Остановит программу, напишет в консоль и лог, если условие не выполняется.
* **NOT_NULL(P)** - Остановит программу, напишет в консоль и лог, если указатель нулевой.
* **SAY(MES)** - Выводит вообщение в консоль и влог.
* **ASSERTM(COND, MES)** - Остановит программу и напишет заданное сообщение в консоль и лог, если условие не выполняется. 

### Правила написания кода

Требуется придерживаться следующих правил:

1. В любых функциях писать **NOT_NULL(P)** для всех параметров-указателей.

```
void doSomething(int * a, SomeClass * b) {
  NOT_NULL(a != nullptr);
  NOT_NULL(b != nullptr);
}
```

2. Для всех классов во всех их конструкторах **всегда** инициализировать все поля.

```
class A {
  int * ptr;
  
  A() : ptr(nullptr) {
    
  }
};
```

3. Для каждой функции писать документацию в формате:
```
/**
Описание вашей функции
@param arg1 - описание параметра 1
@param argN - описание параметра N
@return - описание возвращаемого значения
@author - имя автора, который создал эту функцию
*/
```
Документацию писать перед прототипом функции.

4. Если код зависит от выполнения какого-нибудь условия, и при невыполнении этого условия может теоретически падать, то нужно ставить **ASSERT** или **ASSERTM**.
Другими словами - чем больше ассертов, тем лучше.

5. В декларации класса - секции полей, приватных функций, приватных полей, публичных полей и т.д. должны быть разделены палками.

```
class B {
private:

  // private fields
  //===================
  int a;
  int b;
  //===================
  
public:
  
  // public functions
  //===================
  void foo();
  void hey();
  //===================
  
};
```

6. Для каждого класса писать документацию в формате:

```
/**
Подробное описание вашего класса
@author - имя создателя класса
*/
class A {
  ...
};
```

7. Для вывода информации использовать только встроенную систему логирования.

8. Описание коммитов оформлять так: 

```
SEGMENT_NAME | ACTION_TYPE | DESCRIPTION
1. action 1 description
2. action 2 description
...
n. action n description
```

где SEGMENT_NAME - имя gui, куда делались изменения.
    ACTION_TYPE - тип изменений: Fix, Feature, Refactoring.
    DESCRIPTION - общее описание. 
    Далее идут отдельные опписания всех изменений.

9. Все задачи и все свои действия отображать в **issue**

## Для тех, кто делает pullrequest

1. Писать подробное описание **pullrequest**
2. Для каждого **pullrequest** ставить метку (label)
3. Указывать человека, который должен сделать **code-review** (reviewer)

## Для тестировщиков

Правила для тестирования.

1. Для каждого замечания создавать отдельный **issue**
2. Для каждого **issue** ставить label (метку)


