#define r1 6
#define r2 9 
#define l1 3 
#define l2 5
#define IR1Pin  8
#define IR2Pin  7
int trig=11;
int echo=10;
long Pulseduration;
int distance=100;


void forwards(int speed);
void turnright();
void turnleft();
void brake(void);
void line_trace();
int check_dist();

void setup() {
    Serial.begin(9600);
    pinMode(l1, OUTPUT);
    pinMode(l2, OUTPUT);
    pinMode(r1, OUTPUT);
    pinMode(r2, OUTPUT);
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);


}
void loop() {
    while (check_dist() > 15) {
    Serial.println(check_dist());
    line_trace();
    }
    brake();
    Serial.println("exited loop");
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
void line_trace() {
    int lightVal1 = digitalRead(IR1Pin);
    int lightVal2 = digitalRead(IR2Pin);
    Serial.print(lightVal1);
    Serial.print(",");
    Serial.println(lightVal2);
    if (lightVal1 == 0) {
        if (lightVal2 == 0) {
            forwards(80);
        }
        else {
            turnright();
        }
    }
    else {
        if (lightVal2 == 1) {
            forwards(30);
        }
        else {
            turnleft();
        }
    }
}
void forwards(int speed) {
    digitalWrite(r1, LOW);
    analogWrite(r2, speed);
    digitalWrite(l1, LOW);
    analogWrite(l2, speed); ;
}
void brake() {
    Serial.println("Brake");
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
}
void turnright() {
    digitalWrite(r1, LOW);
    analogWrite(r2, 100);
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
}
void turnleft() {
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
    digitalWrite(l1, LOW);
    analogWrite(l2, 140);
}
