#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
  private:
    // sentido == 0 ==> cw, sentido == 1 ==> ccw
    int velocidad = 0;
    int pin1;
    int pin2;

  public:
    Motor(int, int);
    void setPins(int, int);
    int getPin1();
    int getPin2();
    void setVelocidad(int);
    int getVelocidad();
};

#endif