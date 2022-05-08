//JAKUB WOJCIECHOWSKI
//THIS IS MAIN MODULE FOR HERMES PROJECT
#include <Wire.h>
#include "data_struct.h"
#include "SSD1306Wire.h"
#include "heat_rate_module.h"
#include "pedometr.h"


SSD1306Wire display(0x3c, D2, D1);

#include "wifi_module.h"
#include"time_module.h"

float BPM = 0;
int steps_ = 0;
bool sync = true;

//--------------------------SETUP FUNCTION--------------------------  
void setup() 
{
  Wire.begin();
  Serial.begin(9600);

  if (!display.init()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  }else Serial.println("SSD1306 display initalized!");

  display.flipScreenVertically();
  
  //Start Screen
  display.clear();
  StartScreen();
  display.display();
  delay(1000);
  
  setup_heartRate();   //initalizing sensor MAX30102
  setup_accelerometer();    //initalizing accelerometer
  setup_time();     //updating the time from NTP server
  time_update();
  
  delay(100);
  
  //if(WiFi.status() != WL_CONNECTED)WiFi.mode(WIFI_OFF);
}


//--------------------------MAIN LOOP OF THE WHOLE SYSTEM--------------------------  
void loop() 
{
  BPM = heartRate();    //taking mesurament of heart rate
  steps_ = Pedometer();    //counting number of taken steps

  if(timeClient.getHours() == 12 && sync == true){
    sync_data(steps_, BPM);
    sync == false;
  }
  if(timeClient.getHours() == 13) sync == true;
  
  //Main Screen displamant
  display.clear();
  MainScreen();
  display.display();
  delay(10);
}


//--------------------------START SCREEN--------------------------  
void StartScreen() 
{
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_24);
    display.drawString(64, 11, "Hermes");
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 37, "Health monitoring");
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 47, "system");
}


//--------------------------MAIN SCREEN WITH CURRENT DATA--------------------------  
void MainScreen() 
{
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_24);
    display.drawString(64, 11, String(timeClient.getHours()) + ":" + String(timeClient.getMinutes()));
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 37, String(steps_) + " Steps");
    display.setFont(ArialMT_Plain_10);
    display.drawString(64, 47, String(BPM*8) + " Bpm");
}
