
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

const int Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000011,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void HienThiLed7Doan(unsigned long giatri, byte soled = 2) {
  byte *array = new byte[soled];
  for (byte i = 0; i < soled; i++) {
    array[i] = (byte)(giatri % 10UL);
    giatri = (unsigned long)(giatri / 10UL);
  }
  digitalWrite(latchPin, LOW);
  for (int i = soled - 1; i >= 0; i--) {
    shiftOut(dataPin, clockPin, MSBFIRST, Seg[array[i]]);
  }
  digitalWrite(latchPin, HIGH);
  free(array);
}



void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long point = 0;
  HienThiLed7Doan(point, 2);
  point = (point + 1) % 10;
  delay(500);
}
