# IZ-AZ 🧭
Easy Azimuth display for amature radio antenna rotators

This is a 2 parts project:
1. Remote module - attached to one of the rotating parts (boom, pole, motor, etc')
this module contains the compass and transmits the azimuth to the Station module

2. Station module - receives the Remote module transmition and display the azimuth on the LCD
It also pushes the azimuth to the COM port so that other programs can read and use it.


Remote module 📡
-------------
- Arduino pro mini
- 433MHz ASK transmitter
- GY-271 HMC5883L Digital Compass (3.3v)

![promini](https://user-images.githubusercontent.com/24712835/133967826-984f3f25-2c4e-4ef8-8a24-b9c2356f814d.PNG)
![HMC5883L](https://user-images.githubusercontent.com/24712835/133968411-6b3fa3ec-9f69-4f71-8ad4-f264eb2424bd.PNG)
![433TX](https://user-images.githubusercontent.com/24712835/133967978-cde48dd8-5c06-4cd3-b061-c042d39e43d8.PNG)


Station module 🏠
--------------
- Arduino nano
- 433MHz ASK reciever
- 2*16 LCD

![nano](https://user-images.githubusercontent.com/24712835/133968429-6a6d9c30-166a-4cb9-a21a-307b86cd4563.PNG)
![433RX](https://user-images.githubusercontent.com/24712835/133968015-e499f448-b7c8-4aaa-bb50-e7f5c4bf2eda.PNG)
![lcd](https://user-images.githubusercontent.com/24712835/133968026-307665f1-bb13-47b0-a84e-f2fb52413668.png)
