#include "Sunset_watchface.h"

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

#define IND_GLYPH_HEIGHT 10
#define IND_GLYPH_WIDTH  10

#define DATE_OFFSET 10
#define TAU (2 * PI)

// 'Sun_Symbol', 20x20px
const unsigned char epd_bitmap_Sun_Symbol [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00, 0x04, 0x22, 0x00, 0x02, 0x04, 0x00, 0x20, 
  0xf0, 0x40, 0x13, 0xfc, 0x80, 0x03, 0xfc, 0x00, 0x37, 0xfe, 0xc0, 0x07, 0xfe, 0x00, 0x07, 0xfe, 
  0x00, 0x37, 0xfe, 0xc0, 0x03, 0xfc, 0x00, 0x03, 0xfc, 0x00, 0x10, 0xf0, 0x80, 0x20, 0x00, 0x40, 
  0x02, 0x44, 0x00, 0x04, 0x42, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00
};
// 'Moon_Symbol', 20x20px
const unsigned char epd_bitmap_Moon_Symbol [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x0e, 0x00, 0x00, 
  0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x0f, 
  0x80, 0x00, 0x0f, 0x80, 0x00, 0x1f, 0x00, 0x0c, 0x7f, 0x00, 0x07, 0xfe, 0x00, 0x03, 0xfc, 0x00, 
  0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Sunset_Sunrise_Symbol', 20x20px
const unsigned char epd_bitmap_Sunset_Sunrise_Symbol [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00, 0x04, 0x22, 0x00, 0x02, 0x04, 0x00, 0x20, 
  0xf0, 0x40, 0x13, 0xfc, 0x80, 0x03, 0xfc, 0x00, 0x37, 0xfe, 0xc0, 0x07, 0xfe, 0x00, 0x30, 0xf0, 
  0xc0, 0xc0, 0x00, 0x30, 0x08, 0x01, 0x00, 0x11, 0x08, 0x80, 0x21, 0x08, 0x40, 0x41, 0x08, 0x20, 
  0x02, 0x04, 0x00, 0x02, 0x04, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00
};
// 'Day_Pin', 20x20px
const unsigned char epd_bitmap_Day_Pin [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Night_Pin', 20x20px
const unsigned char epd_bitmap_Night_Pin [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x90, 0x00, 0x00, 0x90, 
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Sunrise_Sunset_Pin', 20x20px
const unsigned char epd_bitmap_Sunrise_Sunset_Pin [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0xb0, 0x00, 0x00, 0xd0, 
  0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


// 'Battery1', 12x10px
const unsigned char epd_bitmap_Battery1 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xe0, 0x10, 0xe0, 0x10, 0xe0, 0x10, 0xe0, 0x10, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};
// 'Battery2', 12x10px
const unsigned char epd_bitmap_Battery2 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xf0, 0x10, 0xf0, 0x10, 0xf0, 0x10, 0xf0, 0x10, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};
// 'Battery0', 12x10px
const unsigned char epd_bitmap_Battery0 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xc0, 0x10, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};
// 'Battery3', 12x10px
const unsigned char epd_bitmap_Battery3 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xf8, 0x10, 0xf8, 0x10, 0xf8, 0x10, 0xf8, 0x10, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};
// 'Battery4', 12x10px
const unsigned char epd_bitmap_Battery4 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xfc, 0x10, 0xfc, 0x10, 0xfc, 0x10, 0xfc, 0x10, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};
// 'Battery5', 12x10px
const unsigned char epd_bitmap_Battery5 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xfe, 0x10, 0xfe, 0x10, 0xfe, 0x10, 0xfe, 0x10, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};
// 'Battery6', 12x10px
const unsigned char epd_bitmap_Battery6 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xff, 0x10, 0xff, 0x10, 0xff, 0x10, 0xff, 0x10, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};
// 'Battery7', 12x10px
const unsigned char epd_bitmap_Battery7 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xff, 0x90, 0xff, 0x90, 0xff, 0x90, 0xff, 0x90, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};
// 'Battery8', 12x10px
const unsigned char epd_bitmap_Battery8 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xff, 0xd0, 0xff, 0xd0, 0xff, 0xd0, 0xff, 0xd0, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};
// 'Battery9', 12x10px
const unsigned char epd_bitmap_Battery9 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xff, 0xe0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00
};

