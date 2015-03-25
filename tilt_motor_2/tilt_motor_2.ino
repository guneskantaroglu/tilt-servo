#include <Servo.h> 
 
Servo myservo1;  // create servo object to control servo
Servo myservo2;  
 
int joypin1 = A0;  // analog pin used to connect the potentiometer
int joypin2 = A1;
int val1;    // variable to read the value from the analog pin 
int val2;
 
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
  val1 = analogRead(joypin1);           // reads the value of the potentiometer (value between 0 and 1023) 
  val1 = map(val1, 0, 1023, 0, 80);    // scale it to use it with the servo (value between 0 and 180) 
  myservo1.write(val1);                // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
  
  val2 = analogRead(joypin2);           // reads the value of the potentiometer (value between 0 and 1023) 
  val2 = map(val2, 0, 1023, 0, 80);    // scale it to use it with the servo (value between 0 and 180) 
  myservo2.write(val2);                // sets the servo position according to the scaled value 
  delay(15);                     
  
  Serial.println(val1);
  
}
