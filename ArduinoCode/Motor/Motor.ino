/* Adafruit Arduino - Lesson 15. Bi-directional Motor */
#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 

// for use in curr coords
#define STEP_WAIT 10

struct motor { int pin1, pin2, pin3, pin4; } typedef motor; 
struct motor * UD;
struct motor * LR;		// vertical and horizontal motor controllers

int step_number = 0;
int REVERSE = 0;		// for use with U/D/L/R to make things easier
int FORWARD	= 1;

int incoming[2];

// METHOD DECLARATIONS //

void U();
void D();
void L();
void R();

////////////////////////

// QUEUE FUNCTIONS AND STRUCTS // // TAKEN FROM GEEKS FOR GEEKS //

// A structure to represent a queue 
struct Queue 
{ 
	int front, rear, size; 
	unsigned capacity; 
	int* array; 
}; 
  
// function to create a queue of given capacity.  
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity) 
{ 
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
	queue->capacity = capacity; 
	queue->front = queue->size = 0;  
	queue->rear = capacity - 1;  // This is important, see the enqueue 
	queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
	return queue; 
} 
  
// Queue is full when size becomes equal to the capacity  
int isFull(struct Queue* queue) 
{  return (queue->size == queue->capacity);  } 
  
// Queue is empty when size is 0 
int isEmpty(struct Queue* queue) 
{  return (queue->size == 0); } 
  
// Function to add an item to the queue.   
// It changes rear and size 
void enqueue(struct Queue* queue, int item) 
{ 
	if (isFull(queue)) 
		return; 
	queue->rear = (queue->rear + 1)%queue->capacity; 
	queue->array[queue->rear] = item; 
	queue->size = queue->size + 1; 
	printf("%d enqueued to queue\n", item); 
} 
  
// Function to remove an item from queue.  
// It changes front and size 
int dequeue(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	int item = queue->array[queue->front]; 
	queue->front = (queue->front + 1)%queue->capacity; 
	queue->size = queue->size - 1; 
	return item; 
} 
  
// Function to get front of queue 
int front(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	return queue->array[queue->front]; 
} 
  
// Function to get rear of queue 
int rear(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	return queue->array[queue->rear]; 
} 

////////////////////////////////

struct Queue* instructionQueue

void setup() {

	instructionQueue = createQueue(1000);

	UD = (motor*)malloc(sizeof(struct motor));
	LR = (motor*)malloc(sizeof(struct motor));

	UD->pin1 = 12;
	UD->pin2 = 11; 
	UD->pin3 = 10;
	UD->pin4 = 9;

	LR->pin1 = 6;
	LR->pin2 = 5;
	LR->pin3 = 4;
	LR->pin4 = 3;

	pinMode(UD->pin1, OUTPUT);
	pinMode(UD->pin2, OUTPUT);
	pinMode(UD->pin3, OUTPUT);
	pinMode(UD->pin4, OUTPUT);

	pinMode(LR->pin1, OUTPUT);
	pinMode(LR->pin2, OUTPUT);
	pinMode(LR->pin3, OUTPUT);
	pinMode(LR->pin4, OUTPUT);

	Serial.begin(9600);

}
 
void loop() {

	while(Serial.available() >= 1){
		if (!isEmpty(instructionQueue)){
			int nextInstruction = dequeue(instructionQueue);
			switch(nextInstruction){
				case 0:
					U();
					break;
				case 1:
					D();
					break;
				case 2:
					L();
					break;
				case 3:
					R();
					break;
			}
		}
		for (int i = 0; i < 1; i++){
			incoming[i] = Serial.read();
		}
		if (!isFull(instructionQueue))
			enqueue(instructionQueue, incoming[0]);
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
				break;
		} 

	}

	step_number++;

	if (step_number > 3) {
		step_number = 0;
	}

}

// Direction Functions //
void U() {
	OneStep(UD, FORWARD);
	curr_coords[Y]++;
	delay(STEP_WAIT);
}

void D() {
	OneStep(UD, REVERSE);
	curr_coords[Y]--;
	delay(STEP_WAIT);
}

void L() {
	OneStep(LR, REVERSE);
	curr_coords[X]--;
	delay(STEP_WAIT);
}

void R() {
	OneStep(LR, FORWARD);
	curr_coords[X]++;
	delay(STEP_WAIT);
}
////////////////

