void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  int valR = analogRead(A0);
  Serial.println(valR);

  if (valR<600){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
  }
  else{
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
  }
  
  delay(100);
}
