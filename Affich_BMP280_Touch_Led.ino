#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define LEDR          2
#define CAPTEUR_TOUCH 7
#define BUZZER        9
#define SEALEVELPRESSURE_HPA (1013.25)
#define TEMP_ALM      22

Adafruit_BME280 bme; // I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

int lastButtonState;
int currentButtonState;
int temperature[]={0,10,15,20,21,22,25,30,35,40,45}; // Températures de consigne
int temp = 5;

unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  lcd.init();
  pinMode(LEDR, OUTPUT);
  pinMode(CAPTEUR_TOUCH, INPUT);
  
  unsigned status;
  delayTime = 1000;
  bme.begin(0x76, &Wire);
  lcd.init();
}

void loop() {
  effaceEcran();
  afficheur();
  alarmeTemp();
  if(digitalRead(CAPTEUR_TOUCH) == HIGH)    // Si appui sur le capteur touch...
    temp++;                                 // ... on incrémente
    
  if (temp>12)                              // Si on arrive au bout du tableau...
    temp=0;                                 // ... on revient au début du tableau
  printConsole();
  delay(delayTime);
}

void afficheur() {
  lcd.setBacklight(1);                    // Active le rétro-éclairage
  
  // Ligne du HAUT:
  lcd.setCursor(0,0);
  lcd.print(bme.readTemperature());       // Affichage de la température instantanée
  lcd.setCursor(5,0);
  lcd.print((char)223);
  lcd.setCursor(7,0);
  lcd.print("Hum");
  lcd.setCursor(10,0);
  lcd.print(bme.readHumidity());          // Affichage de l'humidité
  lcd.setCursor(15,0);
  lcd.print("%");

  // Ligne du BAS:
  lcd.setCursor(0,1);
  lcd.print(bme.readPressure() / 100.0F); // Affichage de la pression
  lcd.setCursor(7,1);
  lcd.print("hPA");
  lcd.setCursor(12,1);
  lcd.print("C:");
  lcd.setCursor(14,1);
  lcd.print(temperature[temp]);           // Affichage de la température de consigne
}

void effaceEcran(){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}

void alarmeTemp() {
  if(bme.readTemperature()>temperature[temp]){    // Si dépassement de la consigne...
    digitalWrite(LEDR, HIGH);                       // ... on allume la LED
    //    tone(BUZZER, 1000);   // Send 1KHz sound signal...
    //    delay(100);           // 1000...for 1 sec
    //    noTone(BUZZER);       // Stop sound...
    //    delay(100);           // 1000...for 1 sec
  }
  else                                              // Sinon...
    digitalWrite(LEDR, LOW);                        // ... on éteint la LED
}

void printConsole() {
  Serial.print("Temperature = ");       Serial.print(bme.readTemperature()); Serial.print(" *C  ");
  Serial.print("Pressure = ");          Serial.print(bme.readPressure() / 100.0F); Serial.print(" hPa  ");
  //Serial.print("Approx. Altitude = ");  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); Serial.print(" m  ");
  Serial.print("Humidity = ");          Serial.print(bme.readHumidity()); Serial.println(" %");
}
