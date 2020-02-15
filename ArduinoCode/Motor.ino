/* Adafruit Arduino - Lesson 15. Bi-directional Motor */

#include <math.h>

struct motor { int pin1, pin2, pin3, pin4; } typedef motor; 
struct motor * UD, LR; 		// vertical and horizontal motor controllers
int switchPin 		= 7;	// keep track of switch pin number
int potPin 			= 0;	// keep track of pot pin number 
int curr_coords [] 	= {0,0}	// keeps track of etchasketch current point, starts at origin in bottom left
int X 				= 0;	// for use with curr_coords to make things less confusing
int Y 				= 1;	//
boolean REVERSE 	= FALSE;// for use with U/D/L/R to make things easier
boolean FORWARD 	= TRUE;	//

void setup() {

	pinMode(UD->pin1, OUTPUT);
	pinMode(UD->pin2, OUTPUT);
	pinMode(UD->pin3, OUTPUT);
	pinMode(UD->pin4, OUTPUT);
	pinMode(LR->pin1, OUTPUT);
	pinMode(LR->pin2, OUTPUT);
	pinMode(LR->pin3, OUTPUT);
	pinMode(LR->pin4, OUTPUT);
	UD->pin1 = 12;
	UD->pin1 = 11; 
	UD->pin1 = 10;
	UD->pin1 = 9;
	LR->pin1 = 6;
	LR->pin1 = 5;
	LR->pin1 = 4;
	LR->pin1 = 3;


 	Serial.begin(9600);

}
 
void loop() {

	// if at least two incoming bytes, read as next coords and draw
	if (Serial.available() >= 2) {
		drawLineFromCurrCoords(Serial.read(), Serial.read());
	}

}

// rotates motor by "one step"
void OneStep(motor * m, bool dir) {
  
  if (dir) {

    switch(step_number){

      case 0:
      digitalWrite(m->pin1, HIGH);
      digitalWrite(m->pin2, LOW);
      digitalWrite(m->pin3, LOW);
      digitalWrite(m->pin4, LOW);
      break;
      case 1:
      digitalWrite(m->pin1, LOW);
      digitalWrite(m->pin2, HIGH);
      digitalWrite(m->pin3, LOW);
      digitalWrite(m->pin4, LOW);
      break;
      case 2:
      digitalWrite(m->pin1, LOW);
      digitalWrite(m->pin2, LOW);
      digitalWrite(m->pin3, HIGH);
      digitalWrite(m->pin4, LOW);
      break;
      case 3:
      digitalWrite(m->pin1, LOW);
      digitalWrite(m->pin2, LOW);
      digitalWrite(m->pin3, LOW);
      digitalWrite(m->pin4, HIGH);
      break;
    } 

  } else {

    switch(step_number) {

      case 0:
      digitalWrite(m->pin1, LOW);
      digitalWrite(m->pin2, LOW);
      digitalWrite(m->pin3, LOW);
      digitalWrite(m->pin4, HIGH);
      break;
      case 1:
      digitalWrite(m->pin1, LOW);
      digitalWrite(m->pin2, LOW);
      digitalWrite(m->pin3, HIGH);
      digitalWrite(m->pin4, LOW);
      break;
      case 2:
      digitalWrite(m->pin1, LOW);
      digitalWrite(m->pin2, HIGH);
      digitalWrite(m->pin3, LOW);
      digitalWrite(m->pin4, LOW);
      break;
      case 3:
      digitalWrite(m->pin1, HIGH);
      digitalWrite(m->pin2, LOW);
      digitalWrite(m->pin3, LOW);
      digitalWrite(m->pin4, LOW);
 
    } 

  }

  step_number++;

  if (step_number > 3) {
    step_number = 0;
  }

}

// directions //
void U() {
  OneStep(UD, FORWARD);
  curr_coords[Y]++;
}

void D() {
  OneStep(UD, REVERSE);
  curr_coords[Y]--;
}

void L() {
  OneStep(LR, REVERSE);
  curr_coords[X]--;
}

void R() {
  OneStep(LR, FORWARD);
  curr_coords[X]++;
}
////////////////


void drawLineFromCurrCoords(int x, int y) {

	// get distance of new coords from current 
	int dx = x - curr_coords[X];
	int dy = y - curr_coords[Y];

	// figure out which direction we are moving in from current position
	void (*UDdirec)();
	void (*LRdirec)();

	if (dx >= 0) { LRdirec = &R; } 
	else 		 { LRdirec = &L; }

	if (dy >= 0) { UDdirec = &U; }
	else 		 { UDdirec = &D; }

	while (!(curr_coords[X] == x && curr_coords[Y] == y)) {

		dx = abs(x - curr_coords[X]);
		dy = abs(y - curr_coords[Y]);
		int p = 2 * dy - dx;

		if      (dx == 0) { *UDdirec(); } // if nowhere else to go sideways
		else if (dy == 0) { *LRdirec(); } // if nowhere else to go vertically
		else { // Bresenham Line-Drawing Algorithm

			if (p < 0) {
				*LRdirec();
				p = p + 2 * dy;
			} else {
				*LRdirec();
				*UDdirec();
				p = p + 2 * (dy - dx);
			}

		}

	}

}
