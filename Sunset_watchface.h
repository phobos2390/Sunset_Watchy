#ifndef SUNSET_WATCHY_H
#define SUNSET_WATCHY_H

#include <Watchy.h>
#include <CliTerminal.h>

#define POSITION_DENSITY 24
#define DAYS_STEP_HISTORY 7

struct ScreenPosition
{
    uint8_t x;
    uint8_t y;
};

class Sunset_watchface : public Watchy
{
    using Watchy::Watchy;
    public:
        virtual void drawWatchFace();
        void initPositions();
        void drawBigNumber(uint16_t bigNumber);
};

#endif /* SUNSET_WATCHY_H */
