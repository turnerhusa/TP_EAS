char serialData;
int LED = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    serialData = Serial.read();
    Serial.print(serialData);
  
   if (serialData == '1')
    digitalWrite(LED, HIGH);
   else if (serialData == '0')
    digitalWrite(LED, LOW);
  }
}