const unsigned char* epd_bitmap_battery_val [] PROGMEM = {
  epd_bitmap_Battery1,
  epd_bitmap_Battery2,
  epd_bitmap_Battery3,
  epd_bitmap_Battery4,
  epd_bitmap_Battery5,
  epd_bitmap_Battery6,
  epd_bitmap_Battery7,
  epd_bitmap_Battery8,
  epd_bitmap_Battery9,
  epd_bitmap_Battery9,  
};

// 'Bluetooth_Disabled', 10x10px
const unsigned char epd_bitmap_Bluetooth_Disabled [] PROGMEM = {
  0x00, 0x00, 0x40, 0x80, 0x21, 0x00, 0x12, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x12, 0x00, 0x21, 0x00, 
  0x40, 0x80, 0x00, 0x00
};
// 'Bluetooth_Enabled', 10x10px
const unsigned char epd_bitmap_Bluetooth_Enabled [] PROGMEM = {
  0x0c, 0x00, 0x0a, 0x00, 0x29, 0x00, 0x1a, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x1a, 0x00, 0x29, 0x00, 
  0x0a, 0x00, 0x0c, 0x00
};
// 'StepSymbol', 10x10px
const unsigned char epd_bitmap_StepSymbol [] PROGMEM = {
  0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x07, 0x80, 0x3f, 0x80, 0x7f, 0x80, 
  0x3f, 0x00, 0x00, 0x00
};
// 'WIFI_Disabled', 10x10px
const unsigned char epd_bitmap_WIFI_Disabled [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x12, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x12, 0x00, 0x21, 0x00, 
  0x00, 0x00, 0x00, 0x40
};
// 'WIFI_Enabled', 10x10px
const unsigned char epd_bitmap_WIFI_Enabled [] PROGMEM = {
  0x03, 0xc0, 0x0c, 0x00, 0x11, 0xc0, 0x26, 0x00, 0x48, 0xc0, 0x51, 0x00, 0x92, 0x40, 0xa4, 0x80, 
  0xa9, 0x00, 0xaa, 0x40
};


struct sun_times
{
  uint8_t sunrise_hour;
  uint8_t sunset_hour;
};

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
    display.drawBitmap(m_hour_positions[i].x, m_hour_positions[i].y, bitmap, 20, 20, GxEPD_WHITE);
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
    uint32_t stepCount = sensor.getCounter();
    if (currentTime.Hour == 0 && currentTime.Minute == 0)
    {
      sensor.resetStepCounter();
      Steps_History[Current_Day] = stepCount;
      Current_Day = (Current_Day + 1) % DAYS_STEP_HISTORY;
      if(Current_Day == 0)
      {
        Days_For_Average = DAYS_STEP_HISTORY;
      }
      else
      {
        Days_For_Average++;
      }
    }
    display.drawBitmap(STEP_GLYPH_POS_X, STEP_GLYPH_POS_Y, epd_bitmap_StepSymbol, IND_GLYPH_WIDTH, IND_GLYPH_HEIGHT, GxEPD_WHITE);
    display.setCursor(STEP_GLYPH_POS_X + IND_GLYPH_WIDTH + 5, STEP_GLYPH_POS_Y + 10);
    display.print(stepCount);
    display.print(" ");
    display.print(Average_Steps(&Steps_History[0], Days_For_Average));
}

void Sunset_watchface::initPositions()
{
  for(uint32_t i = 0; i < POSITION_DENSITY; i++)
  {
    m_hour_positions[i].x = -sin((i*TAU)/POSITION_DENSITY) * DISPLAY_WIDTH/2.35  + DISPLAY_WIDTH/2  - ROTATIONAL_WATCHFACE_OFFSET_X;
    m_hour_positions[i].y =  cos((i*TAU)/POSITION_DENSITY) * DISPLAY_HEIGHT/2.35 + DISPLAY_HEIGHT/2 - ROTATIONAL_WATCHFACE_OFFSET_Y;
  }
  memset(&Steps_History[0], 0, sizeof(Steps_History));
  Current_Day = 0;
  Days_For_Average = 0;
}

