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
    if (distancia <= 10 && distancia != 0)
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
es        driver.setVelocidades(speedL, speedR);
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
