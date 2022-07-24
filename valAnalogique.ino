float valeur = 0;                     // Variable : lecture du potentiomètre
float tension = 0;                    // Variable servant à la conversion en tension

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);                 // Initialisation de la communication série
}

void loop() {
  valeur = analogRead(A0);            // Lecture des données du pin A0 (0 - 1023)
  tension = valeur*5/1024;            // Conversion valeur analogique en tension
  
  Serial.print("Valeur analogique : ");
  Serial.print(int(valeur));
  Serial.print(" => U = ");
  Serial.print(tension);
  Serial.println(" V");

  if(valeur>300)
    digitalWrite(LED_BUILTIN, HIGH);
  else                 
    digitalWrite(LED_BUILTIN, LOW);
  
  delay(500);
}
