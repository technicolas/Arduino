const byte entree[] = {
  9,            // 9 = bouton debug
  };

const byte sortie[] = {
  2,            // 2 = moteur gauche pin1
  3,            // 3 = moteur gauche pin2
  4,            // 4 = moteur droit pin1
  5,            // 5 = moteur droit pin2
  6,            // Contrôle la LED qui simule le moteur GAUCHE.
  7,            // Contrôle la LED qui simule le moteur GAUCHE et DROIT.
  8,            // Contrôle la LED qui simule le moteur DROIT.
  LED_BUILTIN,  // Contrôle la LED interne.
  };

#define SEUIL 700

void setup() {
  Serial.begin(9600);

  for(int i=0; i<1; i++){
    pinMode(entree[i], INPUT_PULLUP);                   // Initialisation des entrées (en fonction du tableau situé quelques lignes plus haut.
  }
  
  for(int i=0; i<8; i++){
    pinMode(sortie[i], OUTPUT);                         // Initialisation des sorties (en fonction du tableau situé quelques lignes plus haut.
  }
  stop();                                               // Au démarrage, on place la voiture sur la ligne noire et face à la photorésitance centrale.
}

void loop() {
  int Capt_G = analogRead(A0);                          // Valeur provenant de la photorésistance située à gauche.
  int Capt_M = analogRead(A1);                          // Valeur provenant de la photorésistance située au milieu.
  int Capt_D = analogRead(A2);                          // Valeur provenant de la photorésistance située à droite.
//  console();
  
  if(!etatDebug()){
    testLigne(Capt_G, Capt_M, Capt_D);
    digitalWrite(LED_BUILTIN, LOW);
  }
  else{
    arret();
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

// --------------------------------------------------
// *****************  Fonctions:  *******************
// --------------------------------------------------

void avant() {
  digitalWrite(sortie[0], LOW);
  digitalWrite(sortie[1], HIGH);
  digitalWrite(sortie[2], LOW);
  digitalWrite(sortie[3], HIGH);
}

void gauche() {
  digitalWrite(sortie[0], LOW);
  digitalWrite(sortie[1], LOW);
  digitalWrite(sortie[2], LOW);
  digitalWrite(sortie[3], HIGH);
}

void droite() {
  digitalWrite(sortie[0], LOW);
  digitalWrite(sortie[1], HIGH);
  digitalWrite(sortie[2], LOW);
  digitalWrite(sortie[3], LOW);
}

void arret() {
  for(int i=0; i<4; i++){
    digitalWrite(sortie[i], LOW);
  }
}

void testLigne(int Capt_G, int Capt_M, int Capt_D){
  if(Capt_G < SEUIL) 
    roueD();                                                    // Ligne noire devant la photorésistance de gauche, mise en fonction du moteur droite.
  if(Capt_M < SEUIL)
    roueGplusD();                                               // Ligne noire devant la photorésistance centrale, mise en fonction du moteur gauche PLUS droit.
  if(Capt_D < SEUIL)
    roueG();                                                    // Ligne noire devant la photorésistance de droite, mise en fonction du moteur gauche.
  if(Capt_G > SEUIL && Capt_M > SEUIL && Capt_D > SEUIL)
    stop();                                                     // Si aucune ligne visible, mise à l'arrêt complet du robot.
  delay(100);
}

void roueG(){
  digitalWrite(sortie[4], HIGH);                                // LED GAUCHE allumée, les autres éteintes.
  digitalWrite(sortie[5], LOW);
  digitalWrite(sortie[6], LOW);
  gauche();                                                     // Moteur gauche fonctionne seul.
}

void roueGplusD(){
  digitalWrite(sortie[4], LOW);
  digitalWrite(sortie[5], HIGH);                                // LED CENTRALE allumée, les autres éteintes.
  digitalWrite(sortie[6], LOW);
  avant();                                                      // Moteur gauche ET droit fonctionnent.
}

void roueD(){
  digitalWrite(sortie[4], LOW);
  digitalWrite(sortie[5], LOW);
  digitalWrite(sortie[6], HIGH);                                // LED DROITE allumée, les autres éteintes.
  droite();                                                     // Moteur droit fonctionne seul.
}

void stop(){
  digitalWrite(sortie[4], LOW);
  digitalWrite(sortie[5], LOW);
  digitalWrite(sortie[6], LOW);                                 // Extinction TOTALE, j'ai bien dit TOTALE (!) de toutes les LED's.
  arret();
}

void console(){
  Serial.print("Capteur Gauche: "); Serial.println(analogRead(A0));
  Serial.print("Capteur Milieu: "); Serial.println(analogRead(A1));
  Serial.print("Capteur Droit: "); Serial.println(analogRead(A2));
}

bool etatDebug(){
  bool etat;
  int etatBouton = digitalRead(entree[0]);
  
  if(etatBouton == HIGH)
    return false;
  else
    return true;
}
