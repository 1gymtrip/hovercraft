// Ultrasonic Sensor 
const int trigPin = 2 ;
const int echoPin = 4 ;
// Motor 1 (Front or Back)
const int motor1a = 22;
const int motor1b = 26;
const int motor1s = 6 ; //speed control
// Motor 2 (Front or Back)
const int motor2a = 31;
const int motor2b = 35;
const int motor2s = 8 ;//speed control
// Motor 3 (Central)
const int motor3a = 44;
const int motor3b = 48;
const int motor3s = 3;
// Servo Motor 
const int servo   = 10;
#include <Servo.h>
Servo myservo;
//Bluetooth Module
//(We use the Android App "Arduino Bluetooth RC Car")
char x = "0" ;

int ultrasonic() {
  /* 
  Through transmition of ultrasonic waves calculates the distance to the nearest object.
  Distance = Δt * c / 2
  Δt: Time between Transmition and Reception 
  c : Speed of Sound in dry air at 20°C
  We divide by 2 because the Δt represents the time for the wave to go hit the object and then come back again.
  By dividing by 2 we can find the distance the wave traversed to reach the object, thus finding the distance between object and vehicle
  */
  int distance;
  int duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);//Transmition
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);//Δt
  distance = duration * 343 / 2;//Distance = Δt * c / 2
  return (distance);
}


/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/
void setup() {
  // Ultrasonic 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Servo 
  myservo.attach(servo);
  // Motor 1 
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor1s, OUTPUT);
  // Motor 2 
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);
  pinMode(motor2s, OUTPUT);
  // Motor 3 
  pinMode(motor3a, OUTPUT);
  pinMode(motor3b, OUTPUT);
  pinMode(motor3s, OUTPUT);
  digitalWrite(motor1s, HIGH);
 digitalWrite(motor2s, HIGH);
  // Motor 3 Setup
  digitalWrite(motor3s, HIGH); 
  digitalWrite(motor3a, HIGH);
  digitalWrite(motor3b, LOW);
  //Commencement of Serial Communication
  Serial.begin(9600);
int ultrasonic = 40;
 myservo.write(90);

}

/*
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
*/

void loop() {
  //-------------------------------------------------------------------------------------------------------------------
  if (ultrasonic() < 20) {
    /* 
    With this 'If-Statement' and bu calling the ultrasonic() function we check the distance to the nearest Object
    If we find that the nearest object is a possible obstacle we close all motors to prevent a crash
    */
    //Motor 1
    digitalWrite(motor1a, LOW);
    digitalWrite(motor1b, LOW);
    //Motor 2
    digitalWrite(motor2a, LOW);
    digitalWrite(motor2b, LOW);
    //Motor 3
    digitalWrite(motor3a, LOW);
    digitalWrite(motor3b, LOW);
    while (ultrasonic() < 30) {
      /*
      To make sure that the vehicle restarts in a safe distance we include this loop that procrastinates until the distance is bigger 
      than 30 cm (30 instead of 20 to make sure that the Hovercraft does not reach the danger zone shortly after restarting)
      */
      delay(200);
    }
    //After the loop is broken we reset the Hovercraft to its post-Setup condition
    digitalWrite(motor3a, HIGH);
    digitalWrite(motor3b, LOW);
  }
  //-------------------------------------------------------------------------------------------------------------------
   Serial.println(x);
  if (Serial.available() > 0) {//checks if there are instructions from the connected bluetooth device
    x = Serial.read();
    Serial.println(x);//Added for Debugging purposes
    if (x=='F'){
      //Forward
      myservo.write(90);
      delay(100);
      motor(1, 'f');
      motor(2, 'f');
    }
    if (x=='B'){
      //Backwards
      myservo.write(90);
      delay(20);
      motor(1, 'b');
      motor(2, 'b');
    }
    if (x=='L'){
      //Left
      myservo.write(180);
      delay(100);
      motor(1, 'f');
      motor(2, 'f');
    }
    if (x=='R'){
      //Right
      motor(1, 'f');
      motor(2, 'f');
      myservo.write(0);
    }
    if (x=='G'){
      //Forward Left
      myservo.write(135);
      delay(100);
      motor(1, 'f');
      motor(2, 'f');
    }
    if (x=='I'){
      //Forward Right
      myservo.write(45);
      delay(100);
      motor(1, 'f');
      motor(2, 'f');
    }
    if (x=='H'){
      //Backwards Left
      myservo.write(45);
      delay(100);
      motor(1, 'b');
      motor(2, 'b');
    }
    if (x=='J'){
      //Backwards Right
      myservo.write(135);
      delay(100);
      motor(1, 'b');
      motor(2, 'b');
    }  
    if (x=='S'){
      //Stop
      motor(1, 's');
      motor(2, 's');
    }
    if (x=='0' or x=='1' or x=='2' or x=='3' or x=='4' or x=='5' or x=='6' or x=='7' or x=='8' or x=='9'){
      //Sets speed to corresponding percentage
      analogWrite(motor1s, 22.5 * int(x));
      analogWrite(motor2s, 22.5 * int(x));
    }
    if (x=='q'){
      //Sets speed to 100%
      analogWrite(motor1s, 225);
      analogWrite(motor2s, 225);
    }
    if (x=='D'){
      //Stops all movement
      digitalWrite(motor3a, LOW);
      digitalWrite(motor3b, LOW);
      digitalWrite(motor1a, LOW);
      digitalWrite(motor1b, LOW);
      digitalWrite(motor2a, LOW);
      digitalWrite(motor2b, LOW);
    }
  }
  //-------------------------------------------------------------------------------------------------------------------
}
void motor( int motor, char direction) {
  if (motor == 1) {
    if (direction == 'f') {
      digitalWrite(motor1a,LOW);
      digitalWrite(motor1b,LOW);
      delay(200);
      digitalWrite(motor1a, HIGH);
      digitalWrite(motor1b, LOW);
    }
    if (direction == 'b') {
      digitalWrite(motor1a,LOW);
      digitalWrite(motor1b,LOW);
      delay(200);
      digitalWrite(motor1b, LOW);
      digitalWrite(motor1a, HIGH);
    }
    if (direction == 's') {
      digitalWrite(motor1b, LOW);
      digitalWrite(motor1a, LOW);
    }
  }
  if (motor == 2) {
    if (direction == 'f') {
      digitalWrite(motor2a,LOW);
      digitalWrite(motor2b,LOW);
      delay(200);
      digitalWrite(motor2a, HIGH);
      digitalWrite(motor2b, LOW);
    }
    if (direction == 'b') {
      digitalWrite(motor2a,LOW);
      digitalWrite(motor2b,LOW);
      delay(200);
      digitalWrite(motor2b, LOW);
      digitalWrite(motor2a, HIGH);
    }
    if (direction == 's') {
      digitalWrite(motor2b, LOW);
      digitalWrite(motor2a, LOW);
    }
  }
}
