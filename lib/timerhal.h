#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f1xx_hal.h"
#include "stdbool.h"
#include "inttypes.h"

struct TimerHal
{
    bool started;
    uint32_t startTime;
    uint32_t period;
};

void TimerHalInit(struct TimerHal *timer);
void TimerHalStart(struct TimerHal *timer, uint32_t period);
static void TimerHalUpdate(struct TimerHal *timer) { timer->startTime = HAL_GetTick(); }
bool TimerHalElapsed(struct TimerHal *timer);

#endif /* _TIMER_H */