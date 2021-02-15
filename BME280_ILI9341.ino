#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define LEDR 2
#define BUZZER 9
#define SEALEVELPRESSURE_HPA (1013.25)
#define TEMP_ALM 22

Adafruit_BME280 bme; // I2C
LiquidCrystal_I2C lcd(0x27, 20, 4);

unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  lcd.init();
  pinMode(LEDR, OUTPUT);
  
  unsigned status;
  delayTime = 1000;
  bme.begin(0x76, &Wire);
  lcd.init();
}

void loop() {
  printConsole();
  for (int i=1; i<4; i++){
    effaceEcran();
    printAfficheur(i);
  delay(delayTime);
  }
  alarmeTemp();
}

void printConsole() {
  Serial.print("Temperature = ");       Serial.print(bme.readTemperature()); Serial.print(" *C  ");
  Serial.print("Pressure = ");          Serial.print(bme.readPressure() / 100.0F); Serial.print(" hPa  ");
  //Serial.print("Approx. Altitude = ");  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); Serial.print(" m  ");
  Serial.print("Humidity = ");          Serial.print(bme.readHumidity()); Serial.println(" %");
}

void printAfficheur(int fct) {
  lcd.setBacklight(1);                  // Active le rétro-éclairage
  
  lcd.setCursor(14,1);
  lcd.print(TEMP_ALM);

  switch (fct) {
    case 1:     //Affichage de la température:
      lcd.setCursor(0,0);
      lcd.print("Temperature");
      lcd.setCursor(0,1);
      lcd.print(bme.readTemperature());
      lcd.setCursor(6,1);
      lcd.print((char)223);
      lcd.setCursor(7,1);
      lcd.print("C");
      break;
    case 2:     //Affichage de la pression atmosphérique:
      lcd.setCursor(0,0);
      lcd.print("P. atmospherique");
      lcd.setCursor(0,1);
      lcd.print(bme.readPressure() / 100.0F);
      lcd.setCursor(8,1);
      lcd.print("hPa");
      break;
    case 3:     //Affichage de l'humidité:
      lcd.setCursor(0,0);
      lcd.print("Humidite");
      lcd.setCursor(0,1);
      lcd.print(bme.readHumidity());
      lcd.setCursor(6,1);
      lcd.print("%");
      break;
    default:
      lcd.setCursor(0,0);
      lcd.print("Rien a afficher");
      break;
  }
}

void effaceEcran(){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("             ");
}

void alarmeTemp() {
  if(bme.readTemperature()>TEMP_ALM){
    digitalWrite(LEDR, HIGH);
    //    tone(BUZZER, 1000);   // Send 1KHz sound signal...
    //    delay(100);           // 1000...for 1 sec
    //    noTone(BUZZER);       // Stop sound...
    //    delay(100);           // 1000...for 1 sec
  }
  else
    digitalWrite(LEDR, LOW);
}
