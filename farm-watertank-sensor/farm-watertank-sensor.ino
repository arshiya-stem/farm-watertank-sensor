/*
Watertank sensor program
///@Author Arshiya MS
///@Date July 6th, 2026
///@Brief
This is a program for the custom watertank sensor for Boreal Farms.
This program uses an Ultrasonic sensor to detect the distance from water surface, 
compute how much (%) is filled based on Tank height, and transmit the data via HC-05 bluetooth module

///@version 0.1
*/

#include <EEPROM.h>

/// Ultrasonic sensor pins
const int trigPin = 8;
const int echoPin = 9;

/// LED pins
const int greenLED = 6;
const int yellowLED = 5;
const int redLED = 4;

/// Tank Height & EEPROM
int tankHeightADDR = 0;
int tankHeight; 

///Function declarations

///@brief used to get the amount of liquid in tank as percent
///@param no parameters
///@return returns the tank percentage rounded to closest integer
int GetWaterLevelinPercent();

///@brief setter for the tank height. Sets the tank height to desired height inside program via hc-05 bluetooth module
///@param no param
///@return no return
void SetWatertankHeight();

///@brief sends integer data through hc-05 bluetooth module
///@param integer data to be sent
///@return no return

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  //check if EEPROM is empty
  if (EEPROM.read(tankHeightADDR) == 0xFF) {
    EEPROM.write(tankHeightADDR, 100);  //default tank height is 1 meter
  }

  delay(300);
  tankHeight = EEPROM.read(tankHeightADDR);
  Serial.println("Tank height = " + String(tankHeight));
}

void loop() {
  // put your main code here, to run repeatedly:

  ///testing Ultrasonic sensor
  Serial.println("Tank percent: " + String(GetWaterLevelinPercent()) + "%");
  TransmitDataBluetooth(GetWaterLevelinPercent());
  if (Serial1.available()) SetWatertankHeight();
  delay(1000);
}

///Function defenitions

//calculate the percentage of liquid in tank based on Ultrasonic sensor reading
int GetWaterLevelinPercent() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.0343)/2;
  
  delay(500);

  int percent = ((tankHeight - distance) / tankHeight) * 100;
  percent = constrain(percent, 0, 100);
  return percent;
}

//transmit data via Bluetooth
void TransmitDataBluetooth(int data) {
  digitalWrite(greenLED, HIGH);
  Serial1.println(data);
  delay(500);
  digitalWrite(greenLED, LOW);
}

//Set and store the tank height based on recieved bluetooth packet
void SetWatertankHeight() {
    //testing: reading raw values from Serial Bluetooth Terminal to determine the data type recieved
    tankHeight = Serial1.parseInt();

    //update EEPROM with new tank height
    EEPROM.update(tankHeightADDR, tankHeight);
    delay(300);
    Serial.println("EEPROM tankheight: " + EEPROM.read(tankHeightADDR));
    Serial.println("new height: " + String(tankHeight));
    //flush the Serial buffer
    Serial1.flush();
}
