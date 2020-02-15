/*
Adafruit Arduino - Lesson 15. Bi-directional Motor
*/

#include <math.h>

// temporary //
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
///////////

int switchPin = 7;
int potPin = 0;
boolean REVERSE = TRUE, FORWARD = FALSE;
struct motor * UD, LR;
int SPEED = 255;
int curr_coords [] = {0,0}
int X = 0, Y = 1;

struct motor {

	int enable;
	int in1;
	int in2;

} typedef motor;

void setup() {

	pinMode(UD->in1, OUTPUT);
	pinMode(UD->in2, OUTPUT);
	pinMode(UD->enable, OUTPUT);
	pinMode(LR->in1, OUTPUT);
	pinMode(LR->in2, OUTPUT);
	pinMode(LR->enable, OUTPUT);

 	Serial.begin(9600);

}
 
void loop() {

	// if at least two incoming bytes, read as next coords and draw
	if (Serial.available() >= 2) {
		drawLineFromCurrCoords(Serial.read(), Serial.read());
	}

}

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


// directions
void U() {
  setMotor(UD, SPEED, FORWARD);
  stopMotor(UD);
  curr_coords[Y]++;
}

void D() {
  setMotor(UD, SPEED, REVERSE);
  stopMotor(UD);
  curr_coords[Y]--;
}

void L() {
  setMotor(LR, SPEED, FORWARD);
  stopMotor(LR);
  curr_coords[X]--;
}

void R() {
  setMotor(LR, SPEED, REVERSE);
  stopMotor(LR);
  curr_coords[X]++;
}
//

//
void stopMotor(motor * m) {
  setMotor(m, 0, TRUE);
}
 
void setMotor(motor * m, int speed, boolean reverse) {
  analogWrite(enablePin, speed);
  digitalWrite(m->in1, ! reverse);
  digitalWrite(m->in2, reverse);
}