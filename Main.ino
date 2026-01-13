#include <LiquidCrystal_I2C.h> // needs initialising in the arduino app
LiquidCrystal_I2C lcd(0x27, 16, 20);

    const int dcMotorPin = 2;
    bool motorValue = false;
    int onDuration;

    const int redLED = 3;
    const int greenLED = 4;

    const int lightSensor = A2;
    int lightValue;

    const int emergencyStop = 5;
    int  emergencyStopValue;
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
    lightValue = analodRead(lightSensor);

    emergencyStopValue = analogRead(emergencyStop);
    continueValue = analogRead(continueButton);
    smallValue = analogRead(smallValue);
    mediumValue = analogRead(mediumValue);
    if(continueValue == 1) {
        while(lightValue > 800) { // adjust number for lightness (higher is darker)
                lcd.clear();
                lcd.setCursor(0,0); 
                lcd.print("place suitcase");
                lcd.setCursor(0,1); 
                lcd.print("on machine");
        } 
        lcd.clear()
        lcd.setCursor(0,0); 
        lcd.print("option selected:");
        lcd.setCursor(0,1);
        lcd.print("continue");

        digitalWrite(dcMotorPin, HIGH);
        motorValue == true;
    }
}

