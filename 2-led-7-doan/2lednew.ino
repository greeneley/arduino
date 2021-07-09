
int latchPin_EW = 8;
int clockPin_EW = 12;
int dataPin_EW = 11;


int latchPin_NS = 2;
int clockPin_NS = 7;
int dataPin_NS = 5;

byte ledStatus_EW;
byte ledStatus_NS;


static unsigned long GREEN_TIME = 39;
static unsigned long YELLOW_TIME = 3;
static unsigned long RED_TIME = 42;

const int program[3] = {
  GREEN_TIME,
  YELLOW_TIME,
  RED_TIME
};

int turn_EW = 0;
int turn_NS = 2;
static unsigned long point_EW = program[turn_EW];
static unsigned long point_NS = program[turn_NS];


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
  pinMode(latchPin_EW, OUTPUT);
  pinMode(clockPin_EW, OUTPUT);
  pinMode(dataPin_EW, OUTPUT);

  pinMode(latchPin_NS, OUTPUT);
  pinMode(clockPin_NS, OUTPUT);
  pinMode(dataPin_NS, OUTPUT);
  // set all lights off
  all_off();
}


void all_off() {

  digitalWrite(latchPin_EW, LOW);
  digitalWrite(clockPin_EW, LOW);
  digitalWrite(dataPin_EW, LOW);

  digitalWrite(latchPin_NS, LOW);
  digitalWrite(clockPin_NS, LOW);
  digitalWrite(dataPin_NS, LOW);
}



void on_EW(unsigned long giatri, byte soled = 2, byte ledStatus = 00000001) {

  byte *array = new byte[soled];
  for (byte i = 0; i < soled; i++) {
    array[i] = (byte)(giatri % 10UL);
    giatri = (unsigned long)(giatri / 10UL);
  }
  digitalWrite(latchPin_EW, LOW);

  shiftOut(dataPin_EW, clockPin_EW, MSBFIRST, ledStatus);
  for (int i = soled - 1; i >= 0; i--) {
    shiftOut(dataPin_EW, clockPin_EW, MSBFIRST, Seg[array[i]]);
  }

  digitalWrite(latchPin_EW, HIGH);
  free(array);
}

void on_NS(unsigned long giatri, byte soled = 2, byte ledStatus = 00000001) {

  byte *array = new byte[soled];
  for (byte i = 0; i < soled; i++) {
    array[i] = (byte)(giatri % 10UL);
    giatri = (unsigned long)(giatri / 10UL);
  }
  digitalWrite(latchPin_NS, LOW);

  shiftOut(dataPin_NS, clockPin_NS, MSBFIRST, ledStatus);
  for (int i = soled - 1; i >= 0; i--) {
    shiftOut(dataPin_NS, clockPin_NS, MSBFIRST, Seg[array[i]]);
  }

  digitalWrite(latchPin_NS, HIGH);
  free(array);
}


void loop() {
  // put your main code here, to run repeatedly:

  if (turn_EW == 0) {
    ledStatus_EW = 100; //GREEN
  } else if (turn_EW == 1) {
    ledStatus_EW = 10; // GREEN
  } else {
    ledStatus_EW = 001; //YELLOW
  }

  if (turn_NS == 0) {
    ledStatus_NS = 100; //GREEN
  } else if (turn_NS == 1) {
    ledStatus_NS = 10; // GREEN
  } else {
    ledStatus_NS = 001; //YELLOW
  }
  //  ledStatus_EW = 111;
  //  ledStatus_NS = 111;
  //  Serial.println(point);
  on_EW(point_EW, 2, ledStatus_EW);
  on_NS(point_NS, 2, ledStatus_NS);

  point_EW = point_EW - 1;
  point_NS = point_NS - 1;

  if (point_EW == -1) {
    turn_EW = (turn_EW + 1) % 3;
    point_EW = program[turn_EW];
  }

  if (point_NS == -1) {
    turn_NS = (turn_NS + 1) % 3;
    point_NS = program[turn_NS];
  }
  delay(1000);
}
