#include <Servo.h>

Servo motor1;

int  servoMotorPin = 9;
int potentioMeterPin = 0;
int motorAngle;
int motorAngleOld;

void setup() {
  // put your setup code here, to run once:
  motor1.attach(servoMotorPin,600,2400);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potentioMeter = analogRead(potentioMeterPin);
  motorAngle = map(potentioMeter,0,1023,0,180);
  motor1.write(motorAngle);

  if(motorAngle != motorAngleOld){
    Serial.print("Servo Motro Angle is: ");
    Serial.println(motorAngle);
  }

  motorAngleOld = motorAngle;
  delay(20);
}
