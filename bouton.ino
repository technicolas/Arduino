// le bouton est connecté à la broche 2 de la carte Adruino
const int bouton = 2;


// variable qui enregistre l'état du bouton
int etatBouton;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(bouton, INPUT_PULLUP); // le bouton est une entrée
    etatBouton = HIGH; // on initialise l'état du bouton comme "relaché"
}

void loop()
{
    etatBouton = digitalRead(bouton); // Rappel : bouton = 2

    if(etatBouton == HIGH){ // test si le bouton a un niveau logique HAUT
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else{  // test si le bouton a un niveau logique différent de HAUT (donc BAS)
        digitalWrite(LED_BUILTIN, LOW);
    }
}
