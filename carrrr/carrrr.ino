#define r1 6
#define r2 9 
#define l1 3 
#define l2 5
#define IR1Pin  A0
#define IR2Pin  A1
#define SPEED 30
#define DISTANCE 10

int trig=11;
int echo=10;
long Pulseduration;
int distance=100;
int start_moving = 2;


void forwards(int speed);
void turnright();
void turnleft();
void brake(void);
void line_trace(int);
void slt();
void woohoo();
int check_dist();
bool state=false;
void setup() {
    Serial.begin(9600);
    pinMode(l1, OUTPUT);
    pinMode(l2, OUTPUT);
    pinMode(r1, OUTPUT);
    pinMode(r2, OUTPUT);
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
 
}
int cur_state=1;
int previous_state=1;
void loop() {
  cur_state=digitalRead(start_moving);

 
  while(digitalRead(start_moving)==1 && check_dist()>DISTANCE){
    for (int j=0; j<100; j++){
     
    line_trace(j);
    }
    
  }
  brake();
 
  if (cur_state!=previous_state && cur_state==1){
    while(check_dist()<DISTANCE+5){
    for (int i=0; i<100; i++){
      line_trace(i);
    }
    }
    delay(100);
    while(check_dist()>DISTANCE){
    for (int j=0; j<100; j++){
      line_trace(j);
    }
    
  }  
  }
  previous_state=cur_state;
  
}

int check_dist(){
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(5);
    digitalWrite(trig,LOW);
    Pulseduration=pulseIn(echo,HIGH);
    distance=Pulseduration/58;
Serial.println(distance);
    return distance;     
}
void line_trace(int j) {
    int lightVal1 = analogRead(IR1Pin);
    int lightVal2 = analogRead(IR2Pin);
   
    if (lightVal1 > 435) {
        if (lightVal2 > 435) {
            forwards(j);
        }
        else {  
            turnright(j);
        }
    }
    else {
        if (lightVal2 < 435) {
            forwards(j);
        }
        else {
            turnleft(j);
        }
    }
}
void slt(){
  int lightVal1 = analogRead(IR1Pin);
  if (lightVal1 > 435){
    turnright();
  }
  else {
    turnleft();
  }
}
void woohoo(){
  brake();
  Serial.println("interrupted");
  Serial.println(digitalRead(2));
  delay(1000);
}
void forwards(int speed) {
    digitalWrite(r1, LOW);
    
    digitalWrite(l1, LOW);
    if (speed <SPEED*1.25){
    analogWrite(l2, 255); ;
    analogWrite(r2, 255);
    }else{
      digitalWrite(r2, LOW);
    
    digitalWrite(l2, LOW);
    }
}
void brake() {
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
}
void turnright(int speed) {
    digitalWrite(r1, LOW);
    if (speed <SPEED*2){
    analogWrite(r2, 255);
    }else{
    analogWrite(r2, 0);
    }
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
}

void turnleft(int speed) {
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
    digitalWrite(l1, LOW);
    if (speed <SPEED*2){
    analogWrite(l2, 255);
    }else{
    analogWrite(l2, 0);
    }
}
