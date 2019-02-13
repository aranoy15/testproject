#include "timerhal.h"

void TimerHalInit(struct TimerHal *timer)
{
    timer->started = false;
    timer->period = 0;
    timer->startTime = 0;
}

void TimerHalStart(struct TimerHal *timer, uint32_t period)
{
    timer->started = true;
    timer->startTime = HAL_GetTick();
    timer->period = period;
}

bool TimerHalElapsed(struct TimerHal *timer)
{
    return ((timer->startTime + timer->period) < HAL_GetTick());
}