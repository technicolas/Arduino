#define capteurTouch 2 // Pin for capactitive touch sensor
 
int ledPin = 13; // pin for the LED
int ledState = LOW;
int lastButtonState;
int currentButtonState;
int temperature[]={0,10,17,18,19,20,21,22,23,24,25,30,35};
int temp = 7;
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
  pinMode(capteurTouch, INPUT);
}
 
void loop() {
  lastButtonState    = currentButtonState;
  currentButtonState = digitalRead(capteurTouch);
  
  if(lastButtonState == LOW && currentButtonState == HIGH) {
    //Serial.println(ledState);
    //ledState=!ledState;
    //digitalWrite(ledPin, ledState);
    temp++;
  }
  Serial.println(temperature[temp]);
  if (temp>12)
    temp=0;
    
  delay(100);
}
