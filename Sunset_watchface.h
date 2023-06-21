#ifndef SUNSET_WATCHY_H
#define SUNSET_WATCHY_H

#include <Watchy.h>
#include "Sunset_Watchface_Stepcounter.h"

#define POSITION_DENSITY 24
#define DAYS_STEP_HISTORY 31

struct ScreenPosition
{
    uint8_t x;
    uint8_t y;
};

class Sunset_watchface : public Watchy
{
    ScreenPosition m_hour_positions [POSITION_DENSITY];
    Step_counter step_counter;
    using Watchy::Watchy;
    public:
        virtual void drawWatchFace();
        void initPositions();
};

#endif /* SUNSET_WATCHY_H */
