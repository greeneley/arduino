
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
byte ledStatus;


static unsigned long GREEN_TIME = 39;
static unsigned long YELLOW_TIME = 3;
static unsigned long RED_TIME = 42;

const int program[3] = {
 GREEN_TIME,
 YELLOW_TIME,
 RED_TIME
};
static unsigned long point = program[0];
int turn = 0;
const int Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  


  
}

void HienThiLed7Doan(unsigned long giatri, byte soled = 2, byte ledStatus = 00000001) {
  
  
  byte *array = new byte[soled];
  for (byte i = 0; i < soled; i++) {
    array[i] = (byte)(giatri % 10UL);
    giatri = (unsigned long)(giatri / 10UL);
  }
  digitalWrite(latchPin, LOW);
    
  shiftOut(dataPin, clockPin, MSBFIRST, ledStatus);
  for (int i = soled - 1; i >= 0; i--) {
    shiftOut(dataPin, clockPin, MSBFIRST, Seg[array[i]]);
  }
  
  digitalWrite(latchPin, HIGH);
  free(array);
}


void loop() {
  // put your main code here, to run repeatedly:    
  
  
  if (turn == 0){
   ledStatus = 100; //GREEN  
  } else if (turn == 1){
   ledStatus = 10; // GREEN
  } else {
    ledStatus = 001; //YELLOW
  }
  Serial.println(point);
  HienThiLed7Doan(point, 2, ledStatus);
  point = point - 1;
  if (point == -1){
    turn = (turn + 1) % 3;
    point = program[turn];
  }
  delay(1000);
}
