#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
const int xAxisPin = 0;
const int yAxisPin = 1;
const int zAxisPin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(zAxisPin, INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  lcd.print("ex 6.5");
  lcd.setCursor(0, 1);
  lcd.print("JoyStick");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("X : ");
  lcd.setCursor(0,1);
  lcd.print("Y : ");
  lcd.setCursor(15,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  int xValue = analogRead(xAxisPin);
  int yValue = analogRead(yAxisPin);
  int zValue = digitalRead(zAxisPin);

  int xDisplay = map(xValue,0,1023,6,15);
  int yDisplay = map(yValue,0,1023,6,15);
  
  lcd.setCursor(2,0);
  lcd.print("     ");
  lcd.setCursor(2,0);
  lcd.print(xValue);

  lcd.setCursor(xDisplay,0);
  lcd.print("|");
  lcd.setCursor(2,1);
  lcd.print("     ");
  lcd.setCursor(2,1);
  lcd.print(yValue);
  lcd.setCursor(yDisplay,1);
  lcd.print("|");

  if(zValue == LOW){
    lcd.noBacklight();
    delay(300);
    lcd.backlight();
    }
    delay(100);
}

