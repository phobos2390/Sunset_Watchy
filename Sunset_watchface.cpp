#include "Sunset_watchface.h"
#include "Sunset_Watchface_Pictures.h"
#include "Sunset_Sunrise_Defaults.h"

#define MID_OFFSET 40
#define LINE_HEIGHT 16
#define ROTATIONAL_WATCHFACE_OFFSET_X 10
#define ROTATIONAL_WATCHFACE_OFFSET_Y 10
#define BATTERY_GLYPH_SIZE_HEIGHT 10
#define BATTERY_GLYPH_SIZE_WIDTH 12
#define BATTERY_GLYPH_POS_X 94
#define BATTERY_GLYPH_POS_Y 150
#define BATTERY_VOLT_MAX 4.16
#define BATTERY_VOLT_MIN 3.7

#define WIFI_GLYPH_POS_X 110
#define WIFI_GLYPH_POS_Y 150

#define BLUETOOTH_GLYPH_POS_X 80
#define BLUETOOTH_GLYPH_POS_Y 150

#define STEP_GLYPH_POS_X 60
#define STEP_GLYPH_POS_Y 130

#define DATE_OFFSET 10
#define TAU (2 * PI)

uint16_t Average_Steps(uint16_t* steps_per_day, size_t number_of_days)
{
  uint64_t total = 0;
  for(size_t i = 0; i < number_of_days; i++)
  {
    total += steps_per_day[i];
  }
  return (uint16_t)total/number_of_days;
}

void Sunset_watchface::drawWatchFace()
{
  display.fillScreen(GxEPD_BLACK);
  display.setTextColor(GxEPD_WHITE);
  display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(DISPLAY_WIDTH/2 - MID_OFFSET, DISPLAY_HEIGHT/2 - LINE_HEIGHT);
  uint32_t dispHour = currentTime.Hour % 12;
  char disp_meridian = 'a';
  if(dispHour == 0)
  {
    dispHour = 12;
  }
  if(currentTime.Hour < 10)
  {
    display.print(' ');
  }
  else if(currentTime.Hour >= 12)
  {
    disp_meridian = 'p';
  }
  display.print(dispHour);
  display.print(':');
  if(currentTime.Minute < 10)
  {
    display.print('0');
  }
  display.print(currentTime.Minute);
  display.print(' ');
  display.print(disp_meridian);
  display.print('m');
  display.setCursor(DISPLAY_WIDTH/2 - MID_OFFSET - DATE_OFFSET, DISPLAY_HEIGHT/2 + LINE_HEIGHT);
  display.print(1970 + currentTime.Year);
  display.print(' ');
  if(currentTime.Month < 10)
  {
    display.print('0');
  }
  display.print(currentTime.Month);
  display.print(' ');
  if(currentTime.Day < 10)
  {
    display.print('0');
  }
  display.print(currentTime.Day);

  for(uint32_t i = 0; i < POSITION_DENSITY; i++)
  {
    DisplayType type = displaySun(i, currentTime.Month);
    const unsigned char* bitmap = NULL;
    if(i != currentTime.Hour)
    {
      switch(type)
      {
        case Day:
          bitmap = epd_bitmap_Day_Pin;
          break;
        case Sunset_Sunrise:
          bitmap = epd_bitmap_Sunrise_Sunset_Pin;
          break;
        case Night:
        default:
          bitmap = epd_bitmap_Night_Pin;
          break;
      }
    }
    else
    {
      switch(type)
      {
        case Day:
          bitmap = epd_bitmap_Sun_Symbol;
          break;
        case Sunset_Sunrise:
          bitmap = epd_bitmap_Sunset_Sunrise_Symbol;
          break;
        case Night:
        default:
          bitmap = epd_bitmap_Moon_Symbol;
          break;
      }
    }
    display.drawBitmap(m_hour_positions[i].x, m_hour_positions[i].y, bitmap, OUTER_SYMBOL_WIDTH, OUTER_SYMBOL_HEIGHT, GxEPD_WHITE);
  }

  const unsigned char* wifi_symbol = epd_bitmap_WIFI_Disabled;
  if(WIFI_CONFIGURED)
  {
    wifi_symbol = epd_bitmap_WIFI_Enabled;
  }
  display.drawBitmap(WIFI_GLYPH_POS_X, WIFI_GLYPH_POS_Y, wifi_symbol, IND_GLYPH_WIDTH, IND_GLYPH_HEIGHT, GxEPD_WHITE);

  const unsigned char* bluetooth_symbol = epd_bitmap_Bluetooth_Disabled;
  if(BLE_CONFIGURED)
  {
    bluetooth_symbol = epd_bitmap_Bluetooth_Enabled;
  }
  display.drawBitmap(BLUETOOTH_GLYPH_POS_X, BLUETOOTH_GLYPH_POS_Y, bluetooth_symbol, IND_GLYPH_WIDTH, IND_GLYPH_HEIGHT, GxEPD_WHITE);

  uint8_t voltPerdec = (uint8_t)(((getBatteryVoltage() - BATTERY_VOLT_MIN) / (BATTERY_VOLT_MAX - BATTERY_VOLT_MIN)) * 10);
  display.drawBitmap(BATTERY_GLYPH_POS_X, 
                     BATTERY_GLYPH_POS_Y, 
                     epd_bitmap_battery_val[voltPerdec], 
                     BATTERY_GLYPH_SIZE_WIDTH, 
                     BATTERY_GLYPH_SIZE_HEIGHT, 
                     GxEPD_WHITE);


    // reset step counter at midnight
    if (currentTime.Hour == 0 && currentTime.Minute == 0)
    {
      step_counter.Next_Day();
    }
    display.drawBitmap(STEP_GLYPH_POS_X, STEP_GLYPH_POS_Y, epd_bitmap_StepSymbol, IND_GLYPH_WIDTH, IND_GLYPH_HEIGHT, GxEPD_WHITE);
    display.setCursor(STEP_GLYPH_POS_X + IND_GLYPH_WIDTH + 5, STEP_GLYPH_POS_Y + 10);
    display.print(step_counter.Get_Step_Count());
    display.print(" ");
    display.print(step_counter.Get_Average_Step_Count());
}

void Sunset_watchface::initPositions()
{
  for(uint32_t i = 0; i < POSITION_DENSITY; i++)
  {
    m_hour_positions[i].x = -sin((i*TAU)/POSITION_DENSITY) * DISPLAY_WIDTH/2.35  + DISPLAY_WIDTH/2  - ROTATIONAL_WATCHFACE_OFFSET_X;
    m_hour_positions[i].y =  cos((i*TAU)/POSITION_DENSITY) * DISPLAY_HEIGHT/2.35 + DISPLAY_HEIGHT/2 - ROTATIONAL_WATCHFACE_OFFSET_Y;
  }
}

//*/
