#include "Robot.h"

Robot::Robot() {}

void Robot::begin() {
  // Attach the servos to the defined GPIO pins
  footLeft.attach(SERVO_FOOT_LEFT_PIN);
  footRight.attach(SERVO_FOOT_RIGHT_PIN);
  legLeft.attach(SERVO_LEG_LEFT_PIN);
  legRight.attach(SERVO_LEG_RIGHT_PIN);

  // Initialize both feet and legs to the vertical position
  footLeft.write(90);
  footRight.write(90);
  legLeft.write(90);
  legRight.write(90);
}

void Robot::moveSmooth(Servo &servo, int startAngle, int endAngle, int delayMs) {
  if (startAngle < endAngle) {
    // Move forward (increase angle)
    for (int angle = startAngle; angle <= endAngle; angle++) {
      servo.write(angle);
      delay(delayMs);
    }
  } else {
    // Move backward (decrease angle)
    for (int angle = startAngle; angle >= endAngle; angle--) {
      servo.write(angle);
      delay(delayMs);
    }
  }
}

void Robot::walkForward() {
  moveSmooth(footRight, 90, 120, 5);  // Lift right foot
  moveSmooth(legRight, 90, 150, 5);   // Move right leg forward

  moveSmooth(footRight, 120, 90, 5);  // Lower right foot
  moveSmooth(legRight, 150, 90, 5);   // Return right leg to initial position

  delay(100);

  moveSmooth(footLeft, 90, 60, 5);    // Lift left foot
  moveSmooth(legLeft, 90, 30, 5);     // Move left leg forward

  moveSmooth(footLeft, 60, 90, 5);    // Lower left foot
  moveSmooth(legLeft, 30, 90, 5);     // Return left leg to initial position

  delay(100);
}

void Robot::moonwalk() {
  moveSmooth(footRight, 90, 60, 5);   // Move right foot backward
  moveSmooth(footLeft, 90, 120, 5);   // Move left foot forward
  moveSmooth(footRight, 60, 90, 5);   // Return right foot to initial position
  moveSmooth(footLeft, 120, 90, 5);   // Return left foot to initial position
  moveSmooth(footRight, 90, 120, 5);  // Move right foot forward
  moveSmooth(footLeft, 90, 60, 5);    // Move left foot backward
}
