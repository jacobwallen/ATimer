#include "Arduino.h"
#include "ATimer.h"

ATimer::ATimer(unsigned short resolution=1000)
{
  _resolution = resolution;
  _run = false;
  _pause = false;
  _idle = true;
}

void ATimer::_extractHMS()
{
  _h = (_time / 3600000);
  _m = ((_time - (_h * 3600000)) / 60000);
  _s = ((_time - (_h * 3600000 + _m * 60000)) / 1000);
  _ms = (_time - (_h * 3600000 + _m * 60000 + _s * 1000));
}

void ATimer::set_time(unsigned long ms)
{
  _time = ms;
  _extractHMS();
}

void ATimer::start()
{
  _run = true;
  _idle = false;
  if (_pause)
  {
    _pause = false;
    _prevMillis = millis();
  }
  else
  {
    _prevMillis = millis();
    _startMillis = _prevMillis;
  }
}

void ATimer::stop()
{
  _endMillis = millis();
  _time = 0;
  _extractHMS();
  _run = false;
  _pause = false;
  _idle = true;
  Serial.print("Timer ran for: ");
  Serial.print(_endMillis - _startMillis);
  Serial.print(" ms\n");
}

void ATimer::pause()
{
  _pauseMillis = _currentMillis - _prevMillis;
  _run = false;
  _pause = true;
}

unsigned long ATimer::get_time()
{
  return _time;
}

unsigned short ATimer::get_h()
{
  return _h;
}

unsigned char ATimer::get_m()
{
  return _m;
}

unsigned char ATimer::get_s()
{
  return _s;
}

unsigned short ATimer::get_ms()
{
  return _ms;
}

unsigned char ATimer::get_tens(unsigned char)
{
  return 0;
}

unsigned char ATimer::get_ones(unsigned char)
{
  return 0;
}

bool ATimer::lessThan(int h,int m,int s,int ms)
{
  return (((h * 3600000) + (m * 60000) + (s * 1000) + ms) > _time);
}

bool ATimer::moreThan(int h,int m,int s,int ms)
{
  return (((h * 3600000) + (m * 60000) + (s * 1000) + ms) < _time);
}

void ATimer::serialPrintTime()
{
  Serial.print("\nATimer: ");
  Serial.print(_h);
  Serial.print(":");
  Serial.print(_m);
  Serial.print(":");
  Serial.print(_s);
  Serial.print(".");
  Serial.print(_ms);
  Serial.print(" \n");
}

void ATimer::tick()
{
  if (_run) // If timer set to tick at all?
  {
    _currentMillis = millis();
    if ((_currentMillis - _prevMillis) >= _resolution) // If a tick has passed
    {
      if ((_time - _resolution) <= 0 || (_time - _resolution) >= 4000000000)
      {
        stop();
      }
      else
      {
        _time = _time - (_currentMillis - _prevMillis); // Tick
        _prevMillis = _currentMillis;
        _extractHMS();
      }
    }
  }
}
