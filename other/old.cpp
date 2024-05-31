#include <Arduino.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
byte censor = A0;
byte led = 2;
byte btn1 = 6;
byte btn2 = 7;
byte btn3 = 8;
byte btn4 = 5;

// Color settings
byte colordelay = 2;
// btn settings
const int btndelay = 500;
// temp settings
byte minTemp = 15;
byte maxTemp = 30;
// led variable
const int minLedTemp = 18;
const int maxLedTemp = 24;
byte negative = false;
byte settings = false;
byte temp = 20;

byte line = 2;
const char *negativestr = "";

const char *text = "Temperature =";
const char *mode = "confort";

String getline(int line)
{
  if (line == 1)
  {
    return text;
  }
  if (line == 2)
  {
    return negativestr + String(temp) + char(223) + "C" + "     " + mode;
  }
  if (line == 3)
  {
    return "MaxTemp = " + String(maxTemp) + char(223) + "C";
  }
  if(line == 4){
    return  "MinTemp = " + String(minTemp) + char(223) + "C";
  }
  return "";
}
void clearline(int line)
{
  lcd.setCursor(0, line - 1);
  lcd.print("                ");
}
void lcdtext()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(getline(1));
  lcd.setCursor(0, 1);
  lcd.print(getline(line));
  lcd.setRGB(0, 255, 0);
}
void lcdconfig()
{
  lcd.display();
  lcd.setRGB(13, 0, 0);
  lcd.noBlink();
  lcd.noBlinkLED();
}
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(led, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);

  lcdconfig();

  lcdtext();
}
void pressed()
{
  // text = "Button Appuye";
  // lcdtext();
  // text = "Temperature =";
  lcdtext();
  delay(btndelay);
}

void loop()
{

  if (digitalRead(btn1) == HIGH && settings == false)
  {
    digitalWrite(btn1, LOW);
    settings = true;
    text = "Parametre";
    line = 3;
    pressed();
    return;
  }

  if (settings)
  {
    if (digitalRead(btn1) == HIGH && line == 4)
    {
      digitalWrite(btn1, LOW);
      settings = false;
      text = "Temperature =";
      line = 2;
      pressed();
      return;
    }
    if (digitalRead(btn1) == HIGH && line == 3)
    {
      line = 4;
      pressed();
      return;
    }

    if(line == 3){
      if (digitalRead(btn2) == HIGH)
      {
        if (maxTemp == minTemp)
          return;
        maxTemp--;
        pressed();
        return;
      }
      if (digitalRead(btn3) == HIGH)
      {
        maxTemp++;
        pressed();
        return;
      }
    }
    if(line == 4){
      if (digitalRead(btn2) == HIGH)
      {
        if (minTemp == 0)
          return;
        minTemp--;
        pressed();
        return;
      }
      if (digitalRead(btn3) == HIGH)
      {
        if (minTemp == maxTemp)
          return;
        minTemp++;
        pressed();
        return;
      }
    }
  }
  else
  {
    if (minLedTemp < temp && temp < maxLedTemp)
    {
      digitalWrite(led, HIGH);
    }
    else
    {
      digitalWrite(led, LOW);
    }
    if (temp >= maxLedTemp)
    {
      mode = "chaud";
    }
    else if (temp <= minLedTemp)
    {
      mode = "froid";
    }
    else
    {
      mode = "confort";
    }
    if (digitalRead(btn2) == HIGH)
    {
      if (temp == 0 && negative == false)
      {
        temp++;
        negative = true;
        negativestr = "-";
        pressed();
        return;
      }
      if (negative == true && temp < minTemp)
      {
        temp++;
        pressed();
        return;
      }
      if (negative == true && temp == minTemp)
        return;
      temp--;
      pressed();
      return;
    }
    if (digitalRead(btn3) == HIGH)
    {

      if (temp == 0 && negative == true)
      {
        temp++;
        negative = false;
        negativestr = "";
        pressed();
        return;
      }
      if (negative == true && temp > 0)
      {
        temp--;
        pressed();
        return;
      }
      if (negative == true && temp == 0)
        return;
      if (negative == false && temp == maxTemp)
        return;

      temp++;

      pressed();

      return;
    }
  }
}