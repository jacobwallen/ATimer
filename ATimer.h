/*
  ATimer.h - Countdown timer object for arduino.
  Created by Jacob Wallen January 17, 2015.
*/

#ifndef ATimer_h
#define ATimer_h

#include "Arduino.h"

class ATimer
{
  public:
    ATimer(unsigned short tickRate);

    // Various Control
    void set_time(unsigned long ms);
    void start();
    void stop();
    void pause();

    // Get methods
    unsigned long get_time();
    unsigned short get_h();
    unsigned char get_m();
    unsigned char get_s();
    unsigned short get_ms();
    unsigned char get_tens(unsigned char value);
    unsigned char get_ones(unsigned char value);

    // Comparison
    bool lessThan(int hour, int minute, int second, int ms);
    bool moreThan(int hour, int minute, int second, int ms);

    // Other
    void serialPrintTime();

    // Vital, run in loop to get timer to tick
    void tick();

  private:
    void _extractHMS();
    unsigned long _currentMillis; // Clocks reference time
    unsigned long _prevMillis; // When was the last tick
    unsigned long _startMillis; // Time when timer was started
    unsigned long _endMillis; // Time when timer ended
    unsigned long _pauseMillis; // Time when pause was started
    unsigned long _time; // Timers total value in ms
    unsigned short _h;
    unsigned char _m;
    unsigned char _s;
    unsigned short _ms; // milliseconds between seconds
    unsigned short _resolution; // How often in ms the timer will subtract time
    bool _run;
    bool _pause;
    bool _idle;
};

#endif
