#define capteurTouch 2 // Pin for capactitive touch sensor
 
int ledPin = 13; // pin for the LED
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
  pinMode(capteurTouch, INPUT);
}
 
void loop() {
  int valCapt = digitalRead(capteurTouch);
  if (valCapt == HIGH){
    digitalWrite(ledPin, HIGH);
    Serial.println(valCapt);
  }
  else{
    digitalWrite(ledPin,LOW);
    Serial.println(valCapt);
  } 
  delay(100);
}
