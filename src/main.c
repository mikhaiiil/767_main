#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include "Control.h"
#include "SteerAngle.h"
#include "serial.h"
#include "experiments.h"

#define EXPERIMENT_TYPE EXPERIMENT_STEER_LEFT

int main(void)
{
    chSysInit();
    halInit();
    ControlInit();
    SteerAngleInit();
    SerialInit();


    while (true)
    {

#if (EXPERIMENT_TYPE == EXPERIMENT_STEER_LEFT)
    experiment_steer_left();
#elif (EXPERIMENT_TYPE == EXPERIMENT_STEER_RIGHT)
    experiment_steer_right();
#endif

    }
}
