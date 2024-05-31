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

byte mode = 0;

void setup()
{
    Serial.begin(9600);


    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);

    Serial.println("Setup done");
}


void loop()
{
    if (XBee.available() > 0)
    {
        data = XBee.read();
        Serial.println(data);

        if (data == '1')
        {
            color = 1;
        }
        else if (data == '2')
        {
            color = 2;
        }
        else if (data == '3')
        {
            color = 3;
        }
        else if (data == '4')
        {
            color = 4;
        }
    }
    else if (Serial.available() > 0)
    {
        data = Serial.read();
        Serial.println(data);

        if (data == '1')
        {
            color = 1;
        }
        else if (data == '2')
        {
            color = 2;
        }
        else if (data == '3')
        {
            color = 3;
        }
        else if (data == '4')
        {
            color = 4;
        }
    }


    if (color == 1)
    {
        digitalWrite(green, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(red, HIGH);

    }
    else if (color == 2)
    {
        digitalWrite(green, LOW);
        digitalWrite(yellow, HIGH);
        digitalWrite(red, LOW);

    }
    else if (color == 3)
    {
        digitalWrite(green, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(red, LOW);
    }
    else if (color == 4)
    {
        digitalWrite(green, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(red, LOW);
    }
    else
    {
        digitalWrite(green, HIGH);
        digitalWrite(yellow, HIGH);
        digitalWrite(red, HIGH);
    }
}
