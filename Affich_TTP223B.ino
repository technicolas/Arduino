#include <LiquidCrystal_I2C.h> 
#define captTouch 2                       // Pin pour le capteur capacitif "Touch"
#define ledR      3                       // Pin pour la LED Rouge
#define ledV      4                       // Pin pour la LED Verte

LiquidCrystal_I2C lcd(0x27, 20, 4);
 
void setup() {
  Serial.begin(9600);
  pinMode(ledV, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(captTouch, INPUT);
  lcd.init();
}
 
void loop() {

  //lcd.backlight();                      // Active le rétro-éclairage
  //lcd.noBacklight();                    // Désactive le rétro-éclairage
  int ctsValue = digitalRead(captTouch);
  
  if (ctsValue == HIGH){
    digitalWrite(ledV, HIGH);
    digitalWrite(ledR, LOW);
    //Serial.println("Capteur touché");
    lcd.setBacklight(1);                  // Active le rétro-éclairage
    lcd.setCursor(0,0);                   // Se positionne au caractère 0 de la première ligne 0
    lcd.print("PORTE OUVERTE   ");        // Afficher texte ligne 0
    lcd.setCursor(0,1);                   // Se positionne au caractère 0 de la première ligne 1
    lcd.print("                ");        // Afficher texte ligne 1
    for(int i=0;i<6;i++){
      lcd.setCursor(i,1);
      lcd.print(i);                       // Afficher texte ligne 1
      delay(1000);
    }
    lcd.setCursor(0,0);                   // Se positionne au caractère 0 de la première ligne 0
    lcd.print("FERMETURE PORTE ");        // Afficher texte ligne 0
    lcd.setCursor(0,1);                   // Se positionne au caractère 0 de la première ligne 1
    lcd.print("    en cours    ");        // Afficher texte ligne 1
    cligno();
  }
  else{
    digitalWrite(ledV,LOW);
    digitalWrite(ledR, HIGH);
    //Serial.println("Capteur non touché");
    lcd.setBacklight(0);
    lcd.setCursor(0,0);
    lcd.print("PORTE FERMEE    ");
    lcd.setCursor(0,1);
    lcd.print("Appui --> ouvrir");
  }
  delay(100);
}

void cligno(void){                        // Fonction de clignotement LED Verte
  for(int i=0;i<6;i++){
    digitalWrite(ledV, LOW);
    delay(100);
    digitalWrite(ledV, HIGH);
    delay(300);
  }
}
