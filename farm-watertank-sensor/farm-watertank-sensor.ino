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

#include <SoftwareSerial.h>

/// Ultrasonic sensor pins
const int trigPin = 8;
const int echoPin = 9;

/// LED pins
const int greenLED = 4;
const int yellowLED = 5;
const int redLED = 6;

/// Tank Height
int tankHeight = 100; // replace this value with actual tank height

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

}

void loop() {
  // put your main code here, to run repeatedly:

  ///testing Ultrasonic sensor
  Serial.println("Tank percent: " + String(GetWaterLevelinPercent()) + "%");
  TransmitDataBluetooth(GetWaterLevelinPercent());
  SetWatertankHeight();
  delay(500);
}

///Function defenitions

int GetWaterLevelinPercent() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.0343)/2;
  
  delay(100);

  int percent = ((tankHeight - distance) / tankHeight) * 100;
  return percent;
}

void TransmitDataBluetooth(int data) {
  Serial1.println(data);
}

void SetWatertankHeight() {
  if (Serial1.available()){
    tankHeight = (int)Serial1.read();
    Serial.println("Successfully changed tank height");
  }
}
