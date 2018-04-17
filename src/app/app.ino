#include "Motor.h"
const int MOTORS[] = {3, 5, 9, 10};
const int NUM_MOTORS = 2;
Motor *motorR = new Motor(0, 0, 3, 5);
Motor *motorL = new Motor(0, 0, 9, 10);

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  for (int i = 0; i < NUM_MOTORS * 2; i++)
  {
    pinMode(MOTORS[i], OUTPUT);
    digitalWrite(MOTORS[i], LOW);
  }
}

// the loop function runs over and over again forever
void loop()
{
  motorR->setVelocidad(200);
  motorL->setVelocidad(200);
  delay(2000);
  motorR->setVelocidad(0);
  motorL->setVelocidad(0);
  delay(3000);
}