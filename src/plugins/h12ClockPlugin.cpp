#include "plugins/h12ClockPlugin.h"

void h12ClockPlugin::setup()
{
  Screen.clear();
  // loading screen
  Screen.setPixel(4, 4, 1);
  Screen.setPixel(4, 5, 1);
  Screen.setPixel(7, 4, 1);
  Screen.setPixel(7, 5, 1);
  Screen.setPixel(11, 4, 1);
  Screen.setPixel(11, 5, 1);

  previousMinutes = -1;
  previousHour = -1;
}

void h12ClockPlugin::loop()
{
  if (getLocalTime(&timeinfo))
  {
    //if (previousMinutes != timeinfo.tm_min)
    //{
      std::vector<int> hh = {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10};
      bool AMPM=0;
      if (timeinfo.tm_hour > 12) 
      {
        hh.at(0) -= 1;
        hh.at(1) -= 2;
        AMPM = 1;
      }
      std::vector<int> mm = {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10};
      std::vector<int> mday = {(timeinfo.tm_mday - timeinfo.tm_mday % 10) / 10, timeinfo.tm_mday % 10};
      std::vector<int> mom = {(timeinfo.tm_mon + 1) - (timeinfo.tm_mon + 1) % 10, (timeinfo.tm_mon + 1) % 10};
      //analogWrite(PIN_ENABLE, 255);
      Screen.clear();
      Screen.ScreenIsUpdated = false;
      //time hh:mm
      Screen.drawCharacter(2, 0, Screen.readBytes(midNumbers[hh.at(1)]), 4);
      bool leadingZero = (hh.at(0) == 0);
      if (!leadingZero) {
        Screen.drawLine(0, 0, 0, 5, 1);
      }
      if (AMPM) {
        Screen.drawLine(1, 6, 1, 9, 1, 32);
        Screen.setPixel(2, 6, 1, 32);
        Screen.setPixel(2, 8, 1, 32);
        Screen.drawLine(3, 6, 3, 8, 1, 32);
        Screen.drawLine(5, 6, 5, 9, 1, 32);
        Screen.setPixel(6, 7, 1, 32);
        Screen.drawLine(7, 6, 7, 9, 1, 32);
      }
      else {
        Screen.drawLine(1, 7, 1, 9, 1, 32);
        Screen.setPixel(2, 6, 1, 32);
        Screen.setPixel(2, 8, 1, 32);
        Screen.drawLine(3, 7, 3, 8, 1, 32);
        Screen.drawLine(5, 6, 5, 9, 1, 32);
        Screen.setPixel(6, 7, 1, 32);
        Screen.drawLine(7, 6, 7, 9, 1, 32);
      }
      Screen.drawCharacter(7, 0, Screen.readBytes(midNumbers[mm.at(0)]), 4);
      Screen.drawCharacter(12, 0, Screen.readBytes(midNumbers[mm.at(1)]), 4);
      //add separation dots between hh und mm (hh:mm)
      Screen.setPixel(6, 1, 1, 32);
      Screen.setPixel(6, 4, 1, 32);

      //date dd.mm.yy
      leadingZero = (mday.at(0) == 0);
      if (leadingZero) {
        mday.erase(mday.begin());
        Screen.drawNarrowNumbers(4, 11, mday);
      }
      else {
        Screen.drawNarrowNumbers(0, 11, mday);
      }
      leadingZero = (mom.at(0) == 0);
      if (leadingZero) {
        mom.erase(mom.begin());
        Screen.drawNarrowNumbers(12, 11, mom);
      }
      else {
        Screen.drawNarrowNumbers(8, 11, mom);
      }
      //int year = timeinfo.tm_year - 100;
      //Screen.drawNarrowNumbers(16, 9, {(year - year % 10) / 10, year % 10});
      //add separation dots between dd und mm (dd.mm.)
      Screen.setPixel( 7, 15, 1, 32);
      Screen.setPixel(15, 15, 1, 32);
      Screen.ScreenIsUpdated = true;
    //}

    previousMinutes = timeinfo.tm_min;
    previousHour = timeinfo.tm_hour;
  }
}

const char *h12ClockPlugin::getName() const
{
  return "h12Clock";
}
