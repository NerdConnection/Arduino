#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <Servo.h>

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char trigPin = 13;
const char echoPin = 12;

int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;

Stepper stepper(600, motorPin1, motorPin3, motorPin2, motorPin4);

int pulseWidth;
int distance;
int distanceOld;

void setup() {
  // 통신설정
  Serial.begin(9600);
  
  // 모터 출력으로 설정
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // LCD 초기설정
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Arduino LCD");
  lcd.setCursor(0, 1);
  lcd.print("Welcome");
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
  delay(250);
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
  delay(250);
  lcd.clear();
  lcd.setCursor(0, 0);

  // 초음파 초기 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  stepper.setSpeed(60);

  // 서보모터 : 초기설정 (차량차단기 내려진 상태로 초기 설정)
  myServo.attach(7);
  myServo.write(70);
  delay(1000);
}

void loop() {
  // 초음파 **********************************************************************
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 거리 계산
  pulseWidth = pulseIn(echoPin, HIGH);
  distance = pulseWidth / 58;


  // case 1 : 차량 감지( 차량이 적절한 거리에 있을 때)
  if (distance <= 10 && distance >= 2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("take a ticket");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.print(" CM  ");
    stepper.step(0);

    // 티켓 가져가는 시간
    delay(3000);
    // 차단기 올리고 3초 대기후 내리기
    myServo.write(180);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Good Bye");
    delay(3000);
    myServo.write(70);
    
    

  // case 2 : 차량 감지( 차량이 적절한 거리에 있지 않을 때)
  } else if (distance > 10 && distance <= 30) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Adjust location");
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.print(" CM  ");

    // 스텝모터를 움직이기
    // 스텝모터 1 바퀴당 2cm 이동한다고 가정
    float moveDistance = (distance - 10)/2.0;
    lcd.print(moveDistance);
    lcd.print(" circles ");
    
    // 위치 조정
    stepper.step(moveDistance*2048);
    // 사용자가 티켓 가져가기 3초 대기
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Take ticket");
    delay(3000);
    
    // 차단기 올리고 3초 대기후 내리기
    myServo.write(180);
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Good Bye");
    myServo.write(70);
    stepper.step(moveDistance*(-2048)); // 원상태로 복귀


  // case 3 : 차량이 감지되지 않을 때 ( 30cm 초과)
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No vehicles");
    lcd.setCursor(0, 1);
    lcd.print("detected");
    Serial.print(distance);
    Serial.println(" CM  ");
    stepper.step(0);
  }

  distanceOld = distance;
  delay(4000);
}