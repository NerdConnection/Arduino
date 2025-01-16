int buzzerPin = 9;
int songLength = 16;

char notes[] = "cee egg dff abb";
int beats[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int tempo = 200;
void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int duration;

  for(int i = 0; i < songLength; i++){
    duration = beats[i] * tempo;

    if(notes[i] == ' '){
      delay(duration);
    }
    else{
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);
    }
    delay(tempo/10);
  }
}

int frequency(char note){
  int i;
  int notes = 8;
  char names[] = {'c','d','e','f','g','a','b','c'};
  int frequency[] = {262,294,330,349,392,440,494,523};
  
  for(i=0; i<notes; i++){
    if(name[i] == note){
      return(frequency[i]);
    };
  };
  return(0);
}