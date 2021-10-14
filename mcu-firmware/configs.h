#ifndef CONFIGS_H_
#define CONFIGS_H_

#include "hal.h"

#define ICU_TIMER_FREQ      1e6
#define SPEED_OF_SOUND      343.2f

#define SONAR_ECHO_LINE     PAL_LINE(GPIOA, 0)
#define SONAR_TRIG_LINE     PAL_LINE(GPIOA, 9)
#define SONAR_THRESHOLD     0.1f

typedef struct
{
    float width;
    float period;
} ICUValue;

extern ICUValue sonarBuffer;
extern const ICUConfig sonarICUConfig;

float sonarRead(void);

#endif
