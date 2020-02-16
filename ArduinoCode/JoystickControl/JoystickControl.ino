// Arduino pin numbers
const int Y_pin = A0; // analog pin connected to Y output
const int X_pin = A1; // analog pin connected to X output

int curX;
int curY;

void setup() {
//  pinMode(SW_pin, INPUT);
//  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  curX = analogRead(X_pin);
  curY = analogRead(Y_pin);

  if(curX != 504 && curY != 517){ // Deafult 0,0 position values
    Serial.print("X-axis: ");
    Serial.print(curX);
    Serial.print("\n");
    Serial.print("Y-axis: ");
    Serial.println(curY);
    Serial.print("\n\n");
    delay(500);
  }

  
 
}
