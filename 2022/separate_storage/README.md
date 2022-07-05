### Последовательность комманд для запуска
- git clone
- cd separate_storage
- sudo docker build -t getting-started .
- sudo docker run -it -v ~/separate_storage:/workspace --device /dev/net/tun:/dev/net/tun --privileged --rm getting-started bash
- ./cross-build.sh

### Результат
[KasperskyOS Community Edition](https://os.kaspersky.com/development/download/)