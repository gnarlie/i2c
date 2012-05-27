Getting Started
===============

Prepare your Pi for I2C
-----------------------
1. Update the firmware from https://github.com/raspberrypi/firmware/tree/master/boot. Copy the *.elf files to your boot partition.

2. Download the newest Pi kernel. I used the .deb from http://www.bootc.net/raspberrypi/linux-image-3.2.18-rpi1+_1_armel.deb.

	>
	> dpkg install linux-image-3.2.18-rpi1+_1_armel.deb
	>

3. Copy the kernel image on your boot partition to kernel.img

4. Reboot & apt-get update. 

5. modprobe i2c-dev

6. Install libi2c-dev via apt-get.

Communicating with your device
------------------------------

Validate that your device is seen with i2cdetect

> pi@raspberrypi:~/i2c$ sudo i2cdetect -y -r 0
>      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
> 00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
> 10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
> 20: 20 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
> 30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
> 40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
> 50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
> 60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --                         

