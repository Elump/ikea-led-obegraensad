#include "plugins/ClockLinePlugin.h"

void ClockLinePlugin::setup()
{
  // loading screen
  Screen.setPixel(4, 7, 1);
  Screen.setPixel(5, 7, 1);
  Screen.setPixel(7, 7, 1);
  Screen.setPixel(8, 7, 1);
  Screen.setPixel(10, 7, 1);
  Screen.setPixel(11, 7, 1);

  previousMinutes = -1;
  previousHour = -1;
}

void ClockLinePlugin::loop()
{
  if (getLocalTime(&timeinfo))
  {
    if (previousHour != timeinfo.tm_hour || previousMinutes != timeinfo.tm_min)
    {
      std::vector<int> hh = {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10};
      std::vector<int> mm = {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10};
      std::vector<int> mday = {(timeinfo.tm_mday - timeinfo.tm_mday % 10) / 10, timeinfo.tm_mday % 10};
      std::vector<int> mom = {(timeinfo.tm_mon + 1) - (timeinfo.tm_mon + 1) % 10, (timeinfo.tm_mon + 1) % 10};
      Screen.ScreenIsUpdated = false;
      Screen.clear();
      analogWrite(PIN_ENABLE, 255);
      //time hh:mm
      bool leadingZero = (hh.at(0) == 0);
      if (leadingZero)
      {
        hh.erase(hh.begin());
        Screen.drawNarrowNumbers(5, 1, hh);
      }
      else
      {
        Screen.drawNarrowNumbers(1, 1, hh);
      }
      Screen.drawNarrowNumbers(9, 1, mm);
      //add separation dots between hh und mm (hh:mm)
      Screen.setPixel(8, 2, 1, 32);
      Screen.setPixel(8, 4, 1, 32);

      //date dd.mm.yy
      leadingZero = (mday.at(0) == 0);
      if (leadingZero)
      {
        mday.erase(mday.begin());
        Screen.drawNarrowNumbers(4, 10, mday);
      }
      else
      {
        Screen.drawNarrowNumbers(0, 10, mday);
      }
      leadingZero = (mom.at(0) == 0);
      if (leadingZero)
      {
        mom.erase(mom.begin());
        Screen.drawNarrowNumbers(12, 10, mom);
      }
      else
      {
        Screen.drawNarrowNumbers(8, 10, mom);
      }
      //int year = timeinfo.tm_year - 100;
      //Screen.drawNarrowNumbers(16, 9, {(year - year % 10) / 10, year % 10});
      //add separation dots between dd und mm (dd.mm.)
      Screen.setPixel( 7, 14, 1, 32);
      Screen.setPixel(15, 14, 1, 32);
      Screen.ScreenIsUpdated = true;
    }

    previousMinutes = timeinfo.tm_min;
    previousHour = timeinfo.tm_hour;
  }
}

const char *ClockLinePlugin::getName() const
{
  return "ClockLine";
}
