// C++ code
//

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

const int HC595_COUNT = 2;
byte ledStatus[HC595_COUNT] = {0};

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}


void fillValueToArray(byte value) {
  for (int i = 0; i < HC595_COUNT; i += 1) {
    ledStatus[i] = value;
  }
}

void shiftOutHC595(int dataPin, int clockPin, byte ledStatus[]) {
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < HC595_COUNT; i++) {
    shiftOut(dataPin, clockPin, LSBFIRST, ledStatus[i]);
  }
  digitalWrite(latchPin, HIGH);
}
MSBFIRST
void loop()
{

  fillValueToArray(0);
  
  for (int i = 0; i < HC595_COUNT; i++) {
    for (byte j = 0; j < 8; j++) {
      ledStatus[i] = (ledStatus[i] << 1) | 1;
      shiftOutHC595(dataPin, clockPin, ledStatus);
      delay(500);
    }
  }

  for (int i = 0; i < HC595_COUNT; i++){
    for (byte j=0; j < 8; j++){
      ledStatus[i] <<=1;
      shiftOutHC595(dataPin, clockPin, ledStatus);
      delay(500);
    }
  }

}
