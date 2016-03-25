int motor1_enablePin = 11; //pwm
int motor1_in1Pin = 13;
int motor1_in2Pin = 12;
 
int motor2_enablePin = 10; //pwm
int motor2_in1Pin = 8;
int motor2_in2Pin = 7;
int switchState = 0;
#define echoPin 4 // broche Echo 
#define trigPin 2 // broche Trigger (declenchement)

int maximumRange = 200; // distance Maximale acceptée (en cm)
int minimumRange = 0;   // distance Minimale acceptée (en cm)
long duration, distance; // Durée utilisé pour calculer la distance
 
void setup()
{
  //on initialise les pins du moteur 1
  pinMode(motor1_in1Pin, OUTPUT);
  pinMode(motor1_in2Pin, OUTPUT);
  pinMode(motor1_enablePin, OUTPUT);
 
  //on initialise les pins du moteur 2
  pinMode(motor2_in1Pin, OUTPUT);
  pinMode(motor2_in2Pin, OUTPUT);
  pinMode(motor2_enablePin, OUTPUT);
  
   // Activer la communication série
 Serial.begin (9600);
 // Activer les broches
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 
 SetMotor1(0, true);
 SetMotor2(0, true);
}
 
void loop()
{
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
   Serial.println("200");
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

  if (distance <= 30) {
SetMotor2(0,true);   //arrêt des moteurs
SetMotor1(0,true);
delay (2000);
SetMotor2 (150,false);  //tourner à droite 90°
SetMotor1 (150,true);
delay (800);
SetMotor2 (0,true); //arrêt des moteurs
SetMotor1 (0,true);
delay (2000);
SetMotor2 (150,true); //avancer 50cm
SetMotor1 (150,true);
delay (2000);
SetMotor2 (0,true); //arrêter les moteurs
SetMotor1 (0,true);
delay(2000);
SetMotor2 (150,true); //tourner à gauche 90°
SetMotor1 (150,false);
delay (800);
SetMotor2 (0,true); //arrêt des moteurs
SetMotor1 (0,true);
delay(2000);
SetMotor2 (150,true); //avancer 65cm
SetMotor1 (150,true);
delay(2600);
SetMotor2 (0,true); //arrêter les moteurs
SetMotor1 (0,true);
delay(2000);
SetMotor2 (150,true);  //tourner à gauche 90°
SetMotor1 (150,false);
delay(800);
SetMotor2 (0,true); //arrêter les moteurs
SetMotor1 (0,true);
delay(2000);
SetMotor2 (150,true); //avancer 50cm
SetMotor1 (150,true);
delay(2000);
SetMotor2 (0,true); //arrêter les moteurs
SetMotor1 (0,true);
delay(2000);
SetMotor2 (150,false);
SetMotor1(150,true);
delay (800);

} //50cm = 2000ms
// 65cm = 2600ms
  else {
    SetMotor2(200, true);
    SetMotor1(200, true);
}
}
//Fonction qui set le moteur1
void SetMotor1(int speed, boolean reverse)
{
  analogWrite(motor1_enablePin, speed);
  digitalWrite(motor1_in1Pin, ! reverse);
  digitalWrite(motor1_in2Pin, reverse);
}
 
//Fonction qui set le moteur2
void SetMotor2(int speed, boolean reverse)
{
  analogWrite(motor2_enablePin, speed);
  digitalWrite(motor2_in1Pin, ! reverse);
  digitalWrite(motor2_in2Pin, reverse);
}
