#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define ledR 2
#define buzzer 9
#define SEALEVELPRESSURE_HPA (1013.25)
#define TEMP_Alm 22


Adafruit_BME280 bme; // I2C

unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  
  unsigned status;
  delayTime = 2000;
  bme.begin(0x76, &Wire);
}

void loop() { 
    printValues();
    delay(delayTime);
    alarmeTemp();
}


void printValues() {
    Serial.print("Temperature = ");       Serial.print(bme.readTemperature()); Serial.print(" *C  ");
    Serial.print("Pressure = ");          Serial.print(bme.readPressure() / 100.0F); Serial.print(" hPa  ");
    Serial.print("Approx. Altitude = ");  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); Serial.print(" m  ");
    Serial.print("Humidity = ");          Serial.print(bme.readHumidity()); Serial.println(" %");
    Serial.println();
}

void alarmeTemp() {
  if(bme.readTemperature()>TEMP_Alm){
    digitalWrite(ledR, HIGH);
//    tone(buzzer, 1000);       // Send 1KHz sound signal...
//    delay(100);                // 1000...for 1 sec
//    noTone(buzzer);           // Stop sound...
//    delay(100);                // 1000...for 1 sec
  }
  else
    digitalWrite(ledR, LOW);
}
