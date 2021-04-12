/*
  This is my rendition of a rectangle controller, based on the work of Crane1195 (https://github.com/Crane1195/).
  It utilises a Fork Mheironimus Arduino Joystick library byJas2o (https://github.com/Jas2o/Leonardo-Switch-Controller).
  This Code features a Dpad/Analog Stick Toggle (Press MOD and HOME and the same time), as well as an on the fly programmable Button,
  (Press Mod + the button you want it to be. Only works with A,B,X,Y,L,R,ZL and ZR).
*/
#include "Joystick.h"

int LEFT = 0;
int DOWN = 1;
int RIGHT = 2;
int UP = 3;

int SELECT = 5;
int START = 6;
int HOME = 7;
int CAPTURE = 8;

int X = 10;
int A = 11;
int B = 12;
int Y = 13;

int L = A0;
int R = A1;
int ZL = A2;
int ZR = A3;

int MOD = A4;

int EXTRA = A5;

char extraButton = 'E';

bool isMOD = false;

uint8_t controlX = 2;   //apparently, when controlX and controlY are 0, the stick drifts to the top left. setting the to 2 fixes that problem. might be different at your build.
uint8_t controlY = 2;

void setup() {

  pinMode(L, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  pinMode(SELECT, INPUT_PULLUP);
  pinMode(HOME, INPUT_PULLUP);
  pinMode(CAPTURE, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(X, INPUT_PULLUP);
  pinMode(ZL, INPUT_PULLUP);
  pinMode(ZR, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(R, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(A, INPUT_PULLUP);
  pinMode(MOD, INPUT_PULLUP);
  pinMode(EXTRA, INPUT_PULLUP);

  Joystick.begin(false);

}

void loop()
{
  bool isL           = (digitalRead(L) == LOW);
  bool isLEFT        = (digitalRead(LEFT) == LOW);
  bool isDOWN        = (digitalRead(DOWN) == LOW);
  bool isRIGHT       = (digitalRead(RIGHT) == LOW);
  bool isSTART       = (digitalRead(START) == LOW);
  bool isSELECT      = (digitalRead(SELECT) == LOW);
  bool isHOME        = (digitalRead(HOME) == LOW);
  bool isCAPTURE     = (digitalRead(CAPTURE) == LOW);
  bool isB           = (digitalRead(B) == LOW);
  bool isX           = (digitalRead(X) == LOW);
  bool isZR          = (digitalRead(ZR) == LOW);
  bool isZL          = (digitalRead(ZL) == LOW);
  bool isUP          = (digitalRead(UP) == LOW);
  bool isR           = (digitalRead(R) == LOW);
  bool isY           = (digitalRead(Y) == LOW);
  bool isA           = (digitalRead(A) == LOW);

  bool isEXTRA       = (digitalRead(EXTRA) == LOW);

  bool mod           = (digitalRead(MOD) == LOW);

  // this is the logic for the dpad/analog toggle.
  if (mod && isHOME) {
    if (isMOD == false)
      isMOD = true;
    else
      isMOD = false;
  }
  //this is the logic for the extra programmable button
  else if (mod && isA)
    extraButton = 'A';
  else if (mod && isB)
    extraButton = 'B';
  else if (mod && isX)
    extraButton = 'X';
  else if (mod && isY)
    extraButton = 'Y';
  else if (mod && isL)
    extraButton = 'L';
  else if (mod && isR)
    extraButton = 'R';
  else if (mod && isZL)
    extraButton = 'J';
  else if (mod && isZR)
    extraButton = 'Z';

  if (isEXTRA) {
    if (extraButton == 'A')
      isA = true;
    else if (extraButton == 'B')
      isB = true;
    else if (extraButton == 'X')
      isX = true;
    else if (extraButton == 'Y')
      isY = true;
    else if (extraButton == 'L')
      isL = true;
    else if (extraButton == 'R')
      isR = true;
    else if (extraButton == 'J')
      isZL = true;
    else if (extraButton == 'Z')
      isZR = true;
  }

  if (isUP)
    controlY = -127;
  else if (isDOWN)
    controlY = 127;
  else
    controlY = 2;

  if (isLEFT)
    controlX = -127;
  else if (isRIGHT)
    controlX = 127;
  else
    controlX = 2;

  //Face Buttons
  Joystick.setButton(2, isA);
  Joystick.setButton(1, isB);
  Joystick.setButton(3, isX);
  Joystick.setButton(0, isY);

  //Shoulder Buttons
  Joystick.setButton(4, isL);
  Joystick.setButton(5, isR);
  Joystick.setButton(6, isZL);
  Joystick.setButton(7, isZR);

  //Menu Buttons
  Joystick.setButton(9, isSTART);
  Joystick.setButton(8, isSELECT);
  Joystick.setButton(12, isHOME);
  Joystick.setButton(13, isCAPTURE);

  if (isMOD == false) {
    Joystick.setXAxis(2);
    Joystick.setYAxis(2);

    if (isUP) {
      if (isLEFT)
        Joystick.setHatSwitch(7);
      else if (isRIGHT)
        Joystick.setHatSwitch(1);
      else
        Joystick.setHatSwitch(0);
    } else if (isDOWN) {
      if (isLEFT)
        Joystick.setHatSwitch(5);
      else if (isRIGHT)
        Joystick.setHatSwitch(3);
      else
        Joystick.setHatSwitch(4);
    } else if (isRIGHT)
      Joystick.setHatSwitch(2);
    else if (isLEFT)
      Joystick.setHatSwitch(6);
    else
      Joystick.setHatSwitch(-1);
  } else {
    Joystick.setXAxis(controlX);
    Joystick.setYAxis(controlY);
  }

  Joystick.sendState();
  delay(1);
}
