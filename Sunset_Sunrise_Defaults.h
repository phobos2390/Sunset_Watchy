#ifndef SUNSET_WATCHFACE_SUNSET_SUNRISE_DEFAULTS_H
#define SUNSET_WATCHFACE_SUNSET_SUNRISE_DEFAULTS_H
#include <stdint.h>

///
/// @brief Data definitions for the best guess for any given sunset and sunrise
///
/// @author James Larsen
/// @date 2023 June 20
///

struct sun_times
{
  uint8_t sunrise_hour;
  uint8_t sunset_hour;
};

// Defaults for Pittsburgh PA
const sun_times month_sun [] = {
  { // January
    .sunrise_hour = 7,
    .sunset_hour = 5 + 12
  },
  { // February
    .sunrise_hour = 7,
    .sunset_hour = 6 + 12
  },
  { // March
    .sunrise_hour = 7,
    .sunset_hour = 7 + 12
  },
  { // April
    .sunrise_hour = 7,
    .sunset_hour = 8 + 12
  },
  { // May
    .sunrise_hour = 6,
    .sunset_hour = 8 + 12
  },
  { // June
    .sunrise_hour = 6,
    .sunset_hour = 9 + 12
  },
  { // July
    .sunrise_hour = 6,
    .sunset_hour = 9 + 12
  },
  { // August
    .sunrise_hour = 6,
    .sunset_hour = 8 + 12
  },  
  { // September
    .sunrise_hour = 7,
    .sunset_hour = 8 + 12
  },
  { // October
    .sunrise_hour = 7,
    .sunset_hour = 7 + 12
  },
  { // November
    .sunrise_hour = 7,
    .sunset_hour = 6 + 12
  },
  { // December
    .sunrise_hour = 7,
    .sunset_hour = 5 + 12
  }
};

enum DisplayType
{
  Night,
  Sunset_Sunrise,
  Day
};

DisplayType displaySun(uint8_t hour, uint8_t month);

#endif /* SUNSET_WATCHFACE_SUNSET_SUNRISE_DEFAULTS_H */
