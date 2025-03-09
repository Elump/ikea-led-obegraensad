#include "plugins/BigModClockPlugin.h"

void BigModClockPlugin::setup()
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

void BigModClockPlugin::loop()
{
  if (getLocalTime(&timeinfo))
  {
    //if (previousHour != timeinfo.tm_hour || previousMinutes != timeinfo.tm_min)
    if (previousMinutes != timeinfo.tm_min)
    {
      std::vector<int> mm = {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10};
      Screen.ScreenIsUpdated = false;
      //Screen.clear();
      //analogWrite(PIN_ENABLE, 255);
      Screen.drawRectangle(1, ROWS / 2, 15, 7, 1, 0);

      Screen.drawBigModNumbers(0, ROWS / 2, mm);

      Screen.ScreenIsUpdated = true;

      previousMinutes = timeinfo.tm_min;
    }
    
    if (previousHour != timeinfo.tm_hour)
    {
      std::vector<int> hh = {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10};
      bool leadingZero = (hh.at(0) == 0);
      Screen.ScreenIsUpdated = false;
      //Screen.clear();
      Screen.drawRectangle(1, 0, 15, 8, 1, 0);
      if (leadingZero)
      {
        hh.erase(hh.begin());
        Screen.drawBigModNumbers(COLS / 2, 0, hh);
      }
      else
      {
        Screen.drawBigModNumbers(0, 0, hh);
      }
      Screen.ScreenIsUpdated = true;
      
      previousHour = timeinfo.tm_hour;
    }
  }
}

const char *BigModClockPlugin::getName() const
{
  return "Big Mod. Clock";
}
