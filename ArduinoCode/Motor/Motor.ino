/* Adafruit Arduino - Lesson 15. Bi-directional Motor */
#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 

// for use in curr coords

struct motor { int pin1, pin2, pin3, pin4, step_number = 0; } typedef motor; 
struct motor * UD;
struct motor * LR;    // vertical and horizontal motor controllers

int step_number = 0;
int REVERSE = 1;    // for use with U/D/L/R to make things easier
int FORWARD = 0;

int incoming[2];

// Arduino joystick pin numbers / enable
const int Y_pin = A0; // analog pin connected to Y output
const int X_pin = A1; // analog pin connected to X output
const boolean joystick_enabled = 1;

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

struct Queue* instructionQueue;

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
 
char receivedChar;
boolean newData = false;

void recvOneChar() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    newData = true;
  }
}

void showNewData() {
  if (newData == true) {
    newData = false;

    switch(receivedChar){
      case '0':
        D();
        break;
      case '1':
        U();
        break;
      case '2':
        L();
        break;
      case '3':
        R();
        break;
    }
    
  }
}

void joystick() {

  int curX = analogRead(X_pin);
  int curY = analogRead(Y_pin);


    if (curX < 508 -30){
      U();
    }

    if (curY < 517 - 30){
      L();
    }

    if (curX > 508 + 30){
      D();
    }

    if (curY > 517 + 30){
      R();
    }
  

//  if ((curX < 490 || curX > 520) || (curY > 545 || curY < 500)) { // Deafult 0,0 position values
////    Serial.print("X-axis: ");
////    Serial.print(curX);
////    Serial.print("\n");
////    Serial.print("Y-axis: ");
////    Serial.println(curY);
////    Serial.print("\n\n");
//    delay(200);
//
//    if (curY >= curX) {
//
//      if (curY > 517) {
//        U();
//        Serial.print("U");
//      } else {
//        D();
//        Serial.print("D");
//      }
//
//      Serial.print(" ");
//      Serial.print(curY);
//
//    } else {
//
//      if (curX > 510) {
//        R();
//        Serial.print("L");
//      } else {
//        L();
//        Serial.print("R");
//      }
//
//      Serial.print(" ");
//      Serial.print(curX);
//
//    }
//
//    Serial.print("\n");
//
//  }

}



void loop() {

  if (!joystick_enabled) {
    recvOneChar();
    showNewData();
  } else {
     joystick();
  }  
    
}

// rotates motor by "one step"
void OneStep(motor * m, bool dir) {

  if (dir) {

    switch(m->step_number){

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

    switch(m->step_number) {

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

  m->step_number = (m->step_number + 1) % 4;

  // if (step_number > 3) {
  //  step_number = 0;
  // }

}

#define ONE_TURN_AMOUNT 4
#define STEP_WAIT 5
// Direction Functions //
void U() {
  int i;
  for (i = 0; i < ONE_TURN_AMOUNT; i++) {
    OneStep(UD, 1);
    delay(STEP_WAIT);
  }
}

void D() {
  int i;
  for (i = 0; i < ONE_TURN_AMOUNT; i++) {
    OneStep(UD, 0);
    delay(STEP_WAIT);
  }
}

void L() {
  int i;
  for (i = 0; i < ONE_TURN_AMOUNT; i++) {
    OneStep(LR, 0);
    delay(STEP_WAIT);
  }
}

void R() {
  int i;
  for (i = 0; i < ONE_TURN_AMOUNT; i++) {
    OneStep(LR, 1);
    delay(STEP_WAIT);
  }
}
////////////////
