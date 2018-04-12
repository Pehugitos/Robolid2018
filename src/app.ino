#include "Driver.h"
#include "Motor.h"
#include "NewPing.h"

const int MOTORS[] = {3, 5, 9, 10};
const int NUM_MOTORS = 2;
Motor *motorR = new Motor(3, 5);
Motor *motorL = new Motor(9, 10);
NewPing sonar(11, 12, 400);
Driver driver(motorL, motorR, 18, 0);
const int  variante = 10;
char last = 'l';

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  for (int i = 0; i < NUM_MOTORS * 2; i++)
  {
    pinMode(MOTORS[i], OUTPUT);
    digitalWrite(MOTORS[i], LOW);
  }
  Serial.begin(9600);
  driver.setVelocidades(200 - variante, 200 + variante);
}

// the loop function runs over and over again forever
void loop()
{
  long distancia = sonar.ping_cm();
  if (distancia <= 30 && distancia != 0)
  {
    driver.setVelocidades(200, 200);
    delay(10);
    driver.stop();
    driver.setVelocidades(-200, 200);
    delay(200);
    long distancia1 = sonar.ping_cm();
    driver.stop();
    driver.setVelocidades(200, -200);
    delay(400);
    long distancia2 = sonar.ping_cm();
    driver.stop();
    if (distancia1 > distancia2)
    {
      driver.setVelocidades(-200, 200);
      delay(400);
    }
  }
  else if (distancia != 0)
  {
    if (last == 'l'){
      driver.setVelocidades(200 + variante, 200 -variante );
      last='r';
    }else{
      driver.setVelocidades(200 - variante, 200 +variante );
      last='l';
    }
    delay(20);
  }
}