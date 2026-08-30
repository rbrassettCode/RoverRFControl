//Pin locations for Potentiometers on Controller
const int leftDialPin = A0;
const int rightDialPin = A1;
const int controlUpDown = A2;
const int controlLeftRight = A3;

//Pin locations for LEDs on controller
const int ledPinRight = 5;
const int ledPinLeft = 6;

//Pin locations for pushbutton/switches
const int s1Btn = 4;
const int s2Btn = 3;
const int s3Btn = 2;
const int controlBtn = 7;

//constant min and max to make universal
const int potPinHigh = 1023;
const int potPinLow = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //define all outputs
  pinMode(ledPinRight, OUTPUT);
  pinMode(ledPinLeft, OUTPUT);

  //deine all intputs
  pinMode(s1Btn, INPUT);
  pinMode(s2Btn, INPUT);
  pinMode(s3Btn, INPUT);
  pinMode(controlBtn, INPUT);


}

void serialPrintf(const char *fmt, ...) {
  char buf[128];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);
  Serial.println(buf);
}

struct ControllerReadings {
  int leftDial;
  int rightDial;
  int controlUpDown;
  int controlLeftRight;
  int s1;
  int s2;
  int s3;
  int controlsBtn;
  
};
//Struct to own all analog read data
ControllerReadings r;

void readAllAnalog() {
  r.leftDial         = analogRead(leftDialPin);
  delay(1);
  r.rightDial        = analogRead(rightDialPin);
  delay(1);
  r.controlUpDown    = analogRead(controlUpDown);
  delay(1);
  r.controlLeftRight = analogRead(controlLeftRight);
  delay(1);

}

void updateLed() {
  analogWrite(ledPinRight, map(r.rightDial, potPinLow, potPinHigh, 0, 255));
  delay(1);
  analogWrite(ledPinLeft, map(r.leftDial, potPinLow, potPinHigh, 0, 255));
  delay(1);
}

void readButton() {
  r.s1 = digitalRead(s1Btn);
  delay(1);
  r.s2 = digitalRead(s2Btn);
  delay(1);
  r.s3 = digitalRead(s3Btn);
  delay(1);
  r.controlsBtn = digitalRead(controlBtn);
  delay(1);
}

void loop() {
  readAllAnalog();
  delay(1);
  readButton();
  delay(1);
  serialPrintf("leftPin: %i, rightPin: %i, updown: %i, leftright: %i, s1: %i, s2: %i, s3: %i, controlBtn: %i.", r.leftDial, r.rightDial, r.controlUpDown, r.controlLeftRight, r.s1, r.s2, r.s3, r.controlsBtn);
  updateLed();
  delay(1);

}
