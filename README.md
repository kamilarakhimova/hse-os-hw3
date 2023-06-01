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

Администратор (сервер) после запуска ожидает клиентов.
Клиенты подключаются поочередно, передают данные о своём поле (женский/мужской) и о виде желаемого номера (одноместный/двухместный).
Администратор (сервер) получает данные от клиента и обрабатывает запрос. Далее рандомно берет ключ от номера желаемого вида. И, если клиент подходит под условия для проживания в этой комнате, заселяет его. Иначе сообщает по какой причине не может заселить клиента.

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
Администратор (сервер) заселяет клиента в комнату 2.
Клиентка-дама заселилась в одноместный номер 2.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 11.
Клиентка-дама заселилась первой в двухместный номер 11.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы клиента 1:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: женский.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

✔ Результат выполнения программы клиента 2:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: женский.
Клиент хочет заселиться в двухместный номер.
Клиент отошёл от стойки регистрации.
```

### ◉ Требования на 6-7 баллов:

Сами программы расположились [тут](https://github.com/kamilarakhimova/hse-os-hw3/tree/main/6-7%20баллов).

✔ Задача:

В дополнение к программе на предыдущую оценку необходимо разработать клиентскую программу, подключаемую к серверу, которая предназначена для отображение комплексной информации о выполнении приложения в целом. То есть, данный программный модуль должен адекватно отображать поведение моделируемой системы, позволяя не пользоваться отдельными видами, предоставляемыми клиентами и серверами по отдельности.

✔ Примечания:

Количество клиентов-гостей, желающих заселиться в отель всё также задаётся переменной "MAX_CLIENTS" в программе "server.c":

```
#define MAX_CLIENTS 2
```

Количество клиентов-наблюдателей определяется переменной "MAX_OBSERVERS" в программе "server.c". В требованиях на данную оценку оно обязательно равно 1.

```
#define MAX_OBSERVERS 1
```

✔ Запускаем работу сервера:

```
~/os-mini-hw1$ gcc -o server server.c
~/os-mini-hw1$ ./server <server_port>
```

✔ Запускаем работу наблюдателя:

```
~/os-mini-hw1$ gcc -o observer observer.c
~/os-mini-hw1$ ./observer <server_ip_address> <server_port>
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
Вы задали количество наблюдателей равным: 1.
Администратор (сервер) готов заселять клиентов.
К администратору (серверу) подключился наблюдатель 1.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 5.
Клиент-джентльмен заселился в одноместный номер 5.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 9.
Клиент-джентльмен заселился в одноместный номер 9.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы наблюдателя (1):

```
Успешно установлено подключение наблюдателя к серверу.
К администратору (серверу) подключился наблюдатель 1.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 5.
Клиент-джентльмен заселился в одноместный номер 5.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 9.
Клиент-джентльмен заселился в одноместный номер 9.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы клиента 1:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: мужской.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

✔ Результат выполнения программы клиента 2:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: мужской.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

### ◉ Требования на 8 баллов:

Сами программы расположились [здесь](https://github.com/kamilarakhimova/hse-os-hw3/tree/main/8%20баллов).

✔ Задача:

В дополнение к предыдущей программе реализовать возможность, подключения множества клиентов, обеспечивающих отображение информации о работе приложения. Это должно позволить осуществлять наблюдение за поведением программы с многих независимых компьютеров.

✔ Примечания:

Количество клиентов-гостей, желающих заселиться в отель всё также задаётся переменной "MAX_CLIENTS" в программе "server.c":

```
#define MAX_CLIENTS 2
```

Количество клиентов-наблюдателей определяется переменной "MAX_OBSERVERS" в программе "server.c". В требованиях на данную оценку оно обязательно равно 1.

```
#define MAX_OBSERVERS 1
```

✔ Запускаем работу сервера:

```
~/os-mini-hw1$ gcc -o server server.c
~/os-mini-hw1$ ./server <server_port>
```

✔ Запускаем работу наблюдателя:

```
~/os-mini-hw1$ gcc -o observer observer.c
~/os-mini-hw1$ ./observer <server_ip_address> <server_port>
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
Вы задали количество наблюдателей равным: 1.
Администратор (сервер) готов заселять клиентов.
К администратору (серверу) подключился наблюдатель 1.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 5.
Клиент-джентльмен заселился в одноместный номер 5.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 9.
Клиент-джентльмен заселился в одноместный номер 9.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы наблюдателя (1):

```
Успешно установлено подключение наблюдателя к серверу.
К администратору (серверу) подключился наблюдатель 1.
Администратор (сервер) обрабатывает клиента 1.
Администратор (сервер) заселяет клиента в комнату 5.
Клиент-джентльмен заселился в одноместный номер 5.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 9.
Клиент-джентльмен заселился в одноместный номер 9.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы клиента 1:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: мужской.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

✔ Результат выполнения программы клиента 2:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: мужской.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

### ◉ Требования на 9-10 баллов:

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
Администратор (сервер) заселяет клиента в комнату 2.
Клиентка-дама заселилась в одноместный номер 2.
Администратор (сервер) обрабатывает клиента 2.
Администратор (сервер) заселяет клиента в комнату 11.
Клиентка-дама заселилась первой в двухместный номер 11.
А вот и рассвет, экскурсия окончена. Всё, конец!
```

✔ Результат выполнения программы клиента 1:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: женский.
Клиент хочет заселиться в одноместный номер.
Клиент отошёл от стойки регистрации.
```

✔ Результат выполнения программы клиента 2:

```
Клиент подошёл к администратору (серверу) оформляться на заселение!
Пол клиента: женский.
Клиент хочет заселиться в двухместный номер.
Клиент отошёл от стойки регистрации.
```
