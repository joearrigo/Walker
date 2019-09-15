#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

const float Kp = 1;
const float Ki = 1;
const float iteration_time = 66;

float desired_value = 20;

float error = 0;
float error_prior = 0;
float integral = 0;

float output = 0;

float duration = 0;
float distance = 0;

Servo servo;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  servo.attach(servoPin);

  //Serial.begin(9600); // Starts the serial communication
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034/2;

  pi(distance);

  //Serial.println(output);
}

void pi(float actual_value){
  error = desired_value-actual_value;
  integral = integral+(error*iteration_time);

  output = Kp * error + Ki * integral;
  error_prior = error;
  
  delay(iteration_time);
}
