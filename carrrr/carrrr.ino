#define l1 6
#define l2 9 
#define r1 3 
#define r2 5
#define IR1Pin  A0
#define IR2Pin  A1
int IR1_Val = 0;
void Full_speed_forward(void);
void Full_speed_backward(void);
void forwards(int speed);
void backwards(int speed);
void turnright();
void turnleft();
void brake(void);
void setup() {
    Serial.begin(9600);
    pinMode(l1, OUTPUT);
    pinMode(l2, OUTPUT);
    pinMode(r1, OUTPUT);
    pinMode(r2, OUTPUT);
    
}
void loop() {
    int lightVal1 = analogRead(IR1Pin);
    int lightVal2 = analogRead(IR2Pin);
    
    Serial.print(lightVal1);
    Serial.print(",");
    Serial.print(lightVal2);
    Serial.print("\n");
    if (lightVal1 < 435){
      if (lightVal2 < 435){
        forwards(85);
      }
      else{
        turnright();
      }
    }
    else{
      if (lightVal2 > 435){
        forwards(30);
      }
      else{
        turnleft();
      }
    }
}

void forwards(int speed) {
    digitalWrite(r2, LOW);
    analogWrite(r1, speed);
    digitalWrite(l2, LOW);
    analogWrite(l1, speed); ;
}
void brake() {
    Serial.println("Brake");
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
}
void turnright(){
  analogWrite(r1, 100);
  digitalWrite(r2, LOW);
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
}
void turnleft(){
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  analogWrite(l1, 110);
  digitalWrite(l2, LOW);
}
