# OrangePI_OLED
Add OLED display with sys info to your Orange PI board

Originated from https://github.com/vdzimyatskevich/SSD1306.git
**connection Orange PI Lite:**

| OLED |    Name   |  Pin  |
|:----:|:---------:|:-----:|
|`VDD` |    3.3v   |  1    |
|`SDA` |   SDA.0   |  3    |
|`SCK` |   SCL.0   |  5    |
|`GND` |    0v     |  9    |

Any other H3 and H2+ boards use i2c-0 pins

To run app:

1.> git clone https://github.com/terraformist/Arduino_ssd1306.git
2.> cd Arduino_SSD1306
3.> make
4.> sudo ./ssd1306_example

Optionaly to install in /usr/local/bin
5.> sudo make install

To run app at boot time:

1.> sudo crontab -e
2.> add row: `@reboot /usr/local/bin/ssd1306_sysinfo
3.> reboot
 enjoy :)


Tested with Armbian image https://www.armbian.com/download/, Orange PI Lite and Orange PI Zero boards.
[![How it works](https://github.com/vadzimyatskevich/OrangePI_OLED/blob/master/img/pic_1.JPG)](https://www.youtube.com/watch?v=xUK7WmqTY78)
![How it works](https://github.com/vadzimyatskevich/OrangePI_OLED/blob/master/img/pic_2.jpg?raw=true)
