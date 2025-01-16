#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
const int waterLevelPin = 0;
const int waterFullAdcValue = 600;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.print("ex 6.4");
  lcd.setCursor(0, 1);
  lcd.print("water Level");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ADC : ");
  lcd.setCursor(0,1);
  lcd.print("Water Level");
  lcd.setCursor(15,1);
  lcd.print("%");
}

void loop() {
  // put your main code here, to run repeatedly:
  int adcValue;
  int waterLevel;

  adcValue = analogRead(waterLevelPin);
  waterLevel = map(adcValue, 0, waterFullAdcValue, 0, 100);

  lcd.setCursor(9,0);
  lcd.print("     ");
  lcd.setCursor(9,0);
  lcd.print(adcValue);

  lcd.setCursor(13,1);
  lcd.print("     ");
  lcd.setCursor(12,1);
  lcd.print(waterLevel);
}
