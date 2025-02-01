void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
}

void delayForMs(int ms) {
  unsigned long startTime = millis();
  while (millis() - startTime < ms) {
    // نترك المعالج يعمل دون توقف خلال التأخير
  }
}

void loop() {
  for (int i = 0; i < 2; i++) {
    if (i == 0) {
      digitalWrite(0, HIGH); 
      digitalWrite(1, HIGH);
      delayForMs(250);  // محاكاة delay(250) باستخدام حلقة millis()
      digitalWrite(0, LOW); 
      digitalWrite(1, LOW);  
      delayForMs(250);
      digitalWrite(0, HIGH); 
      digitalWrite(1, HIGH);
      delayForMs(250);                    
      digitalWrite(0, LOW); 
      digitalWrite(1, LOW);  
      delayForMs(250);
      digitalWrite(0, HIGH); 
      delayForMs(250);                    
      digitalWrite(0, LOW);   
      delayForMs(250);
      digitalWrite(0, HIGH); 
      delayForMs(250);                    
      digitalWrite(0, LOW); 
      delayForMs(250);
    }
    digitalWrite(1, HIGH); 
    delayForMs(500);  // محاكاة delay(500) باستخدام حلقة millis()
    digitalWrite(1, LOW);  
    delayForMs(500);  // محاكاة delay(500) باستخدام حلقة millis()
  }
}
