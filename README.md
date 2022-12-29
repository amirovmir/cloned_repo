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
- Нахождение контрастных стикеров                                                             - реализовано (выделение констрастных меток)
- Определение 2D коодинат стикеров                                                            - реализовано (гомография)
- Ввод маршрута                                                                               - не реализовано
- Формирование команд управления для езды Alphabot по маршруту                                - не реализовано
- Передача команд от сервера управления на Alphabot по tcp                                    - не реализовано

### Программа управления Alphabot для Raspbery PI 4
#### [https://github.com/amirovmir/practice/tree/main/2022/gpio_output](https://github.com/amirovmir/practice/tree/main/2022/gpio_output)
#### Используется
- KasperskyOS
- C++

#### Функции программы
- Выдача команд управления (вперед, назад, стоп, влево, вправо) на моторы Alphabot            - реализовано
- Проезда по заданному маршруту (прямоугольник)                                               - реализовано
- Прием команд по сети                                                                        - не реализовано

### Финальные испытания
- Проезд по заданному фиксированному маршруту (прямоугольник)             - выполнено
- Проеезд по маршруту по командам от сервера распознавания                - не выполнено

### Quick Access
.
├──[2022]()
|   ├──[gpio_output](https://github.com/amirovmir/practice/tree/main/2022/gpio_output)
|   |   ├──[client](https://github.com/amirovmir/practice/tree/main/2022/gpio_output/client)
|   |   └──[einit](https://github.com/amirovmir/practice/tree/main/2022/gpio_output/einit)
|   |
|   ├──[OpenCV](https://github.com/amirovmir/practice/tree/main/2022/opencv)
|   |   └──[code](https://github.com/amirovmir/practice/tree/main/2022/opencv/code)
|   |
|   ├──[tcpserver](https://github.com/amirovmir/practice/tree/main/2022/tcpserver)
|   |   ├──[linux_client](https://github.com/amirovmir/practice/tree/main/2022/tcpserver/linux_client)
|   |   └──[net_server](https://github.com/amirovmir/practice/tree/main/2022/tcpserver/net_server)
|   |
|   ├──[read_from_file](https://github.com/amirovmir/practice/tree/main/2022/read_from_file)
|   |   ├──[einit](https://github.com/amirovmir/practice/tree/main/2022/read_from_file/einit)
|   |   ├──[vfs_user](https://github.com/amirovmir/practice/tree/main/2022/read_from_file/vfs_user)
|   |   ├──[read_manager](https://github.com/amirovmir/practice/tree/main/2022/read_from_file/read_manager)
|   |   └──[common](https://github.com/amirovmir/practice/tree/main/2022/read_from_file/common)
|   |
|   ├──[separate_storage](https://github.com/amirovmir/practice/tree/main/2022/separate_storage)
|   |   ├──[einit](https://github.com/amirovmir/practice/tree/main/2022/separate_storage/einit)
|   |   ├──[vfs_user](https://github.com/amirovmir/practice/tree/main/2022/separate_storage/vfs_user)
|   |   ├──[user_manager](https://github.com/amirovmir/practice/tree/main/2022/separate_storage/user_manager)
|   |   ├──[common](https://github.com/amirovmir/practice/tree/main/2022/separate_storage/common)
|   |   └──[resources](https://github.com/amirovmir/practice/tree/main/2022/separate_storage/resources)
|   |   
|   └──[env_entity](https://github.com/amirovmir/practice/tree/main/2022/env_entity)
|       ├──[einit](https://github.com/amirovmir/practice/tree/main/2022/env_entity/einit)
|       ├──[env](https://github.com/amirovmir/practice/tree/main/2022/env_entity/env)
|       ├──[hello](https://github.com/amirovmir/practice/tree/main/2022/env_entity/hello)
|       └──resources
|           └──[edl](https://github.com/amirovmir/practice/tree/main/2022/env_entity/resources/edl)
|
├──[LICENSE](https://github.com/amirovmir/practice/blob/main/LICENSE)
└──README.md
