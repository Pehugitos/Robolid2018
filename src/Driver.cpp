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