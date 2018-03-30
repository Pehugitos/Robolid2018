const int MOTORPIN = 3;


void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(MOTORPIN, OUTPUT);
  digitalWrite(MOTORPIN, HIGH);
}

// the loop function runs over and over again forever
void loop()
{
  for(int speed =0; speed<=255; speed++){
      analogWrite(MOTORPIN, speed);
      delay(100);
  }

  // delay(100);
  // analogWrite(3, 0);
  // delay(10000);                       // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(1000);                     // wait for a second
}