#ifndef SUNSET_WATCHY_H
#define SUNSET_WATCHY_H

#include <Watchy.h>

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
    uint16_t Steps_History [DAYS_STEP_HISTORY];
    uint8_t Current_Day;
    uint8_t Days_For_Average;
    using Watchy::Watchy;
    public:
        virtual void drawWatchFace();
        void initPositions();
};

#endif /* SUNSET_WATCHY_H */
