#ifndef DRIVER_H
#define DRIVER_H

#include "Motor.h"

class Driver
{
  private:
    Motor *motorL;
    Motor *motorR;
    int velocidadMax = 255;
    int velocidadMin = 0;
    int difR,difL;

  public:
    Driver(Motor *, Motor *, int, int);
    void setMotorL(Motor *);
    void setMotorR(Motor *);
    Motor *getMotorL();
    Motor *getMotorR();
    void setVelocidadMax(int);
    int getVelocidadMax();
    void setVelocidadMin(int);
    int getVelocidadMin();
    void setVelocidades(int, int);
    void setDifL(int);
    void setDifR(int);
    int getDifL();
    int getDifR();
    void stop();
};

#endif