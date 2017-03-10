#include "Ultrasonic.h"

int ledPin = 13;
int uep = 12;
int utp = 8;
Ultrasonic usonic(uep,utp);

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(uep, INPUT);
  pinMode(utp, OUTPUT);
}

void loop() 
{
  triggerParktronic();
  long duration =  pulseIn(uep, HIGH);
  long cm = microsecondsToCentimeters(duration);

  if(cm <= 50) // if the distance is less than 50cm, start LED blinking, if not hold the LED turned off
  {
      ledPinBlinking(cm);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }

  if(Serial.available() > 0) // if any information is sent, read that information and if its "s" to show the distance
  {
    char pres = Serial.read();
    
    if(pres == 's')
    {
      Serial.print(cm);
      Serial.println(" cm");
    }    
  }


  delay(150);
  
}

void ledPinBlinking(int distance) // function for LED blinking, the less the distance the faster the blinking
{
  digitalWrite(ledPin, HIGH);
  delay(distance*10);
  digitalWrite(ledPin, LOW);
  delay(distance*10);
}

void triggerParktronic() // function to send sound waves
{
  digitalWrite(utp, LOW);
  delayMicroseconds(2);
  digitalWrite(utp, HIGH);
  delayMicroseconds(10);
  digitalWrite(utp, LOW);
}

long microsecondsToCentimeters(long microseconds) // function to convert microseconds in centimeters
{
    return microseconds / 29 / 2;
}
