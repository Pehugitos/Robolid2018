int leftMotor = 0, rightMotor = 0;

void setup()
{
	Serial.begin(9600);
    Serial.setTimeout(100);
}

void loop()
{
}


void serialEvent() {
    char motorIdentifier = (char) Serial.read();
    if (motorIdentifier == 'L') {
        leftMotor = Serial.parseInt();
        Serial.print("leftMotor is now ");
        Serial.println(leftMotor);
    }

    
    else if (motorIdentifier == 'R') {
        rightMotor = Serial.parseInt();
        Serial.print("rightMotor is now ");
        Serial.println(rightMotor);
    }
}

