#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

const int numRows = 4;
const int numCols = 4;
const int coolingPin = 13;
const float tempThreshold = 5.0;
const float weightFactor = 0.2;

char PW[5] = {'1', '2', '3', 'A', 'B'};
char enteredPW[5];
int enteredIndex = 0;
char keys[numRows][numCols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
int rowPins[] = {9, 8, 7, 6};
int colPins[] = {5, 4, 3, 2};
int TempSensor = A1;
int FSRsensor = A2;
Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(coolingPin, OUTPUT);

  for (int i = 0; i < numRows; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < numCols; i++) { 
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  myservo.attach(10);
  myservo.write(0);
  lcd.init();
  lcd.backlight();
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypadRead();
  if (key) {
    handlePasswordInput(key);
  }
  float val = readTempAndFSR();
  // 온도 제어 로직
  if (val >= tempThreshold) { 
    digitalWrite(coolingPin, HIGH); 
  } else {
    digitalWrite(coolingPin, LOW); 
  }
}

float readTempAndFSR() {
  int FSRReading = analogRead(FSRsensor);
  float voltage = analogRead(TempSensor) * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100;

  // 무게 보정 값 계산
  float weightAdjustedTemp = temperatureC - FSRReading * weightFactor;

  return weightAdjustedTemp;
}

float fmap(long x, long in_min, long in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}


void handlePasswordInput(char key) {
  if (enteredIndex < sizeof(PW) / sizeof(PW[0])) {
    enteredPW[enteredIndex] = key;
    enteredIndex++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
    lcd.setCursor(0, 1);
    for (int i = 0; i < enteredIndex; i++) {
      lcd.print("*");
    }
  }

  if (enteredIndex == sizeof(PW) / sizeof(PW[0])) {
    if (isPasswordCorrect()) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Success!");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Put things inside");
      lcd.setCursor(0, 1);
      lcd.print("Press 1 to close");

      ServoForDoorOpen();

      bool doorOpen = true;
      while (doorOpen) {
        char closeKey = keypadRead();
        if (closeKey == '1') {
          ServoForDoorClose();
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Door closing");
          delay(2500);
          lcd.clear();
          doorOpen = false;
        }
      }

      resetPasswordInput();

    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Fail. Try again.");
      delay(1000);
    }
    resetPasswordInput();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
  }
}

char keypadRead() {
  char key = 0;
  for (int i = 0; i < numCols; i++) {
    digitalWrite(colPins[i], LOW);
    for (int j = 0; j < numRows; j++) {
      if (digitalRead(rowPins[j]) == LOW) {
        delay(50); 
        while (digitalRead(rowPins[j]) == LOW);
        key = keys[j][i];
      }
    }
    digitalWrite(colPins[i], HIGH);
  }
  return key;
}

bool isPasswordCorrect() {
  for (int i = 0; i < sizeof(PW) / sizeof(PW[0]); i++) {
    if (enteredPW[i] != PW[i]) {
      return false;
    }
  }
  return true;
}

void resetPasswordInput() {
  enteredIndex = 0;
  for (int i = 0; i < sizeof(PW) / sizeof(PW[0]); i++) {
    enteredPW[i] = '\0';
  }
}

void ServoForDoorOpen() {
  for (int i = 0; i <= 180; i += 20) {
    myservo.write(i);
    delay(100);
  }
}

void ServoForDoorClose() {
  for (int i = 180; i >= 0; i -= 20) {
    myservo.write(i);
    delay(100);
  }
}
