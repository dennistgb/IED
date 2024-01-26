
//www.elegoo.com
//2018.12.19
#include <Servo.h>
#define IR1Pin  A1
#define IR2Pin  A0
/* After including the corresponding libraries,
   we can use the "class" like "Servo" created by the developer for us.
   We can use the functions and variables created in the libraries by creating 
   objects like the following "myservo" to refer to the members in ".".*/
void dispense(int);
Servo Servo1;
Servo Servo2;

void setup(){
  Serial.begin(9600);
  Servo1.attach(2);//connect pin 9 with the control line(the middle line of Servo) 
  Servo2.attach(4);
//  Servo1.write(180);
//  Servo2.write(180);
//  delay(1000);
//  Servo1.write(0);
//  Servo2.write(0);

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
    dispense(2);
    Serial.println("Dispensed 1 of medicine 2");
  }
  if (c=='1'){
    dispense(1);
    Serial.println("Dispensed 1 of medicine 1");
  }
  }
  
  
  
}


void dispense(int number)
{
  int IRPIN;
  Servo SERVOPIN;
  if (number==1){
    IRPIN=IR2Pin;
    SERVOPIN=Servo1;
  }else{
    IRPIN=IR1Pin;
    SERVOPIN=Servo2;
  }
  int cur=millis();
  int target=cur+1000;
  int dir=true;
  while (!digitalRead(IRPIN)){
  cur=millis();
  if (dir){
  SERVOPIN.write(((float)(target-cur)/4.0));// move servos to center position -> 60°
  }else{
  SERVOPIN.write(180-((float)(target-cur)/4.0));// move servos to center position -> 90°
  }
  if (cur>target){
    dir=!dir;
    target=cur+1000;
  }
  
  }
  
}
