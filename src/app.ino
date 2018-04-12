#include "Driver.h"
#include "Motor.h"
#include "NewPing.h"

const int MOTORS[] = {3, 5, 9, 10};
const int NUM_MOTORS = 2;
Motor *motorR = new Motor(0, 0, 3, 5);
Motor *motorL = new Motor(0, 0, 9, 10);
NewPing sonar(11, 12, 400);
Driver driver(motorL, motorR, 18, 0);
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  for (int i = 0; i < NUM_MOTORS * 2; i++)
  {
    pinMode(MOTORS[i], OUTPUT);
    digitalWrite(MOTORS[i], LOW);
  }
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop()
{
  driver.setVelocidades(200, 200);
  long distancia = sonar.ping_cm();
  if (distancia <= 30 && distancia != 0)
  {
    driver.stop();
    driver.setVelocidades(-150, 150);
    delay(100);
    driver.stop();
  }
  else if (distancia != 0)
  {

    driver.setVelocidades(200, 200);
  }
  // motorR->setSentido(0);
  // motorL->setSentido(0);
  // motorR->setVelocidad(255);
  // motorL->setVelocidad(255);
  // delay(2000);
  // motorR->setSentido(0);
  // motorL->setSentido(0);
  // motorR->setVelocidad(255);
  // motorL->setVelocidad(180);
  // delay(2000);
  // motorR->setSentido(0);
  // motorL->setSentido(0);
  // motorR->setVelocidad(255);
  // motorL->setVelocidad(255);
  // delay(2000);
  // motorR->setSentido(0);
  // motorL->setSentido(0);
  // motorR->setVelocidad(255);
  // motorL->setVelocidad(180);
  // delay(2000);
  // motorR->setVelocidad(0);
  // motorL->setVelocidad(0);
}