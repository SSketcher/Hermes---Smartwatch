# Hermes---Smartwatch
## General info
Projeckt  of a wristband which is a watch and a health monitor at the same time, measuring parameters such as: heart rate, heart rate and the number of steps taken. The project is called HERMES and it refers to its general purpose, namely the Health Monitoring System. The purpose of the HERMES wristband is to monitor the condition during the day, not necessarily for sports / recreational purposes. Along with the parallel project "Hermes - health monitoring system web application", the full Hermes package will aim to draw the user's attention to how he spends his day and how it may affect his health and well-being.

The band is designed to monitor the user's condition during daily activities. The information is displayed on the band's screen, you can see the current time, the number of steps taken during the day and the heart rate at the current moment. The idea was to create a small device that consumes as little electricity as possible. The project is based on the D1 mini board with the ESP8266 microcontroller, which collects data from the heart rate monitor and accelerometer and displays them on the OLED screen. The collected data is sent via the built-in wifi module to the database and than further processed in [Hermes---Web-App](https://github.com/SSketcher/Hermes---Web-App).


![alt text](https://github.com/SSketcher/Hermes---Smartwatch/blob/main/resources/0.png)

The photo shows the complete electronics assembled into the final version of the project.
Consisting of components (from the top):
- LCD display
- ADXL345 accelerometer
-Wemos D1 mini ESP8266
-Power system
On a four-wire cable:
- MAX30102 heart rate monitor
On a two-core cable:
- 9V battery connector



![alt text](https://github.com/SSketcher/Hermes---Smartwatch/blob/main/resources/1.png)

The attached photo shows the project housing with attached electronics.



![alt text](https://github.com/SSketcher/Hermes---Smartwatch/blob/main/resources/2.png)

Project splash screen This is where all initializations and full project start up is performed.



![alt text](https://github.com/SSketcher/Hermes---Smartwatch/blob/main/resources/3.png)

Data synchronization screen, consisting of three phases:
- establishing a connection with Wi-Fi
- establishing a connection with database
- sending the SQL command with the data to the database



![alt text](https://github.com/SSketcher/Hermes---Smartwatch/blob/main/resources/4.png)

The main screen displays the time and basic information collected from sensors, processed on an ongoing basis for the user:
- the number of steps taken
- the heart rate.


## Technologies
* ESP 8266
* C/C++
* Arduino Framework
* NTC 

Libraries:
* MAX30105
* NTPClient
* WiFiUdp
* ESP8266 WiFi
* MySQL Connector Arduino

## Sources and helpful materials
[ESP8266 Arduino Core’s documentation](https://arduino-esp8266.readthedocs.io/en/latest/)
[Arduino framework for esp8266](https://www.arduino.cc/reference/en/libraries/esp8266-framework/)
