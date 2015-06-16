#include "ATimer.h"

ATimer timer(100);
const int ledPin = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  timer.set_time(20000);
  timer.start();
}

void loop()
{
  timer.tick();
  if (timer.get_time() > 0)
  {
    timer.serialPrintTime();
  }
  else
  {
    timer.set_time(12000);
    timer.start();
  }

  if (timer.lessThan(0,0,10,0) && timer.moreThan(0,0,9,499))
  {
    digitalWrite(ledPin, HIGH);
  }
  if (timer.lessThan(0,0,9,500) && timer.moreThan(0,0,8,999))
  {
    digitalWrite(ledPin, LOW);
  }
}
