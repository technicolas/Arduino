#include "TinyGPS++.h"
#include "SoftwareSerial.h"

SoftwareSerial serial_connection(10, 11);       // RX=pin 10, TX=pin 11,
TinyGPSPlus gps;

void setup(){
    Serial.begin(9600);
    serial_connection.begin(9600);
    Serial.println("GPS start");
}

void loop(){
    while(serial_connection.available()){
        gps.encode(serial_connection.read());
    }
    if(gps.location.isUpdated()){
        Serial.println("Satellite count:");
        Serial.println(gps.satellites.value());
        Serial.println("Latitude:");
        Serial.println(gps.location.lat(), 6);
        Serial.println("Longitude:");
        Serial.println(gps.location.lng(), 6);
        Serial.println("Speed MPH:");
        Serial.println(gps.speed.mph());
        Serial.println("Altitude Feet:");
        Serial.println(gps.altitude.feet());
        Serial.println("");
    }
}