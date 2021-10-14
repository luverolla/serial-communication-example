#include "ch.h"
#include "hal.h"
#include "configs.h"

ICUValue sonarBuffer = {0.0f, 0.0f};

float sonarRead(void)
{
    return SPEED_OF_SOUND * 0.5 * sonarBuffer.width;
}

static void sonarICUCallback(ICUDriver *icud)
{
    sonarBuffer.width = icuGetWidthX(icud) / ICU_TIMER_FREQ;
    sonarBuffer.period = icuGetPeriodX(icud) / ICU_TIMER_FREQ;
}

const ICUConfig sonarICUConfig =
{
    ICU_INPUT_ACTIVE_HIGH,
    ICU_TIMER_FREQ,
    sonarICUCallback,
    NULL,
    NULL,
    ICU_CHANNEL_1,
    0,
    0xFFFFFFFFU,
};
