short leftMotor = 0, rightMotor = 0;

void setup()
{
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    Serial.begin(115200);

}

void loop()
{
    analogWrite(2, abs(leftMotor));
    analogWrite(3, abs(rightMotor));
    //Serial.println("L: " + (String)leftMotor + "; R: " + (String)rightMotor);

}

String parseSerial(){
    char nextSerial =(char) Serial.read();
    String parsedSerial = "";

    while(nextSerial != ','){
        if (nextSerial == 'L' || nextSerial == 'R'){
            return (String)nextSerial;
        }
        else {
            parsedSerial += nextSerial;
        }
        Serial.print(nextSerial);
        nextSerial = (char) Serial.read();

    }

    return parsedSerial; 
}

void serialEvent(){
    Serial.print("MCHAMMER!");
    int i = 0;
    while (Serial.available()) {
        Serial.println(i++);

        switch (parseSerial()[0]){
            case 'L':   leftMotor = parseSerial().toInt();
                        break;
            case 'R':   rightMotor = parseSerial().toInt();
                        break;
            default:    break;
       }
            
    }
    while(Serial.read() != '\n'){
        ;
    }
}       