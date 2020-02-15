#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

#define STEPPER_PIN_1_1 6
#define STEPPER_PIN_2_1 5
#define STEPPER_PIN_3_1 4
#define STEPPER_PIN_4_1 3

// For one step code
int step_number = 0;

// For serial code
char serialData;
int incoming[2];

void setup() {
	pinMode(STEPPER_PIN_1, OUTPUT);
	pinMode(STEPPER_PIN_2, OUTPUT);
	pinMode(STEPPER_PIN_3, OUTPUT);
	pinMode(STEPPER_PIN_4, OUTPUT);


	Serial.begin(9600);
}

void loop() {
	while(Serial.available() >= 3){

    for (int i = 0; i < 3; i++){
      incoming[i] = Serial.read();
    }
    multiStep(incoming[0],incoming[1], incoming[2]);
	}
}

void multiStep(bool dir, int n){
	int i = 0;
	for (i = 0; i < n; i++){
		OneStep(dir);
		delay(5);
	}
}


void OneStep(bool dir){
		if(dir){
			switch(step_number){
				case 0:
					digitalWrite(STEPPER_PIN_1, HIGH);
					digitalWrite(STEPPER_PIN_2, LOW);
					digitalWrite(STEPPER_PIN_3, LOW);
					digitalWrite(STEPPER_PIN_4, LOW);
					break;
				case 1:
					digitalWrite(STEPPER_PIN_1, LOW);
					digitalWrite(STEPPER_PIN_2, HIGH);
					digitalWrite(STEPPER_PIN_3, LOW);
					digitalWrite(STEPPER_PIN_4, LOW);
					break;
				case 2:
					digitalWrite(STEPPER_PIN_1, LOW);
					digitalWrite(STEPPER_PIN_2, LOW);
					digitalWrite(STEPPER_PIN_3, HIGH);
					digitalWrite(STEPPER_PIN_4, LOW);
					break;
				case 3:
					digitalWrite(STEPPER_PIN_1, LOW);
					digitalWrite(STEPPER_PIN_2, LOW);
					digitalWrite(STEPPER_PIN_3, LOW);
					digitalWrite(STEPPER_PIN_4, HIGH);
					break;
			} 
		}else{
			switch(step_number){
				case 0:
					digitalWrite(STEPPER_PIN_1, LOW);
					digitalWrite(STEPPER_PIN_2, LOW);
					digitalWrite(STEPPER_PIN_3, LOW);
					digitalWrite(STEPPER_PIN_4, HIGH);
					break;
				case 1:
					digitalWrite(STEPPER_PIN_1, LOW);
					digitalWrite(STEPPER_PIN_2, LOW);
					digitalWrite(STEPPER_PIN_3, HIGH);
					digitalWrite(STEPPER_PIN_4, LOW);
					break;
				case 2:
					digitalWrite(STEPPER_PIN_1, LOW);
					digitalWrite(STEPPER_PIN_2, HIGH);
					digitalWrite(STEPPER_PIN_3, LOW);
					digitalWrite(STEPPER_PIN_4, LOW);
					break;
				case 3:
					digitalWrite(STEPPER_PIN_1, HIGH);
					digitalWrite(STEPPER_PIN_2, LOW);
					digitalWrite(STEPPER_PIN_3, LOW);
					digitalWrite(STEPPER_PIN_4, LOW);
					break;
			} 
	}
	step_number++;
	if(step_number > 3){
		step_number = 0;
	}
}
