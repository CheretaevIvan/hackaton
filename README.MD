# Установка системы обнаружения объекта на пути приоритетного объекта

1. Первым делом подключаем Edison Compute Module к Edison Arduino board. Затем подключаем плату расширения Grove Basic Shield к Edison Arduino Board. Grove LCD RGB Backlight подключается к I2C разъему на Grove Basic Shield.
    Ультразвуковой датчик расстояния HC-SR04 подключается к Grove Basic Shield следующим образом (см. рис. schema.jpg):

- Vcc к +5V;
	
- Trig к пину #3;

- Echo к пину #4;
	
- Gnd к Gnd.

2. Используя кроссплатформенную среду разработки [MCU SDK](https://software.intel.com/en-us/node/545143), загружаем код для работы датчика, представленный в файле mcu_main.c

3. Помещаем в /home/root/ файлы show_distance.py и startup.sh

4. Скачиваем в /home/root/ файл init_DIG.sh, если он отсутствует:
> wget http://downloadmirror.intel.com/24910/eng/init_DIG.sh

5. Помечаем скрипты как исполняемые:
> chmod a+x /home/root/startup.sh
> chmod a+x /home/root/init_DIG.sh

6. Так как Yocto Linux использует systemd, то для добавления скрипта в автозапуск нужно создать файл так называемого «сервиса». Переносим в /lib/systemd/system/ файл startup-script.service

7. Добавляем скрипт в автозапуск:
> systemctl enable startup-script

# Итог

После перезагрузки на символьном дисплее должна отобразиться измеренная дистанция.