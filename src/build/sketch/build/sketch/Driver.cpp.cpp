#include <Arduino.h>
#line 1 "/home/kuro/Documents/Programming/Robolid2018/src/Driver.cpp"
#line 1 "/home/kuro/Documents/Programming/Robolid2018/src/Driver.cpp"
#include "Driver.h"
#include "Motor.h"

Driver::Driver(Motor *motor1, Motor *motor2, int dif1, int dif2)
{
    motorL = motor1;
    motorR = motor2;
    difL = dif1;
    difR = dif2;
}

void Driver::setMotorL(Motor *motor)
{
    motorL = motor;
}

void Driver::setMotorR(Motor *motor)
{
    motorR = motor;
}
Motor *Driver::getMotorL()
{
    return motorL;
}
Motor *Driver::getMotorR()
{
    return motorR;
}

void Driver::setVelocidadMax(int velocidad)
{
    velocidadMax = velocidad;
}
int Driver::getVelocidadMax()
{
    return velocidadMax;
}
void Driver::setVelocidadMin(int velocidad)
{
    velocidadMin = velocidad;
}
int Driver::getVelocidadMin()
{
    return velocidadMin;
}
void Driver::setVelocidades(int velocidad1, int velocidad2)
{
    int aux;
    if (abs(velocidad1) + difL > velocidadMax)
    {
        aux = velocidadMax;
    }
    else if (abs(velocidad1) + difL < velocidadMin)
    {
        aux = 0;
    }
    else
    {
        aux = velocidad1;
    }

    int aux2;
    if (abs(velocidad2) + difR > velocidadMax)
    {
        aux2 = velocidadMax;
    }
    else if (abs(velocidad2) + difR < velocidadMin)
    {
        aux2 = 0;
    }
    else
    {
        aux2 = velocidad2;
    }

    if (aux <= 0)
    {
        if (aux == 0)
        {
            motorL->setVelocidad(aux);
        }
        else
        {
            motorL->setVelocidad(aux - difL);
        }
    }
    else
    {
        motorL->setVelocidad(aux + difL);
    }
    if (aux2 <= 0)
    {
        if (aux == 0)
        {
            motorR->setVelocidad(aux2);
        }
        else
        {
            motorR->setVelocidad(aux2 - difR);
        }
    }
    else
    {
        motorR->setVelocidad(aux2 + difR);
    }
}
void Driver::stop()
{
    setVelocidades(0, 0);
}

void Driver::setDifL(int dif)
{
    difL = dif;
}

void Driver::setDifR(int dif)
{
    difR = dif;
}

int Driver::getDifL()
{
    return difL;
}

int Driver::getDifR()
{
    return difR;
}
#line 1 "/home/kuro/Documents/Programming/Robolid2018/src/app.ino"
#include "Driver.h"
#include "Motor.h"
#include "NewPing.h"

const int MOTORS[] = {3, 5, 9, 10};
const int NUM_MOTORS = 2;
Motor *motorR = new Motor(3, 5);
Motor *motorL = new Motor(9, 10);
int speedL, speedR;
bool bluetoothToggle = false;
NewPing sonar(11, 12, 400);
Driver driver(motorL, motorR, 18, 0);

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.

  Serial.begin(9600);
  Serial.setTimeout(100);
  for (int i = 0; i < NUM_MOTORS * 2; i++)
  {
    pinMode(MOTORS[i], OUTPUT);
    digitalWrite(MOTORS[i], LOW);
  }
}

// the loop function runs over and over again forever
void loop()
{
  if (bluetoothToggle){
    driver.setVelocidades(speedL, speedR);
  }

  else{
    long distancia = sonar.ping_cm();
    if (distancia <= 30 && distancia != 0)
    {
      driver.stop();
      speedL = -200, speedR = 200;
      driver.setVelocidades(speedL, speedR);
      delay(200);
      long distancia1 = sonar.ping_cm();
      driver.stop();
      speedL = 200, speedR = -200;
      driver.setVelocidades(speedL, speedR);
      delay(400);
      long distancia2 = sonar.ping_cm();
      driver.stop();
      if (distancia1 > distancia2 && distancia1 > 30)
      {
        speedL = -200, speedR = 200;
        driver.setVelocidades(speedL, speedR);
        delay(400);
      }
      else if (distancia1 <= distancia2 && distancia2 > 30)
      {
        speedL = 200, speedR = 200;
        driver.setVelocidades(speedL, speedR);
      }else{
        speedL = -200, speedR = 200;
        driver.setVelocidades(speedL, speedR);
        delay(200);
        speedL = -200, speedR = -200;
        driver.setVelocidades(speedL, speedR);
        delay(100);
      }
    }
    else if (distancia != 0)
    {
      speedL = 200, speedR = 200;
      driver.setVelocidades(speedL, speedR);
    }
  }
}


void serialEvent() {
    char motorIdentifier = (char) Serial.read();
    Serial.println("Char recieved: " + motorIdentifier);

    if (motorIdentifier == 'L') {
        speedL = Serial.parseInt();
        if (speedL == 156){
          speedL = 0;
        }
        else if (speedL > 156){
          speedL = map(speedL, 157, 311, 100, 255);
        }
        else{
          speedL = map(speedL, 0, 155, -255, -100);
        }

        Serial.print("leftMotor is now ");
        Serial.println(speedL);
    }

    
    else if (motorIdentifier == 'R') {
        speedR = Serial.parseInt();
        if (speedR == 156){
          speedR = 0;
        }
        else if (speedR > 156){
          speedR = map(speedR, 157, 311, 100, 255);
        }
        else{
          speedR = map(speedR, 0, 155, -255, -100);
        }
        Serial.print("rightMotor is now ");
        Serial.println(speedR);
    }

    else if (motorIdentifier == 'B') {
      Serial.println("BT TOGGLED");
      bluetoothToggle = !bluetoothToggle;
      speedL = 0, speedR = 0;
    }
}

