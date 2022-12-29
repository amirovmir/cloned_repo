# KasperskyOS Hackaton 2022

## Система управления роботом на основе KasperskyOS с помощью камеры

### В рамках летнего хакатона от Kaspersky был создан прототип решения удаленного управления IoT устройством на KasperskyOS через TCP соединение
### Задачи:
- Реализовать удаленное соединение робота с управляющей программой по TCP протоколу в одной локальной среде 
- Реализовать функционал с управлением двигателем через порты GPIO 
- Реализовать функционал распознавания робота и его целей 
- Создать алгоритм управления роботом через внешнюю камеру 

## Реализация
### Программа распознавания
#### [https://github.com/amirovmir/practice/tree/main/2022/opencv](https://github.com/amirovmir/practice/tree/main/2022/opencv)
#### Используется:
- Linux
- C++
- OpenCV

#### Функции программы
    - Нахождение контрастных стикеров                                       - реализовано (выделение констрастных меток)
    - Определение 2D коодинат стикеров                                      - реализовано (гомография)
    - Ввод маршрута                                                         - не реализовано
    - Формирование команд управления для езды Alphabot по маршруту          - не реализовано
    - Передача команд от сервера управления на Alphabot по tcp              - не реализовано

### Программа управления Alphabot для Raspbery PI 4
#### [https://github.com/amirovmir/practice/tree/main/2022/gpio_output](https://github.com/amirovmir/practice/tree/main/2022/gpio_output)
#### Используется
- KasperskyOS
- C++

#### Функции программы
    - Выдача команд управления (вперед, назад, стоп, влево, вправо) на моторы Alphabot   - реализовано
    - Проезда по заданному маршруту (прямоугольник)                                      - реализовано
    - Прием команд по сети                                                               - не реализовано

### Финальные испытания
    - Проезд по заданному фиксированному маршруту (прямоугольник)    - выполнено
    - Проезд по маршруту по командам от сервера распознавания       - не выполнено

### Quick Access
    .
    ├──2022
    |   ├──gpio_output
    |   |   ├──client
    |   |   └──einit
    |   |
    |   ├──OpenCV
    |   |   └──code
    |   |
    |   ├──tcpserver
    |   |   ├──linux_client
    |   |   └──net_server
    |   |
    |   ├──read_from_file
    |   |   ├──einit
    |   |   ├──vfs_user
    |   |   ├──read_manager
    |   |   └──common
    |   |
    |   ├──separate_storage
    |   |   ├──einit
    |   |   ├──vfs_user
    |   |   ├──user_manager
    |   |   ├──common
    |   |   └──resources
    |   |   
    |   └──env_entity
    |       ├──einit
    |       ├──env
    |       ├──hello
    |       └──resources
    |           └──edl
    |
    ├──LICENSE
    └──README.md

© amirovmir, Kachanay-Boshka, Moscow Aviation Institute feat. Kaspersky Lab  
Moscow, 2022