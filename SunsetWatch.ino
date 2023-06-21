#include "Sunset_watchface.h"
#include "settings.h"



Sunset_watchface watchface(settings);

void setup() 
{
  // put your setup code here, to run once:
  watchface.initPositions();
  watchface.init();
}

void loop() {}
