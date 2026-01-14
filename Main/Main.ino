#include <LiquidCrystal_I2C.h> // needs initialising in the arduino app
LiquidCrystal_I2C lcd(0x27, 16, 20);

    const int dcMotorPin = 5;
    bool motorValue = false;
    int onDuration;

    const int redLED = 3;
    const int greenLED = 4;

    const int lightSensor = A2;
    int lightValue;

    const int emergencyStop = 2;
    volatile bool emergencyStopValue = false;
    const int continueButton = 6;
    int continueValue;
    const int smallButton = 7;
    int smallValue;
    const int mediumButton = 8;
    int mediumValue;

void setup()
{
    pinMode(dcMotorPin, OUTPUT);
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);

    pinMode(emergencyStop, INPUT);
    attachInterrupt(digitalPinToInterrupt(emergencyStop), stopNow, FALLING);
    pinMode(continueButton, INPUT);
    pinMode(smallButton, INPUT);
    pinMode(mediumButton, INPUT);

    lcd.init(); 
    lcd.backlight(); 
    lcd.setCursor(0,0); 
    lcd.print("Select small, me-"); 
    lcd.setCursor(0,1); 
    lcd.print("dium or continue:"); 
}

void loop()
{
    lightValue = analogRead(lightSensor);

    continueValue = digitalRead(continueButton);
    smallValue = digitalRead(smallValue);
    mediumValue = digitalRead(mediumValue);
    
    
    if (mediumValue ==1 || smallValue ==1 || continueValue == 1) {
    lcd.clear();
    while(lightValue > 800) { // adjust number for lightness (higher is darker)        lcd.setCursor(0,0); 
        lcd.print("place suitcase");
        lcd.setCursor(0,1); 
        lcd.print("on machine      ");
        lightValue = analogRead(lightSensor);
    }
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("option selected:");
    lcd.setCursor(0,1);
    digitalWrite(dcMotorPin, HIGH);
    motorValue = true;
    }

    if(mediumValue == 1) {
        lcd.print("medium"); 
        onDuration =  (10000 + millis()); 
    } else if(smallValue == 1) {
        lcd.print("small"); 
        onDuration =  (5000 + millis()); 
    } else if(continueValue == 1) {
        lcd.print("continue");
        onDuration =  (5000 + millis()); 
    }

    if(motorValue == true) {
        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, LOW);
    } else if(motorValue == false) {
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, HIGH);
    }
    
    if (motorValue && millis() >= onDuration) { 
        digitalWrite(dcMotorPin, LOW);
        motorValue =  false;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("complete");
    }

    if (emergencyStopValue) {
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("emergency stop");
        while (true) {
            digitalWrite(dcMotorPin, LOW);
            motorValue =  false;
            digitalWrite(redLED, LOW);
            digitalWrite(greenLED, HIGH);
        }
    }
}

void stopNow() {
    emergencyStopValue = true;
}