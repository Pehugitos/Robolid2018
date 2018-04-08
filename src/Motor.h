#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
  private:
    // sentido == 0 ==> cw, sentido == 1 ==> ccw
    int sentido;
    int velocidad;
    int pin1;
    int pin2;

  public:
    Motor(int, int, int, int);
    void setPins(int, int);
    int getPin1();
    int getPin2();
    void setSentido(int);
    int getSentido();
    void setVelocidad(int);
    int getVelocidad();
};

#endif