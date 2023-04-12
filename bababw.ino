// VARIABLES ET CONSTANTE UKTRASONNIC
const int S = 7; //droit
long microsecondsToInches(long microseconds) { return microseconds / 74 / 2; }
long microsecondsToCentimeters(long microseconds) {return microseconds / 29 / 2; }

//VARIABLES MOTEUR
int M1 = 4; //moteur droit connecté au pin4
int M2 = 7; //moteur gauche connecté au pin 6
int E1 = 5; //pour controler la vitesse du moteur droit 
int E2 = 6; //pour controler la vitesse du moteur gauche

// Configuration de la broche d'interruption
#define interruptPin 2
volatile bool interruptFlag = false;
void interruptFunction() {
  interruptFlag = true;
}

// Variables line finder

const int capteurDroit = A0; // Connecter le capteur Droit en A0
const int capteurGauche = A2; // Connecter le capteur Gauche en A

void setup() {

  //moteur
  pinMode (M1, OUTPUT); //moteur droit en sortie
  pinMode (M2, OUTPUT); //moteur gauche en sortie
  Serial.begin(9600);


  // Configuration de la broche d'interruption
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptFunction, FALLING);


//line finder
  pinMode(capteurDroit, INPUT); //capteur droit recois le signal lumineux
  pinMode(capteurGauche, INPUT); //capteur gauche recois le signal lumineux
  Serial.begin(9600); // Initialise la communication série à 9600 bauds

}


void loop() {

  float distance = 0;
  long duration = 0;
while (distance < 10) {
long duration, distancei, distance;
   
  pinMode(S, OUTPUT);
  digitalWrite(S, LOW);
  delayMicroseconds(2);
  digitalWrite(S, HIGH);
  delayMicroseconds(5);
  digitalWrite(S, LOW);

  pinMode(S, INPUT);
  duration = pulseIn(S, HIGH);

  distancei = microsecondsToInches(duration);
  distance = microsecondsToCentimeters(duration);

    if (distance < 4 || interruptFlag) { //-->gauche
      digitalWrite(M1, HIGH); 
    analogWrite(E1, 240);
    digitalWrite(M2, HIGH); 
    analogWrite(E2, 110);
    } 

else if (distance < 10 && distance > 7) { //--> droite
      digitalWrite(M1, HIGH); 
    analogWrite(E1, 110);
    digitalWrite(M2, HIGH); 
    analogWrite(E2, 240);
    }
    else if (distance > 4 && distance < 7){ //avancer
    digitalWrite(M1, HIGH); 
    analogWrite(E1, 150);
    digitalWrite(M2, HIGH); //Roue gauche avance a une vistesse max
    analogWrite(E2, 150);
    }
  }
  delay(100);

  // Réinitialiser le drapeau d'interruption
    interruptFlag = false;

// Attendre un certain temps avant de reprendre le programme
    delay(5000);

int etatDroit = digitalRead(capteurDroit); // Lit l'état du capteur droit
  int etatGauche = digitalRead(capteurGauche); // Lit l'état du capteur gauche
  
  if (etatGauche == LOW && etatDroit == LOW) { // les deux HORS ligne --> AVANCER
    digitalWrite(M1, HIGH); 
    analogWrite(E1, 150);
    digitalWrite(M2, HIGH); //Roue gauche avance a une vistesse max
    analogWrite(E2, 150);
  }
else if (etatGauche == HIGH && etatDroit == HIGH) { // les deux surligne --> AVANCER
     digitalWrite(M1, HIGH); 
    analogWrite(E1, 150);
    digitalWrite(M2, HIGH); //Roue gauche avance a une vistesse max
    analogWrite(E2, 150); 
}

  else if (etatGauche == LOW && etatDroit == HIGH) { //droit SURligne -->DROITE     
		digitalWrite(M1, HIGH); 
    analogWrite(E1, 80);
    digitalWrite(M2, HIGH); //Roue gauche avance a une vistesse max
    analogWrite(E2, 125);
  }

 else if (etatGauche == HIGH && etatDroit == LOW) { //gauche sur ligneligne -->gauche     
		digitalWrite(M1, HIGH); 
    analogWrite(E1, 125);
    digitalWrite(M2, HIGH); //Roue gauche avance a une vistesse max
    analogWrite(E2, 80);
}  
delay(5);    
}
