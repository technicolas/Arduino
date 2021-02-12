#include <LiquidCrystal_I2C.h> 
#define captTouch 2                       // Pin for capactitive touch sensor

LiquidCrystal_I2C lcd(0x27, 20, 4);

int ledPin = 13;                          // Pin pour la  LED
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
  pinMode(captTouch, INPUT);
  lcd.init();
}
 
void loop() {

  //lcd.backlight();                      // Active le rétro-éclairage
  //lcd.noBacklight();                    // Désactive le rétro-éclairage
  int ctsValue = digitalRead(captTouch);
  
  if (ctsValue == HIGH){
    digitalWrite(ledPin, HIGH);
    //Serial.println("Capteur touché");
    lcd.setBacklight(1);                  // Active le rétro-éclairage
    lcd.setCursor(0,0);                  // Se positionne au caractère 0 de la première ligne 0
    lcd.print("PORTE OUVERTE   ");           // Afficher texte ligne 0
    lcd.setCursor(0,1);                   // Se positionne au caractère 0 de la première ligne 1
    lcd.print("                ");           // Afficher texte ligne 1
    for(int i=5;i>0;i--){
      lcd.setCursor(6,1);
      lcd.print(i);                       // Afficher texte ligne 1
      delay(1000);
    }
    lcd.setCursor(0,0);                  // Se positionne au caractère 0 de la première ligne 0
    lcd.print("FERMETURE PORTE ");           // Afficher texte ligne 0
    lcd.setCursor(0,1);                   // Se positionne au caractère 0 de la première ligne 1
    lcd.print("    en cours    ");           // Afficher texte ligne 1
    delay(2000);
  }
  else{
    digitalWrite(ledPin,LOW);
    //Serial.println("Capteur non touché");
    lcd.setBacklight(0);
    lcd.setCursor(0,0);
    lcd.print("PORTE FERMEE    ");
    lcd.setCursor(0,1);
    lcd.print("Appui --> ouvrir");
  }
  delay(100);
}
