#include <stdio.h>
#include <math.h>


#define c4  262
#define d4  294
#define e4  330
#define f4  349
#define g4  392
#define a4  440
#define b4  494
#define c5  523

#define R 0

int speakerOut1 = 11;
int echoPin = 13;
int triggerPin = 12;
int notenumber[] = { 4, 5, 6, 7, 8, 9, 10 };
int notechar[] = { c4, d4, e4, f4, g4, a4, b4 }; 
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int a = 9;
int b = 10;


int frequency1 = 0;
int frequency2 = 0;
int buttonCheck = 0;
int buttonstate1 = 0;
int buttonstate2 = 0;
int buttonstate3 = 0;
int buttonCount = 0;

const int xAxisPin = A0;
const int yAxisPin = A1;
const int switchPin = 2;

int centerX = 0;
int centerY = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(speakerOut1, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(switchPin, INPUT);
  pinMode(c, INPUT);
  pinMode(d, INPUT);
  pinMode(e, INPUT);
  pinMode(f, INPUT);
  pinMode(g, INPUT);
  pinMode(a, INPUT);
  pinMode(b, INPUT);
  centerX = analogRead(xAxisPin);
  centerY = analogRead(yAxisPin);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance = duration * 0.0017;

  Serial.println(distance);


  
  int jsState = digitalRead(switchPin);
  if (jsState == HIGH) { // Pullup
    Serial.println("Button was pressed");
  } else {
    Serial.println("Button was NOT pressed");
  }
  int x = analogRead(xAxisPin);
  int y = analogRead(yAxisPin);
  x -= centerX;
  y -= centerY;
  int xRatio = x / 100;
  int yRatio = y / 100;


  distance += (xRatio + yRatio);


  buttonstate1 = 0;
  buttonstate2 = 0;
  buttonstate3 = 0;
  buttonCount = 0;
  for (int i = 0; i < 7; i += 1) {
    buttonCheck = digitalRead(notenumber[i]);
    if (buttonCheck == LOW) {
      if (buttonCount == 0) {
        buttonstate1 = notechar[i];
      }
      else if (buttonCount == 1) {
        buttonstate2 = notechar[i];
      }
      else if (buttonCount == 2) {
        buttonstate3 = notechar[i];
      }
      
      buttonCount += 1;
    }
    
  }

 
  if (buttonstate1 != 0 && buttonstate2 == 0 && buttonstate3 == 0) {
    tone(speakerOut1, buttonstate1*(pow(2, distance)), 150);
    delay(150);

  }
  if (buttonstate1 != 0 && buttonstate2 != 0 && buttonstate3 == 0) {
    tone(speakerOut1, buttonstate1*(pow(2, distance)), 150);
    delay(150);
    tone(speakerOut1, buttonstate2*(pow(2, distance)), 150);
    delay(150);
  }
  if (buttonstate1 != 0 && buttonstate2 != 0 && buttonstate3 != 0) {
    tone(speakerOut1, buttonstate1*(pow(2, distance)), 150);
    delay(150);
    tone(speakerOut1, buttonstate2*(pow(2, distance)), 150);
    delay(150);
    tone(speakerOut1, buttonstate3*(pow(2, distance)), 150);
    delay(150);
  }
  
}
