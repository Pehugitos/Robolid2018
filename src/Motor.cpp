#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int pin1, int pin2)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
}

void Motor::setPins(int pin1, int pin2)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
}

int Motor::getPin1()
{
    return pin1;
}

int Motor::getPin2()
{
    return pin2;
}

void Motor::setVelocidad(int velocidad)
{
    this->velocidad = velocidad;
    if (velocidad >= 0)
    {
        analogWrite(pin1, 0);
        analogWrite(pin2, velocidad);
    }
    else
    {
        analogWrite(pin2, 0);
        analogWrite(pin1, -velocidad);
    }
}

int Motor::getVelocidad()
{
    return velocidad;
}