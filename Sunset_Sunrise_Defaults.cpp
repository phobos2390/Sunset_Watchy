#include "Sunset_Sunrise_Defaults.h"

DisplayType displaySun(uint8_t hour, uint8_t month)
{
  DisplayType retval = Night;
  if ((month_sun[month].sunrise_hour < hour) && (hour < month_sun[month].sunset_hour))
  {
    retval = Day;
  }
  else if ((month_sun[month].sunrise_hour == hour) || (hour == month_sun[month].sunset_hour))
  {
    retval = Sunset_Sunrise;
  }
  return retval;
}