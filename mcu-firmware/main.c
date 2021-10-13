#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define SONAR_ECHO PAL_LINE(GPIOA, 0)
#define SONAR_TRIG PAL_LINE(GPIOA, 9)

#define ICU_TIM_FREQ        1e6
#define SSPEED              343.2f

static float lastdistance = 0.0;

static void icuwidthcb(ICUDriver *icup)
{
    palSetLine(LINE_LED_GREEN);
    icucnt_t width = icuGetWidthX(icup);
    lastdistance = (SSPEED * width) / (ICU_TIM_FREQ * 2);

    chprintf((BaseSequentialStream*)&SD2, "RES %3.6f\r\n", lastdistance);
}

static ICUConfig icucfg =
{
    ICU_INPUT_ACTIVE_HIGH,
    ICU_TIM_FREQ,
    icuwidthcb,
    NULL,
    NULL,
    ICU_CHANNEL_1,
    0,
    0xFFFFFFFFU,
};

int main(void)
{
    halInit();
    chSysInit();
    sdInit();

    sdStart(&SD2, NULL);

    palSetLineMode(SONAR_TRIG, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(SONAR_ECHO, PAL_MODE_ALTERNATE(2));

    icuStart(&ICUD5, &icucfg);
    icuStartCapture(&ICUD5);
    icuEnableNotifications(&ICUD5);

    while (true)
    {
        palWriteLine(SONAR_TRIG, PAL_HIGH);
        chThdSleepMicroseconds(20);
        palWriteLine(SONAR_TRIG, PAL_LOW);
        chThdSleepMilliseconds(50);
    }
}
