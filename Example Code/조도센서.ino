#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16,2);
const int CdSPin = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();

  lcd.print("ex 6.2");
  lcd.setCursor(0,1);
  lcd.print("CDS Cell Test");

  delay(3000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ADC : ");
  lcd.setCursor(0,1);
  lcd.print("Illuminance");
  lcd.setCursor(15,1);
  lcd.print("%");

}

void loop() {
  // put your main code here, to run repeatedly:
  int adcValue;
  int illuminance;

  adcValue = analogRead(CdSPin);
  illuminance = map(adcValue,0 ,1023,100,0);

  lcd.setCursor(9,0);
  lcd.print("     ");
  lcd.setCursor(9,0);
  lcd.print(adcValue);

  lcd.setCursor(13,1);
  lcd.print("     ");

  lcd.setCursor(12,1);
  lcd.print(illuminance);

  delay(1000);
}
