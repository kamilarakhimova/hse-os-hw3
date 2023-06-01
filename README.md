# hse-os-hw3
---
# ИДЗ №3 по предмету "Операционнные системы"

# Курс 2, ПИ, ФКН, НИУ ВШЭ

# Вариант 14, Рахимова Камила Мухаммадовна, БПИ214

---

## *Условие задачи:*

Задача о гостинице – 3 (дамы и джентльмены). В гостинице 10 номеров рассчитаны на одного человека и 15 номеров рассчитаны на двух человек. В гостиницу случайно приходят клиенты–дамы и клиенты–джентльмены, и конечно они могут провести ночь в номере только с представителем своего пола. Если для клиента не находится подходящего номера, он уходит искать ночлег в другое место. Клиенты порождаются динамически и уничтожаются при освобождении номера или уходе из гостиницы при невозможности поселиться. Создать приложение, моделирующее работу гостиницы.

Гостиница — сервер. Каждого гостя реализовать в виде отдельного клиента, порождаемого вручную. Можно запустить скрипт, порождающий сразу множество гостей в фоновом режиме.

---

## *Сценарий решаемой задачи:*

Собственно сценарий уже описан в условии. Гостиница является сервером, а клиенты -- клиентами. Так как условие может быть интерпретировано на собственное усмотрение, для упрощения я решила работать только с n клиентами (количество n задаётся в программе "server.c"), создаваемыми вручную.

---

## *Примечания:*

✔️ Программа с момента запуска и до завершения работы моделирует одну ночь работы отеля. Соответственно клиенты уничтожаются с рассветом (по окончании работы программы).

✔️ В данном варианте нет необходимости в наборе тестовых файлов для понимания работы программы. Результатом моделирования работы гостиницы является описание результатов действий сервера, выводимое программой.

---

## *Отчёт*

Работа выполнена с расчётом на получение оценки в 10/10 баллов (но пока реализовала только на 4-5, решение ещё в процессе).

### ◉ Требования на 4-5 баллов:

Сами программы расположились [здесь](https://github.com/kamilarakhimova/hse-os-hw3/tree/main/4-5%20баллов).

✔ Задача:

Разработать клиент–серверное приложение, в котором сервер и клиенты независимо друг от друга отображают только ту информацию, которая поступает им во время обмена. То есть, отсутствует какой-либо общий вывод интегрированной информации, отображающий поведение системы в целом.

✔ Примечания:

Количество клиентов-гостей, желающих заселиться в отель задаётся переменной "MAX_CLIENTS" в программе "server.c":

```
#define MAX_CLIENTS 2
```

✔ Запускаем работу сервера:

```
~/os-mini-hw1$ gcc -o server server.c
~/os-mini-hw1$ ./server <server_port>
```

✔ Запускаем работу клиента столько раз, сколько у нас клиентов (в моём примере их 2):
```
~/os-mini-hw1$ gcc -o client client.c
~/os-mini-hw1$ ./client <server_ip_address> <server_port>
```


✔ Результат выполнения программы сервера:

```
server ip address = <server_ip_address>
Добро пожаловать на ночную экскурсию в отель.
Вы задали количество клиентов, ожидающих заселения, равным: 2.
Администратор (сервер) готов заселять клиентов.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 3.
Клиентка-дама заселилась в одноместный номер 3.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 6.
Клиент-джентльмен заселился в одноместный номер 6.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы клиента 1:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: женский.
Клиент отошёл от стойки регистрации.
```

✔ Результат выполнения программы клиента 2:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: мужской.
Клиент отошёл от стойки регистрации.
```

### ◉ Требования на 6-7 баллов:

Требования, совпадающие с требованиями на более низкую оценку, остались выполненными и в [этой](https://github.com/kamilarakhimova/hse-os-hw2/tree/main/6%20баллов/main.c) программе.

✔ Выбранная схема решения:

Множество процессов взаимодействуют с использованием семафоров в стандарте UNIX SYSTEM V. Обмен данными ведется через разделяемую память в стандарте UNIX SYSTEM V.

✔ Запускаем программу:

```
~/os-mini-hw1$ gcc -pthread main.c -o main
~/os-mini-hw1$ ./main 50
```

✔ Результат работы программы можно увидеть [тут](https://github.com/kamilarakhimova/hse-os-hw2/tree/main/6%20баллов/result).

### ◉ Требования на 7 баллов:

Требования, совпадающие с требованиями на более низкую оценку, остались выполненными и в [этих](https://github.com/kamilarakhimova/hse-os-hw2/tree/main/7%20баллов/program1.c) [программах](https://github.com/kamilarakhimova/hse-os-hw2/tree/main/7%20баллов/program2.c).

✔ Выбранная схема решения:

Множество независимых процессов взаимодействуют с использованием именованных POSIX семафоров. Обмен данными ведется через разделяемую память в стандарте POSIX.

✔ Запускаем программу:

```
~/os-mini-hw1$ gcc -pthread program1.c -o program1
~/os-mini-hw1$ gcc -pthread program2.c -o program2
~/os-mini-hw1$ ./program1 50 & ./program2
```

✔ Результат работы программы можно увидеть [тут](https://github.com/kamilarakhimova/hse-os-hw2/tree/main/7%20баллов/result).
