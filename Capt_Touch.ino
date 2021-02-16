#define capteurTouch 2 // Pin for capactitive touch sensor
 
int ledPin = 13; // pin for the LED
int ledState = LOW;
int lastButtonState;
int currentButtonState;
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
  pinMode(capteurTouch, INPUT);
}
 
void loop() {
  lastButtonState    = currentButtonState;
  currentButtonState = digitalRead(capteurTouch);

  if(lastButtonState == LOW && currentButtonState == HIGH) {
    Serial.println(ledState);
    ledState=!ledState;
    digitalWrite(ledPin, ledState);
  }
  delay(10);
}
