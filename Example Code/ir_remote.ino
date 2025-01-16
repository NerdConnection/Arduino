#include <IRremote.h>

int irPin = 11;
IRrecv irrecv(irPin);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);  
}

void loop() {
  if(irrecv.decode(&results)){
    if(results.value != 0xFFFFFFFF){
      Serial.print("Received Code is ");
      Serial.println(results.value, HEX);
    };
    irrecv.resume(); 
  }
}
