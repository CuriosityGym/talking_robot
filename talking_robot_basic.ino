//https://www.factoryforward.com/mp3-tf-16p-arduino-dfplayer/

#include "Arduino.h"
 
#include "SoftwareSerial.h"
 
#include "DFRobotDFPlayerMini.h"
 
SoftwareSerial mySoftwareSerial(3, 2); // RX, TX
 
DFRobotDFPlayerMini myDFPlayer;

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;
 
void setup()
 
{
 
  mySoftwareSerial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);
 
  Serial.println();
 
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
 
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
 
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
 
    Serial.println(F("Unable to begin:"));
 
    Serial.println(F("1.Please recheck the connection!"));
 
    Serial.println(F("2.Please insert the SD card!"));
 
    while(true);
 
  }
 
  Serial.println(F("DFPlayer Mini online."));
 
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
 
}
 
void loop()
 
{
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 // Sets the trigPin on HIGH state for 10 micro seconds
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 // Reads the echoPin, returns the sound wave travel time in microseconds
 duration = pulseIn(echoPin, HIGH);
 // Calculating the distance
 distance= duration*0.034/2;
 // Prints the distance on the Serial Monitor
 Serial.print("Distance: ");
 Serial.println(distance);
 
 
 if(distance < 20){
  myDFPlayer.next();  //Play next mp3
  delay(3000);
 }
 
 
 
}
