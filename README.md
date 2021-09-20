# IZ-AZ
Easy Azimuth display for amature radio antenna rotators

This is a 2 parts project:
1. Remote module - attached to one of the rotating parts (boom, pole, motor, etc')
this module contains the compass and transmits the azimuth to the Station module

2. Station module - receives the Remote module transmition and display the azimuth on the LCD
It also pushes the azimuth to the COM port so that other programs can read and use it.


Remote module
--------------
Arduino pro mini
433MHz ASK transmitter
GY-271 HMC5883L Digital Compass


Station module
--------------
Arduino nano
433MHz ASK reciever
2*16 LCD
