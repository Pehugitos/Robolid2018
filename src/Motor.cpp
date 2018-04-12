#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int sentido, int velocidad, int pin1, int pin2)
{
    this->sentido = sentido;
    this->velocidad = velocidad;
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

void Motor::setSentido(int sentido)
{
    this->sentido = sentido;
}

int Motor::getSentido()
{
    return sentido;
}

void Motor::setVelocidad(int velocidad)
{
    this->velocidad = velocidad;
    if (sentido == 0)
    {
        analogWrite(pin2, velocidad);
    }
    else
    {
        analogWrite(pin1, velocidad);
    }
}

int Motor::getVelocidad()
{
    return velocidad;
}