void Sunset_watchface::handleButtonPositions()
{
 uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
  // Menu Button
  if (wakeupBit & MENU_BTN_MASK) {
    if (guiState ==
        WATCHFACE_STATE) { // enter menu state if coming from watch face
      showMenu(menuIndex, false);
    } else if (guiState ==
               MAIN_MENU_STATE) { // if already in menu, then select menu item
      switch (menuIndex) {
      case 0:
        showAbout();
        break;
      case 1:
        showBuzz();
        break;
      case 2:
        showAccelerometer();
        break;
      case 3:
        setTime();
        break;
      case 4:
        setupWifi();
        break;
      case 5:
        showUpdateFW();
        break;
      case 6:
        showSyncNTP();
        break;
      default:
        break;
      }
    } else if (guiState == FW_UPDATE_STATE) {
      updateFWBegin();
    }
  }
  // Back Button
  else if (wakeupBit & BACK_BTN_MASK) {
    if (guiState == MAIN_MENU_STATE) { // exit to watch face if already in menu
      RTC.read(currentTime);
      showWatchFace(false);
    } else if (guiState == APP_STATE) {
      showMenu(menuIndex, false); // exit to menu if already in app
    } else if (guiState == FW_UPDATE_STATE) {
      showMenu(menuIndex, false); // exit to menu if already in app
    } else if (guiState == WATCHFACE_STATE) {
      return;
    }
  }
  // Up Button
  else if (wakeupBit & UP_BTN_MASK) {
    if (guiState == MAIN_MENU_STATE) { // increment menu index
      menuIndex--;
      if (menuIndex < 0) {
        menuIndex = MENU_LENGTH - 1;
      }
      showMenu(menuIndex, true);
    } else if (guiState == WATCHFACE_STATE) {
      return;
    }
  }
  // Down Button
  else if (wakeupBit & DOWN_BTN_MASK) {
    if (guiState == MAIN_MENU_STATE) { // decrement menu index
      menuIndex++;
      if (menuIndex > MENU_LENGTH - 1) {
        menuIndex = 0;
      }
      showMenu(menuIndex, true);
    } else if (guiState == WATCHFACE_STATE) {
      return;
    }
  }

  /***************** fast menu *****************/
  bool timeout     = false;
  long lastTimeout = millis();
  pinMode(MENU_BTN_PIN, INPUT);
  pinMode(BACK_BTN_PIN, INPUT);
  pinMode(UP_BTN_PIN, INPUT);
  pinMode(DOWN_BTN_PIN, INPUT);
  while (!timeout) {
    if (millis() - lastTimeout > 5000) {
      timeout = true;
    } else {
      if (digitalRead(MENU_BTN_PIN) == 1) {
        lastTimeout = millis();
        if (guiState ==
            MAIN_MENU_STATE) { // if already in menu, then select menu item
          switch (menuIndex) {
          case 0:
            showAbout();
            break;
          case 1:
            showBuzz();
            break;
          case 2:
            showAccelerometer();
            break;
          case 3:
            setTime();
            break;
          case 4:
            setupWifi();
            break;
          case 5:
            showUpdateFW();
            break;
          case 6:
            showSyncNTP();
            break;
          default:
            break;
          }
        } else if (guiState == FW_UPDATE_STATE) {
          updateFWBegin();
        }
      } else if (digitalRead(BACK_BTN_PIN) == 1) {
        lastTimeout = millis();
        if (guiState ==
            MAIN_MENU_STATE) { // exit to watch face if already in menu
          RTC.read(currentTime);
          showWatchFace(false);
          break; // leave loop
        } else if (guiState == APP_STATE) {
          showMenu(menuIndex, false); // exit to menu if already in app
        } else if (guiState == FW_UPDATE_STATE) {
          showMenu(menuIndex, false); // exit to menu if already in app
        }
      } else if (digitalRead(UP_BTN_PIN) == 1) {
        lastTimeout = millis();
        if (guiState == MAIN_MENU_STATE) { // increment menu index
          menuIndex--;
          if (menuIndex < 0) {
            menuIndex = MENU_LENGTH - 1;
          }
          showFastMenu(menuIndex);
        }
      } else if (digitalRead(DOWN_BTN_PIN) == 1) {
        lastTimeout = millis();
        if (guiState == MAIN_MENU_STATE) { // decrement menu index
          menuIndex++;
          if (menuIndex > MENU_LENGTH - 1) {
            menuIndex = 0;
          }
          showFastMenu(menuIndex);
        }
      }
    }
  }
}
