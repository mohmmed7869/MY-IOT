void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
}

void loop() {
  if(digitalRead(1)==LOW)
  digitalWrite(0, HIGH);
  else
  digitalWrite(0, LOW);
}
