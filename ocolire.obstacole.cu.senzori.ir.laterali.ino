#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h> 
//robot ocolire obstacole cu senzor ir pentru detectarea miscarii si senzori laterali
// Definirea pinurilor și a variabilelor
#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 100
#define BUZZER_PIN A2 
#define IR_SENSOR_FRONT A3 // Pinul pentru senzorul IR frontal
#define IR_SENSOR_LEFT A4  // Pinul pentru senzorul IR stânga
#define IR_SENSOR_RIGHT A5 // Pinul pentru senzorul IR dreapta

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   
String lastTurnDirection = "";
boolean robotActive = false;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(IR_SENSOR_FRONT, INPUT);  // Senzor IR frontal
  pinMode(IR_SENSOR_LEFT, INPUT);   // Senzor IR stânga
  pinMode(IR_SENSOR_RIGHT, INPUT);  // Senzor IR dreapta
  myservo.attach(10);  
  myservo.write(90); 
  delay(1000);
}

void loop() {
  // Citim senzorii IR
  int irFront = digitalRead(IR_SENSOR_FRONT);
  int irLeft = digitalRead(IR_SENSOR_LEFT);
  int irRight = digitalRead(IR_SENSOR_RIGHT);

  // Activăm robotul doar dacă senzorul IR frontal detectează mișcare
  robotActive = (irFront == LOW);

  if (robotActive) {
    handleSideCollision(irLeft, irRight); // Verificăm senzorii laterali
    avoidObstacle();                      // Verificăm obstacolele din față
  } else {
    moveStop(); // Oprim robotul
  }

  delay(50); // Întârziere pentru stabilitatea senzorilor
}

void handleSideCollision(int irLeft, int irRight) {
  if (irRight == LOW) {  // Obstacol pe stânga - deviază fin spre dreapta
    for (int i = 0; i < 5; i++) { // Repetă de 5 ori o mică deviere
      motor1.setSpeed(90); 
      motor2.setSpeed(120);
      motor3.setSpeed(120);  // Motoarele din partea dreaptă cu viteză ușor mai mică
      motor4.setSpeed(90);

      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);

      delay(20); // Perioadă scurtă pentru o mișcare fină
    }
  } else if (irLeft == LOW) { // Obstacol pe dreapta - deviază fin spre stânga
    for (int i = 0; i < 5; i++) { // Repetă de 5 ori o mică deviere
      motor1.setSpeed(130);   // Motoarele din partea stângă cu viteză ușor mai mică
      motor2.setSpeed(90);
      motor3.setSpeed(130); 
      motor4.setSpeed(90);

      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);

      delay(20); // Perioadă scurtă pentru o mișcare fină
    }
  } else {
    // Dacă nu există obstacole laterale, continuă normal
    motor1.setSpeed(100);
    motor2.setSpeed(100);
    motor3.setSpeed(100);
    motor4.setSpeed(100);

    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
}


void avoidObstacle() {
  distance = readPing();  
  if (distance < 40) { 
    moveStop();        
    soundBuzzer();     

    int distanceR = lookRight(); 
    delay(200);  
    int distanceL = lookLeft();   

    if (distanceR > distanceL) {
      turnRightForDuration(550); 
      lastTurnDirection = "RIGHT";
    } else {
      turnLeftForDuration(500);   
      lastTurnDirection = "LEFT";
    }

    moveForwardDistance(30);  

    // Revenim pe traseul inițial
    if (lastTurnDirection == "RIGHT") {
      turnLeftForDuration(800);  
    } else if (lastTurnDirection == "LEFT") {
      turnRightForDuration(650);
    }

    moveForwardDistance(20); 

    // Mică corecție pentru aliniere
    if (lastTurnDirection == "RIGHT") {
      turnRightForDuration(400); 
    } else if (lastTurnDirection == "LEFT") {
      turnLeftForDuration(350);  
    }

    moveForward(); 
  } else {
    moveForward(); 
  }
}

void moveForwardDistance(int distance) {
  unsigned long startTime = millis();
  unsigned long travelTime = (distance * 1000) / 25;

  while (millis() - startTime < travelTime) {
    motor1.setSpeed(120);
    motor2.setSpeed(120);
    motor3.setSpeed(120);
    motor4.setSpeed(120);

    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void turnRightForDuration(unsigned long duration) {
  motor1.setSpeed(120); 
  motor2.setSpeed(120);  
  motor3.setSpeed(120);
  motor4.setSpeed(120);

  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(duration);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void turnLeftForDuration(unsigned long duration) {
  motor1.setSpeed(140);  
  motor2.setSpeed(120);   
  motor3.setSpeed(120);   
  motor4.setSpeed(140);   

  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  delay(duration);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

int lookRight() {
  myservo.write(30);  
  delay(500);  
  int distance = readPing();
  myservo.write(90);  
  return distance;
}

int lookLeft() {
  myservo.write(160);  
  delay(500);  
  int distance = readPing();
  myservo.write(90);  
  return distance;
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveForward() {
  if (robotActive && !goesForward) { 
    goesForward = true;
    motor1.setSpeed(90); 
    motor2.setSpeed(90);
    motor3.setSpeed(90);
    motor4.setSpeed(90);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    delay(100); 
    
    for (speedSet = 50; speedSet < MAX_SPEED; speedSet += 2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  goesForward = false; 
}

void soundBuzzer() {
  for (int i = 0; i < 40; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
    delay(50);
  }
}
