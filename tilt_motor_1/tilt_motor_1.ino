#include <Servo.h> 
 
Servo myservo1;  // create servo object to control servo
Servo myservo2;  
 
int potpin1 = A0;  // analog pin used to connect the potentiometer
int potpin2 = A1;
int val1;    // variable to read the value from the analog pin 
int val2;

int joy1;
int midMotor;
int motorVal;
 
void setup() 
{ 
  myservo1.attach(10);  // attaches the servo on pin 9 to the servo object 
  myservo2.attach(9);
  
  
  Serial.begin(9600);
  joy1 = analogRead(potpin1);
  midMotor = map(joy1,0,1023,0,30);
  motorVal = midMotor;
} 
 
void loop() 
{ 
  motorMove();
  delay(50);
  myservo1.write(motorVal);
  /*
  val1 = analogRead(potpin1);           // reads the value of the potentiometer (value between 0 and 1023) 
  //val1 = map(val1, 0, 1023, 0, 30);    // scale it to use it with the servo (value between 0 and 180) 
  myservo1.write(val1);                // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
  
  val2 = analogRead(potpin2);           // reads the value of the potentiometer (value between 0 and 1023) 
  val2 = map(val2, 0, 1023, 0, 30);    // scale it to use it with the servo (value between 0 and 180) 
  myservo2.write(val2);                // sets the servo position according to the scaled value 
  delay(15);                     
  */
  Serial.println(joy1);
  Serial.println(motorVal);
  
}

void motorMove(){
  
  joy1 = analogRead(potpin1);
  if(joy1>1000 && motorVal<30){
    motorVal++;
  }
  
  if(joy1<50 && motorVal >0){
  motorVal--;
  }
  
  if(joy1>50 && joy1<1000){
    if(motorVal<midMotor)
    motorVal++;
    else if(motorVal>midMotor)
    motorVal--;
  }
  
}


