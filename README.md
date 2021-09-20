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
![lcd](https://user-images.githubusercontent.com/24712835/133973304-bc6a9c48-b0fe-41d9-8712-b8bf6c9cc91b.png)


My IZ-AZ build 🛠️
--------------
![IMG_20210920_085830](https://user-images.githubusercontent.com/24712835/133973324-ebe749b0-898d-4f0f-ba35-6ebad7deb68f.jpg)
![IMG_20210920_111628](https://user-images.githubusercontent.com/24712835/133973631-71f4e3ce-7f5d-421e-b285-a1f733e723df.jpg)
![IMG_20210906_130919](https://user-images.githubusercontent.com/24712835/133973133-72cdacbf-b4ad-4969-b550-709cd759de6e.jpg)
![IMG_20210906_130939](https://user-images.githubusercontent.com/24712835/133973136-12077c4a-f7bd-46c1-b4c3-7f2c238910b5.jpg)

Enjoy,
Gil 4Z1KD
