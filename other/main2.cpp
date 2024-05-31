#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial XBee(2, 3);

byte switchbtn = 4;
byte red = 6;
byte yellow = 7;
byte green = 8;

byte delayRed = 5;       // Time in seconds that the traffic light will be red
byte delayYellow = 2;    // Time in seconds that the traffic light will be yellow
byte delayGreen = 5;     // Time in seconds that the traffic light will be green
boolean onedelay = true; // If true, the traffic light will only have one delay
byte delaytime = 3;      // Time in seconds that the traffic light will be on (only if onedelay is true)

byte color = 4; // The colour that the program init | Usage: 1= red, 2 = yellow, 3 = green 4= OFF

byte mode = 0;

void request(int payload)
{
    Serial.print(payload);
    XBee.print(payload);
}

void setup()
{
    Serial.begin(9600);
    if (onedelay)
    {
        delayRed = delaytime;
        delayYellow = delaytime;
        delayGreen = delaytime;
    }
    pinMode(switchbtn, INPUT);
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);

    request(mode);
}

void TraficLight()
{

    if (color == 1)
    {
        color = 3;
    }
    else if (color == 3)
    {
        color = 2;
    }
    else if (color == 2)
    {
        color = 1;
    }
    else
    {
        color = 1;
    }
}

int switchState = 0;

void OrangeLight()
{

    if (color == 2)
    {
        color = 4;
    }
    else if (color == 4)
    {
        color = 2;
    }
    else
    {
        color = 2;
    }
}
void loop()
{
    switchState = digitalRead(switchbtn);
    if (switchState == HIGH)
    {
        if (mode != 2)
        {
            mode = 2;
        }
    }
    else if (switchState == LOW)
    {
        if (mode != 1)
        {
            mode = 1;
        }
    }
    if (mode == 1)
    {
        TraficLight();
    }
    else if (mode == 2)
    {
        OrangeLight();
    }
    else
    {
        color = 4;
    }

    request(color);

    if (color == 1)
    {
        digitalWrite(green, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(red, HIGH);

        delay(delayRed * 1000);
    }
    else if (color == 2)
    {
        digitalWrite(green, LOW);
        digitalWrite(yellow, HIGH);
        digitalWrite(red, LOW);

        delay(delayYellow * 1000);
    }
    else if (color == 3)
    {
        digitalWrite(green, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(red, LOW);
        delay(delayGreen * 1000);
    }
    else if (color == 4)
    {
        digitalWrite(green, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(red, LOW);
        delay(delayYellow * 1000);
    }
    else
    {
        digitalWrite(green, HIGH);
        digitalWrite(yellow, HIGH);
        digitalWrite(red, HIGH);
        delay(1000);
    }
}