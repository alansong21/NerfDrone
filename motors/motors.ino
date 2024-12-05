#include <Servo.h>

Servo myservo;  // create servo object to control a servo

// Motor A 
int pwmA = 5;
int in1A = 3;
int in2A = 4;
 
// Motor B
 
int pwmB = 6;
int in1B = 7;
int in2B = 8;

// Motors on
bool motorsOn = false;
 
// Reading data
int incomingByte = 0;

void setup() 
{
  // Initialize Serial
  Serial.begin(9600);

  // Set all the motor control pins to outputs
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(0); 

}
 
void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
  }

  if (incomingByte == 'f') {
    motorsOn = !motorsOn;

    if (motorsOn) {
      Serial.println("turning on!");
      // Set Motor A forward
      digitalWrite(in1A, LOW);
      digitalWrite(in2A, HIGH);
    
      // Set Motor B forward
      digitalWrite(in1B, LOW);
      digitalWrite(in2B, HIGH);

      // Set the motor speeds
      analogWrite(pwmA, 255);
      analogWrite(pwmB, 255);
      incomingByte = 0;
    }
    else {
      Serial.println("turning off!");
      analogWrite(pwmA, 0);
      analogWrite(pwmB, 0);
      incomingByte = 0;
    }
  }

  else if (incomingByte == 's') {
     // Reset servo
    delay(500); 
    myservo.write(100); // Actuate servo (push bullet)
    delay(1000);
    myservo.write(0);
    incomingByte = 0;
  }

}

