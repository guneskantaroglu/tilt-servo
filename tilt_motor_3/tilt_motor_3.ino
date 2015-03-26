#include <Servo.h> 
 
Servo myservo1;  // create servo object to control servo
Servo myservo2;  
 
int joypin1 = A0;  // analog pin used to connect the potentiometer
int joypin2 = A1;

int oldval1, newval1;    // variable to read the value from the analog pin 
int oldval2, newval2;
 
void setup() 
{ 
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo2.attach(10);
  
  Serial.begin(9600);
} 
 
 int treatValue(int data) {
   return (data * 9/1024)+48;
   
 }
  
void loop() 
{ 
  newval1 = smoothing(joypin1);           // reads the value of the potentiometer (value between 0 and 1023) 
  newval1 = map(newval1, 0, 1023, 20, 40);    // scale it to use it with the servo (value between 0 and 180) 
  if (newval1 < (oldval1+2) || newval1 > (oldval1-2)){
    myservo1.write(newval1);                // sets the servo position according to the scaled value
    delay(155);                           // waits for the servo to get there
    oldval1=newval1;
  }
  
  
  newval2 = smoothing(joypin2);           // reads the value of the potentiometer (value between 0 and 1023) 
  newval2 = map(newval2, 0, 1023, 30, 50);   // scale it to use it with the servo (value between 0 and 180)  
 if (newval2 < (oldval2+2) || newval2 > (oldval2-2)){
    myservo2.write(newval2);                // sets the servo position according to the scaled value
    delay(155);                           // waits for the servo to get there
    oldval2=newval2;
  }  
  
  Serial.println(analogRead(joypin1));
  
}

int smoothing(int pin) {
  int val=0;
  for(int i=0; i<100; i++) {
   val=val+analogRead(pin)/100;
  }
  return val;
  
}
