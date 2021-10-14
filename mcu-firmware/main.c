#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "configs.h"

static THD_WORKING_AREA(serialThdWa, 128);
static THD_FUNCTION(serialThd, arg)
{
    (void)arg;

    while(true)
    {
        float dis = sonarRead();
        chprintf((BaseSequentialStream*)&SD2, "DIS %3.3f\n", dis);

        chThdSleepMilliseconds(1000);
    }
}

static THD_WORKING_AREA(alarmThdWa, 128);
static THD_FUNCTION(alarmThd, arg)
{
    (void)arg;

    while(true)
    {
        float dis = sonarRead();

        if(dis < SONAR_THRESHOLD)
            palSetLine(LINE_LED_GREEN);
        else
            palClearLine(LINE_LED_GREEN);

        chThdSleepMilliseconds(10);
    }
}

int main(void)
{
    halInit();
    chSysInit();
    sdInit();

    sdStart(&SD2, NULL);

    palSetLineMode(SONAR_TRIG_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(SONAR_ECHO_LINE, PAL_MODE_ALTERNATE(2));

    icuStart(&ICUD5, &sonarICUConfig);
    icuStartCapture(&ICUD5);
    icuEnableNotifications(&ICUD5);

    chThdCreateStatic(serialThdWa, sizeof(serialThdWa), NORMALPRIO, serialThd, NULL);
    chThdCreateStatic(alarmThdWa, sizeof(alarmThdWa), NORMALPRIO + 1, alarmThd, NULL);

    while (true)
    {
        palWriteLine(SONAR_TRIG_LINE, PAL_HIGH);
        chThdSleepMicroseconds(20);

        palWriteLine(SONAR_TRIG_LINE, PAL_LOW);
        chThdSleepMilliseconds(50);
    }
}
