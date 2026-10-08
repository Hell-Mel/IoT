#define led1 4 
#define led2 5

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  digitalWrite(led2, LOW);
  digitalWrite(led1, HIGH); 
  delay(500);
  digitalWrite(led2, HIGH);
  digitalWrite(led1, LOW); 
  delay(500);
}
