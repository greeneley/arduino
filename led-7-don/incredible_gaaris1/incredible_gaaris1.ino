// C++ code
//

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;


byte ledStatus;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop()
{
ledStatus = 0 ;
  for ( int i = 0; i < 8; i++){
  	ledStatus = (ledStatus << 1) | 00000001;
  	digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, ledStatus);
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
  for (int i = 0; i < 8; i++){
  	ledStatus <<= 1; // ledstatus = ledstatus << 1
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, ledStatus);
    digitalWrite(latchPin,HIGH);
    delay(500);
  }
}
