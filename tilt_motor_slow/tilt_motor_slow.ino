#include <Servo.h>

Servo myservo1;  // create servo object to control servo
Servo myservo2;

int lightPins[] = {A2, A3, A4, A5};

int joypin1 = A0;  // analog pin used to connect the potentiometer
int joypin2 = A1;

boolean printed = false;

int joy1;
int joy2;
int midMotor1;
int midMotor2;
int motorVal1;
int motorVal2;

int m1Low = 20;
int m1High = 40;
int m2Low = 30;
int m2High = 50;

unsigned long currentTime;
unsigned long prevTime;
int time = 1000;

int light[4];
int lightAmbient[4];

void setup()
{
  myservo1.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(9);


  Serial.begin(9600);
  delay(2000);
  joy1 = analogRead(joypin1);
  joy2 = analogRead(joypin2);
  midMotor1 = map(joy1, 0, 1023, m1Low, m1High);
  midMotor2 = map(joy2, 0, 1023, m2Low, m2High);
  motorVal1 = midMotor1;
  motorVal2 = midMotor2;

  for (int i = 0; i < 4; i++) {
    light[i] = smoothing(lightPins[i]);
    lightAmbient[i] = light[i];
    Serial.println(lightAmbient[i]);
  }

}

void loop()
{
  motors();
  lights();
  printed = false;
}

void lights() {
  for (int i = 0; i < 2; i++) {
    light[i] = smoothing(lightPins[i]);
    if (light[i] < (lightAmbient[i] - 300)) {
      prevTime = millis();
      while (light[i] < (lightAmbient[i] - 300)) {
        currentTime = millis();
        light[i] = smoothing(lightPins[i]);
        if (currentTime > (prevTime + time)){
          if(!printed) 
          Serial.println(i);
          printed = true;
        }
      }
    }

  }
}

void motors() {
  motorMove();
  delay(50);
  myservo1.write(motorVal1);

  motorMove();
  delay(50);
  myservo2.write(motorVal2);

}

void motorMove() {

  joy1 = analogRead(joypin1);
  if (joy1 > 1000 && motorVal1 < m1High) {
    motorVal1++;
  }

  if (joy1 < 50 && motorVal1 > m1Low) {
    motorVal1--;
  }

  if (joy1 > 50 && joy1 < 1000) {
    if (motorVal1 < midMotor1)
      motorVal1++;
    else if (motorVal1 > midMotor1)
      motorVal1--;
  }

  joy2 = analogRead(joypin2);
  if (joy2 > 1000 && motorVal2 < m2High) {
    motorVal2++;
  }

  if (joy2 < 50 && motorVal2 > m2Low) {
    motorVal2--;
  }

  if (joy2 > 50 && joy2 < 1000) {
    if (motorVal2 < midMotor2)
      motorVal2++;
    else if (motorVal2 > midMotor2)
      motorVal2--;
  }

}

int smoothing(int pin) {
  int val = 0;
  for (int i = 0; i < 100; i++) {
    val = val + analogRead(pin) / 100;
  }
  return val;
}


