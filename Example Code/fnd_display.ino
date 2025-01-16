const byte number[10] = {
  B00111111,
  B00000110,
  B01011011, 
  B01001111, 
  B01100110, 
  B01101101, 
  B01111101, 
  B00000111,
  B01111111,
  B01101111,
};

void setup() {
  // put your setup code here, to run once:
  for(int i = 2; i<= 9 ; ++i){
    pinMode(i,OUTPUT);
  };
  digitalWrite(9,LOW);
}

void loop() {
  for(int k =0 ; k<=9;++k){
    fndDisplay(k);
    delay(1000);
  };
}

void fndDisplay(int displayValue){
  boolean bitValue;

  for(int i=2;i<=9;++i){
    digitalWrite(i, LOW);
  };

  for(int i=0;i<=7;++i){
    bitValue = bitRead(number[displayValue], i);
    digitalWrite(i+2, bitValue);
  }
}