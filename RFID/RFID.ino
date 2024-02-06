#include <SPI.h>
#include <MFRC522.h>
#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

void readData(int c);
void displayData(int dataIndex);
void printDateTime(DateTime dt);
void dispense(int number);

#define SS_PIN 10
#define RST_PIN 9
#define IR1_Pin  A0
#define IR2_Pin  A1


Servo Servo1;
Servo Servo2;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
RTC_DS1307 rtc;
int r = 0;
const int numRows = 3;
const int numCols = 5;
char myArray[numRows][numCols][20] =
{
  // added time column that will update based on when card is read
  "Sue", "75", "2", "1", "00:00:00",
  "Ann", "70", "5", "3", "00:00:00",
  "Bob", "169", "7", "3", "00:00:00"
};

char daysOfTheWeek[7][12] =
{
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

void setup()
{
  Serial.begin(9600); // Initiate a serial communication
  SPI.begin();        // Initiate SPI bus
  mfrc522.PCD_Init(); // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set the initial date and time based on compilation timestamp
  DateTime now = rtc.now();
  printDateTime(now);
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  pinMode(8, OUTPUT);
  Serial.println("go to looopppppp");
}

void loop()
{
  DateTime now = rtc.now();
  digitalWrite(8, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  //  lcd.print(':');
  //  lcd.println(now.second());

  if ( now.hour() == 18 && now.minute() == 50)
  {
    digitalWrite(8, HIGH);
    int pinState = digitalRead(8);
    Serial.print(pinState);
  }
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    Serial.println("cannot read serial");
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  //Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B3 9B 04 1A" && now.hour() > 16)
  {
    r = 1;
  }
  else if (content.substring(1) == "83 17 E4 11" && now.hour() == 11)
  {
    r = 2;
  }
  else if (content.substring(1) == "63 6F D0 0D")
  {
    r = 3;
  }
  else if (content.substring(1) == "53 8D 8D F4") // master card
  {
    r = 4;
  }
  else
  {
    lcd.clear();
    lcd.print("Wrong Card");
    delay(1000);
    return;
  }
  readData(r);

  //  mfrc522.PICC_HaltA();
  //  mfrc522.PCD_StopCrypto1();
}

void readData(int c)
{
  DateTime now = rtc.now();
  int dataIndex;
  // Determine the index in myArray based on the case or identifier
  if (c == 1 || c == 2 || c == 3)
    dataIndex = 0;
  if (c == 4)
    dataIndex = 3;
  // Updates the array value for time
  sprintf(myArray[dataIndex][4], "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  Serial.print("Heres the data you requested:");
  Serial.println();
  displayData(dataIndex);
  delay(1000); // Delay to avoid multiple reads for the same card
}

void displayData(int dataIndex)
{
  Serial.println();
  if (dataIndex == 0)
  {
    digitalWrite(8, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Name:");
    lcd.print(myArray[r - 1][0]);
    lcd.print(" ");
    lcd.print("Age:");
    lcd.print(myArray[r - 1][1]);
    lcd.setCursor(0, 1);
    lcd.print("PillA:");
    lcd.print(myArray[r - 1][2]);
    lcd.print(" ");
    lcd.print("PillB:");
    lcd.print(myArray[r - 1][3]);
    delay(5000);
    Serial.println("Access Granted");
    lcd.clear();
    lcd.print("Dispensing");
    int X;
    for ( X = 0; X < atoi(myArray[r - 1][2]); X++)
    {
      Serial.print("Im in the loop");
      dispense(1);
      delay(500);
    }
    delay(5000);
    digitalWrite(8, HIGH);
    int pinState = digitalRead(8);
    Serial.println(pinState);
    

    //      int Y;
    //      for ( Y = 0; Y < atoi(myArray[r - 1][3]); Y++) // Instead row of the array and loop dispense function to output for the anount specidified within the array
    //      {
    //        dispense(2);
    //      }
  }
  if (dataIndex == 3)
  {
    lcd.clear();
    lcd.print(" Hello Nurse");

    Serial.println("Summary");
    for (int i = 0; i < numRows; i++)
    {
      for (int j = 0; j < numCols; j++)
      {
        Serial.print(myArray[i][j]);
        Serial.print("\t");  // Add a tab for better formatting
      }
      Serial.println();  // Move to the next line after printing each row
    }
    Serial.println("End");
  }
}

void printDateTime(DateTime dt)
{
  Serial.print(dt.day());
  Serial.print('/');
  Serial.print(dt.month());
  Serial.print('/');
  Serial.print(dt.year());
  Serial.print(" (");
  Serial.print(daysOfTheWeek[dt.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(dt.hour());
  Serial.print(':');
  Serial.print(dt.minute());
  Serial.print(':');
  Serial.println(dt.second());
}

void dispense(int number)
{
  char c;
  Servo1.attach(2);//connect pin 9 with the control line(the middle line of Servo)
  Servo2.attach(4);
  int IRPIN;
  Servo SERVOPIN;
  if (number == 1) {
    IRPIN = IR1_Pin;
    SERVOPIN = Servo1;
  } else {
    IRPIN = IR1_Pin;
    SERVOPIN = Servo2;
  }
  int cur = millis();
  int target = cur + 1000;
  int dir = true;
  while (!digitalRead(IRPIN))

  {
    cur = millis();
    if (dir) {
      SERVOPIN.write(((float)(target - cur) / 4.0)); // move servos to center position -> 60°
    } else {
      SERVOPIN.write(180 - ((float)(target - cur) / 4.0)); // move servos to center position -> 90°
    }
    if (cur > target) {
      dir = !dir;
      target = cur + 1000;
    }
  }
  Servo1.detach();
  Servo2.detach();
  SERVOPIN.detach();
  Serial.println("Done dispensing");
}
