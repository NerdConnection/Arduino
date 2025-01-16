const int ledPin = 13;
int blinkNumber = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char val = Serial.read();
    if(isDigit(val)){
      blinkNumber = (val - '0');
    }
  }

  for(char i = 0; i < blinkNumber; i++){
    digitalWrite(ledPin, HIGH);
    delay(3000);
    digitalWrite(ledPin, LOW);
    delay(3000);
  }
}
