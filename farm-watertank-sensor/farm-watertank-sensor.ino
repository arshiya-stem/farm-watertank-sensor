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

/// Ultrasonic sensor pins
const int trigPin = 8;
const int echoPin = 9;

/// Ultrasonic variables for distance measurement
float duration, distance;

/// LED pins
const int greenLED = 4;
const int yellowLED = 5;
const int redLED = 6;

///Function defenitions

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
