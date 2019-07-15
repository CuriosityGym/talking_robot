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
int obstacle = 0;
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
 
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  delay(2000);
}
 
void loop()
{
  if(measureDistance() < 25){
  for(int i=0; i<4;i++)
     {
       distance = measureDistance();
       //Serial.print(i);
       if(i != 0)
         {
           // Calculating the distance
           distance += distance;
           delay(50);
         }
     }
         
  distance = distance/3;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(50);
  if((distance < 25) && (distance > 10))
    {
      Serial.println("first mp3");
      myDFPlayer.play(1);  //Play the first mp3
      delay(20000);
    }
 
  if(distance <= 10)
    {
      Serial.println("second mp3");
      myDFPlayer.play(2);  //Play second mp3
      delay(3000);
    }
  }
 
 
}

int measureDistance(){
  int d=0;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  d += duration*0.034/2;
  return d;
   
}
