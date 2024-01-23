//www.elegoo.com
//2018.12.19
#include <Servo.h>
#define IR1Pin  A1
#define IR2Pin  A0
/* After including the corresponding libraries,
   we can use the "class" like "Servo" created by the developer for us.
   We can use the functions and variables created in the libraries by creating 
   objects like the following "myservo" to refer to the members in ".".*/
void dispense();
Servo Servo1;
Servo Servo2;

void setup(){
  Serial.begin(9600);
  Servo1.attach(2);//connect pin 9 with the control line(the middle line of Servo) 
  Servo2.attach(4);
  delay(1000);
    //2
    ++++++++++++dispense();
  //dispense2();
} 
char c;
void loop(){
  //dispense();
//  Serial.print(!digitalRead(IR1Pin));
//  Serial.print(",");
//  Serial.println(!digitalRead(IR2Pin));

  while (Serial.available()) {
    delay(3);  
    c = Serial.read();
    if (c=='2'){
    dispense2();
    Serial.println("Dispensed 1 of medicine 2");
  }
  if (c=='1'){
    dispense();
    Serial.println("Dispensed 1 of medicine 1");
  }
  }
  
  
  
}

void dispense()
{
  int cur=millis();
  int target=cur+500;
  int dir=true;
  while (!digitalRead(IR2Pin)){
//  Serial.print(!digitalRead(IR1Pin));
//  Serial.print(",");
//  Serial.println(!digitalRead(IR2Pin));
  if (dir){
  Servo1.write(180);// move servos to center position -> 60°
  }else{
  Servo1.write(0);// move servos to center position -> 90°
  }
  if (millis()>target){
    dir=!dir;
    target=millis()+500;
  }
  
  }
  
}

void dispense2()
{
  int cur=millis();
  int target=cur+1000;
  int dir=true;
  while (!digitalRead(IR1Pin)){
//  Serial.print(!digitalRead(IR1Pin));
//  Serial.print(",");
//  Serial.println(!digitalRead(IR2Pin));
  if (dir){
  Servo2.write(180);// move servos to center position -> 60°
  }else{
  Servo2.write(0);// move servos to center position -> 90°
  }
  if (millis()>target){
    dir=!dir;
    target=millis()+1000;
  }
  
  }
  
}
