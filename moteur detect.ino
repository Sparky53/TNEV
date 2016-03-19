/* Senseur de distance Ultrason HC-SR04:
 VCC sur Arduino 5v 
 GND sur Arduino GND
 Echo sur Arduino broche 7 
 Trig sur Arduino broche 8*/

#define echoPin 4 // broche Echo 
#define trigPin 2 // broche Trigger (declenchement)
int motor1_enablePin = 11; //pwm
int motor1_in1Pin = 13;
int motor1_in2Pin = 12;
 
int motor2_enablePin = 10; //pwm
int motor2_in1Pin = 8;
int motor2_in2Pin = 7;


int maximumRange = 200; // distance Maximale acceptée (en cm)
int minimumRange = 0;   // distance Minimale acceptée (en cm)
long duration, distance; // Durée utilisé pour calculer la distance

void setup() {
 // Activer la communication série
 Serial.begin (9600);
 // Activer les broches
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
   //on initialise les pins du moteur 1
  pinMode(motor1_in1Pin, OUTPUT);
  pinMode(motor1_in2Pin, OUTPUT);
  pinMode(motor1_enablePin, OUTPUT);
 
  //on initialise les pins du moteur 2
  pinMode(motor2_in1Pin, OUTPUT);
  pinMode(motor2_in2Pin, OUTPUT);
  pinMode(motor2_enablePin, OUTPUT);
 
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
 if (distance <= 20){
  SetMotor2(0, false);
  SetMotor1(0, false);
 }
 else {
   SetMotor2(175, true);
   SetMotor1(175, true);
   Serial.print("microseconds ");
   Serial.println(duration);
        // Serial print centimeters :
   Serial.print("cm ");
   Serial.println(distance);
 }
}
