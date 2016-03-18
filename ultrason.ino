/* Senseur de distance Ultrason HC-SR04:
 VCC sur Arduino 5v 
 GND sur Arduino GND
 Echo sur Arduino broche 7 
 Trig sur Arduino broche 8*/

#define echoPin 4 // broche Echo 
#define trigPin 2 // broche Trigger (declenchement)


int maximumRange = 200; // distance Maximale acceptée (en cm)
int minimumRange = 0;   // distance Minimale acceptée (en cm)
long duration, distance; // Durée utilisé pour calculer la distance

void setup() {
 // Activer la communication série
 Serial.begin (9600);
 // Activer les broches
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LEDPin, OUTPUT); // activer la LED sur la carte (si nécessaire)
}

// Partie du code continuellement exécuté
// Son but est d'effectuer un cycle de détection pour déterminer 
// la distance de l'objet le plus proche (par réverbération de 
// l'onde sur ce dernier)
//
void loop() {
 // Envoi une impulsion de 10 micro seconde sur la broche "trigger" 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);

 // Attend que la broche Echo passe au niveau HAUT 
 // retourne la durée
 duration = pulseIn(echoPin, HIGH);
 
 //Calculer la distance (en cm, basé sur la vitesse du son).
 distance = duration/58.2;
 
 // Si la distance mesurée est HORS des valeurs acceptables
 if (distance >= maximumRange || distance <= minimumRange){
    /* Envoyer une valeur négative sur la liaison série.
       Activer la LED pour indiquer que l'erreur */
   Serial.println("-1");
 }
 else {
   /* Envoyer la distance vers l'ordinateur via liaison série.
      Eteindre la LED pour indiquer une lecture correcte. */
   Serial.print("microseconds ");
   Serial.println(duration);
        // Serial print centimeters :
   Serial.print("cm ");
   Serial.println(distance);
 }
 
 //Attendre 50ms avant d'effectuer la lecture suivante.
 delay(1000);
}
