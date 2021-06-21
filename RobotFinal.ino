const byte sortie[] = {
  2,  // moteur gauche pin1 = 2;
  3,  // moteur gauche pin2 = 3;
  4,  // moteur droit  pin1 = 4;
  5,  // moteur droit  pin2 = 5;
  6,  // Contrôle la LED qui simule le moteur GAUCHE.
  7,  // Contrôle la LED qui simule le moteur GAUCHE et DROIT.
  8,  // Contrôle la LED qui simule le moteur DROIT.
  };

void setup() {
  Serial.begin(9600);
  for(int i=0; i<7; i++){
    pinMode(sortie[i], OUTPUT);
  }
  roueGplusD();                                         // Au démarrage, on place la voiture sur la ligne noire et face à la photorésitance centrale.
}

void loop() {
  int Capt_G = analogRead(A0);                          // Valeur provenant de la photorésistance située à gauche.
  int Capt_M = analogRead(A1);                          // Valeur provenant de la photorésistance située au milieu.
  int Capt_D = analogRead(A2);                          // Valeur provenant de la photorésistance située à droite.
  
  testLigne(Capt_G, Capt_M, Capt_D);
//  console(false, Capt_G, Capt_M, Capt_D);
}


// TODO Intégrer un mode DEBUG
// if(!debug) then...



// --------------------------------------------------
// *****************  Fonctions:  *******************
// --------------------------------------------------

void avant() {
  digitalWrite(sortie[0], HIGH);
  digitalWrite(sortie[1], LOW);
  digitalWrite(sortie[2], HIGH);
  digitalWrite(sortie[3], LOW);
}

void gauche() {
  digitalWrite(sortie[0], LOW);
  digitalWrite(sortie[1], LOW);
  digitalWrite(sortie[2], HIGH);
  digitalWrite(sortie[3], LOW);
}

void droite() {
  digitalWrite(sortie[0], HIGH);
  digitalWrite(sortie[1], LOW);
  digitalWrite(sortie[2], LOW);
  digitalWrite(sortie[3], LOW);
}

void arret() {
  digitalWrite(sortie[0], LOW);
  digitalWrite(sortie[1], LOW);
  digitalWrite(sortie[2], LOW);
  digitalWrite(sortie[3], LOW);
}

void repos(int temps){
  delay(temps);
}

void testLigne(int Capt_G, int Capt_M, int Capt_D){
    // Exemple:
    // --------
    // Si la voiture va trop à droite, le capteur gauche sera dans le noir; il faudra alors demander à la roue droite d'accélérer ou à la roue gauche de ralentir un peu.
    // Si la voiture va trop à gauche, le capteur droit sera dans le noir; il faudra alors demander à la roue gauche d'accélérer ou à la roue droite de ralentir un peu.
    // Par contre, si le capteur du milieu est sur la bande noire, on demande aux deux roues d'avancer normalement.
    
  if(Capt_G < 600) roueG();                             // Ligne noire devant la photorésistance de gauche, mise en fonction du moteur gauche.
  if(Capt_M < 600) roueGplusD();                        // Ligne noire devant la photorésistance centrale, mise en fonction du moteur gauche PLUS droit.
  if(Capt_D < 600) roueD();                             // Ligne noire devant la photorésistance de droite, mise en fonction du moteur droit.
  delay(100);
}

void roueG(){
  digitalWrite(2, HIGH);                                // LED GAUCHE allumée, les autres éteintes.
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  gauche();
}

void roueGplusD(){
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);                                // LED CENTRALE allumée, les autres éteintes.
  digitalWrite(4, LOW);
  avant();
}

void roueD(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);                                // LED DROITE allumée, les autres éteintes.
  droite();
}

void console(bool etat, int Capt_G, int Capt_M, int Capt_D){
  if (etat==1){
    Serial.print("Capteur Gauche: "); Serial.println(Capt_G);
    Serial.print("Capteur Milieu: "); Serial.println(Capt_M);
    Serial.print("Capteur Droit: "); Serial.println(Capt_D);
    delay(1000);
  }
}
