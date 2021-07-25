# Cognitia II
В этом репозитории находится вторая версия программы для оптимизации процесса обучения студентов, а также планирования курсов.

# Концепция
Рассмотрим несколько старых картинок из незаконченного аналогичного проекта.   
![](https://github.com/timattt/Project-Cognitia-II/blob/main/About/old/0.png)

![](https://github.com/timattt/Project-Cognitia-II/blob/main/About/old/1.png)

![](https://github.com/timattt/Project-Cognitia-II/blob/main/About/old/2.png)

## Структуры
Введем несколько структур для хранения данных, сохранения и загрузки данных.

### SkillPack
Это набор навыков, которыми студент может обзавестись в процессе обучения. Причем каждым навыком можно владеть на определенном уровне. 
Какое знание навыка какому уровню соответствует определяет описание уровня. Формально это выглядит так:

![](https://github.com/timattt/Project-Cognitia-II/blob/main/About/SkillPack.png)

Пусть мы рассматриваем некий навык **S**. Тогда у него есть множество уровней. Причем существует число **N** - максимальный уровень.
Тогда будем выполнять, что:
1. Для каждого навыка у каждого студента будет число **K**, которое будет отображать текущий прогресс студента в данном навыке. Причем **0 <= K <= N**
2. Если имеем некий уровень **L**. Тогда **K >= L** в том и только в том случае, если выполняются условия из описания уровня

### CourseUnit
Это единица курса. Представляет собой задачу, которую нужно выполнить. Существуют два набора навыков: входные навыки - то, что необходимо знать, чтобы приступить к работе; выходные навыки - максимальные навыки, которые может получить студент после решения задачи.

![](https://github.com/timattt/Project-Cognitia-II/blob/main/About/CourseUnit.jpg)

На выходные навыки накладываются некие ограничения:   
Пусть **S** - выходной навык, **L** - его уровень, тогда:
1. Если существует входной навык **S'** с уровнем **L'**, такой что **S' = S**. Тогда необходимо, чтобы **L' + 1 = L**
2. Если не существует входного навыка **S'**, такого что **S' = S**. Тогда необходимо, чтобы **L = 1**

Единицы курса образовывают ориентированный ациклический граф курса, играя роль вершин.   
Причем для корректного построения графа необходимо следующее:      
Для любой единицы курса **U** с **входными** скилами и их уровнями **{Si, Li}** существует набор **входных** ребер, которые связаны с другими вершинами **{Vj}**.
У каждой вершины **Vj** есть набор **выходных** скилов и их уровней **{Sjk, Ljk}**.   
Тогда для любого **входного** скила **{Si, Li}** существует **j** и **k**, такое что **Si = Sjk** и **Li = Ljk**.   

Единицу курса можно помечать меткой.   
Виды меток:
* Начало графа - множество входных навыков пусто (в графе такая метка ровно одна)
* Конец графа - отсутсвуют выходные ребра (в графе такая метка ровно одна)
* Бонус - данная единица курса не является основной, а является дополнительной   

Каждая единица курса может содержать граф других единиц курса. Такая рекурсия может продолжаться до бесконечности.
Причем входные скилы совпадают с входными скилами внутренней вершины с меткой **Начало графа**, а выходные скилы совпадают с выходными скилами вершины с меткой **Конец графа**.
Более того, весь курс, с которым будет работать пользователь будет **корневой** единицей курса, которая содержит в себе основной граф курса.

![](https://github.com/timattt/Project-Cognitia-II/blob/main/About/CourseUnitRecursion.jpg)

### StudentProgress
Эта структура индивидуальна для каждого студента. Она жестко привзяна к заданному SkillPack и CourseUnitGraph.   
Она содержит:
* для каждого скила действительное число K - навык студента в данном скиле. Если максимальный уровень данного скила - N, то 0 <= K <= N, причем число [K] - текущий уровень студента в данном скиле
* Данные о бонусных единицах курса, которые ментор может добавлять по своему желанию. По сути это просто дополнительные произволные единицы курса, но они могут быть уникальны для каждого студента


## Процесс работы системы
Опираясь на заданнные структуры данных, поймем, как будет происходить процесс взаимодействия с программой. Пользователями выступают методист, менторы и студенты.

![](https://github.com/timattt/Project-Cognitia-II/blob/main/About/WorkProcess.jpg)

Здесь зеленая линия - чтение из облака, красная линия - запись в облако. Вершины обозначают действия пользователей. Кроме синей жирной - она обозначает облачное хранилище.
Под вершиной написано, кто выполняет данное действие.













