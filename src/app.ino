const int MOTORPIN = 5;
const int MOTORPIN2 = 3;
int speed = 200;

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(MOTORPIN, OUTPUT);
  pinMode(MOTORPIN2, OUTPUT);
  digitalWrite(MOTORPIN, HIGH);
  digitalWrite(MOTORPIN2, HIGH);
}

// the loop function runs over and over again forever
void loop()
{
  digitalWrite(MOTORPIN, LOW);
  digitalWrite(MOTORPIN2, LOW);
  for (int speed = 140; speed <= 255; speed += 10)
  {
    analogWrite(MOTORPIN, speed);

    delay(1000);
  }

  digitalWrite(MOTORPIN, LOW);
  digitalWrite(MOTORPIN2, LOW);
  for (int speed = 140; speed <= 255; speed += 10)
  {
    analogWrite(MOTORPIN2, speed);

    delay(1000);
  }
}