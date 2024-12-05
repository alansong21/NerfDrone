// Set PORTS_TO_USE to determine which set of ports is being used
// PORTS_TO_USE 1 for pins D8-D13
// PORTS_TO_USE 2 for pins A0-A5
// PORTS_TO_USE 3 for pins D0-D7
#define PORTS_TO_USE 3

// Helper library for reading pulse signals from RC receiver
// Download from https://github.com/timoxd7/FastRCReader
#include <FastRCReader.h>
#include <Servo.h>

// CONSTANTS
const byte numInputChannels = 1;
// Each channel is assigned a unique pin determined by PORTS_TO_USE
const uint8_t channelPins[numInputChannels] = {2};

// GLOBALS
Servo myServo;
FastRCReader RC;

// Motor A 
int pwmA = 5;
int in1A = 3;
int in2A = 4;
 
// Motor B
 
int pwmB = 6;
int in1B = 7;
int in2B = 8;
int initialServoPosition = 0;
int firingServoPosition = 100;
int servoPin = 9;

void turnOnFlywheels(bool verbose=false) {
  if (verbose) {
    Serial.println("turning on!");
  }
  // Set Motor A forward
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, HIGH);

  // Set Motor B forward
  digitalWrite(in1B, LOW);
  digitalWrite(in2B, HIGH);

  // Set the motor speeds
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
}

void turnOffFlywheels(bool verbose=false) {
  if (verbose) {
    Serial.println("turning off!");
  }
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
}

void setup() {
  // Initialize serial connection
  Serial.begin(9600);
  // Start RC receiver connection
  RC.begin();
  // Add array of channel pins
  RC.addChannel(channelPins, numInputChannels);

  // Set all the motor control pins to outputs
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);

  myServo.attach(servoPin);  // attaches the servo to the servoPin on the servo object
  myServo.write(initialServoPosition);   // Set servo to default position

  // LED on Arduino
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  unsigned int pulseWidth = RC.getFreq(channelPins[0]); // Get pulse width in microseconds
  // Serial.print(pulseWidth);
  // Serial.println();

  // Check if pulse width is within a valid range
  int code;
  if (pulseWidth >= 1000 && pulseWidth <= 2000) {
    // Map pulse width to a numerical code
    code = map(pulseWidth, 1000, 2000, 0, 3);
    // Serial.print(code);
    // Serial.println();
  }
  // Interpret code received from signal
  switch (code) {
    case 2:
    // Stop the flywheel; reset servo to initial position
    turnOffFlywheels(true);
    myServo.write(initialServoPosition);
    digitalWrite(LED_BUILTIN, LOW);
    break;
    case 1:
    // Spin the flywheel; reset servo to initial position
    turnOnFlywheels(true);
    myServo.write(initialServoPosition);
    digitalWrite(LED_BUILTIN, HIGH);
    break;
    case 0:
    // Spin the flywheel; swing servo to firing position
    
    turnOnFlywheels(true);
    myServo.write(firingServoPosition);
    digitalWrite(LED_BUILTIN, HIGH);
    break;

  }
}


  // // Read all current channel input values into the input array
  // for (int i = 0 ; i < numInputChannels; i++) {
  //   Serial.print(RC.getFreq(channelPins[i]));
  //   if (i < numInputChannels - 1) {
  //     Serial.print(",");
  //   }
  //   delay(1000);
  // }
  // Serial.println();
