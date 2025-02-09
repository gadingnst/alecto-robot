#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trigPin, int echoPin) : trigPin(trigPin), echoPin(echoPin) {}

void Ultrasonic::setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Ultrasonic sensor initialized");
}

long Ultrasonic::measureDistance() {
  // Clear the TRIG_PIN
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the TRIG_PIN high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the ECHO_PIN, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  long distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

bool Ultrasonic::isObjectClose(long thresholdDistance) {
  long distance = measureDistance();
  return distance <= thresholdDistance;
}
