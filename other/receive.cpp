#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
int data;
int data2;
SoftwareSerial XBee(2, 3);
byte red = 6;
byte yellow = 7;
byte green = 8;
byte color = 4; // The colour that the program init | Usage: 1= red, 2 = yellow, 3 = green 4= OFF

byte delayRed = 5;       // Time in seconds that the traffic light will be red
byte delayYellow = 2;    // Time in seconds that the traffic light will be yellow
byte delayGreen = 5;     // Time in seconds that the traffic light will be green
boolean onedelay = true; // If true, the traffic light will only have one delay
byte delaytime = 2;      // Time in seconds that the traffic light will be on (only if onedelay is true)

byte mode = 0;

void setup()
{
    Serial.begin(9600);

    if (onedelay)
    {
        delayRed = delaytime;
        delayYellow = delaytime;
        delayGreen = delaytime;
    }

    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);

    Serial.println("Setup done");
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
    if (XBee.available() > 0)
    {
        data = XBee.read();
        Serial.println(data);
        if (data == '1')
        {
            if (mode != 1)
            {
                mode = 1;
                Serial.println("Trafic Light");
            }
            else
            {
                TraficLight();
                Serial.println("Trafic Light Already On");
            }
        }
        else if (data == '2')
        {
            if (mode != 2)
            {
                mode = 2;
                Serial.println("Orange Light");
            }
            else
            {
                OrangeLight();
                Serial.println("Orange Light Already On");
            }
        }
    }
    else if (Serial.available() > 0)
    {
        data = Serial.read();
        Serial.println(data);

        if (data == '1')
        {
            if (mode != 1)
            {
                mode = 1;
                Serial.println("Trafic Light");
            }
            else
            {
                TraficLight();
                Serial.println("Trafic Light Already On");
            }
        }
        else if (data == '2')
        {
            if (mode != 2)
            {
                mode = 2;
                Serial.println("Orange Light");
            }
            else
            {
                OrangeLight();
                Serial.println("Orange Light Already On");
            }
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
