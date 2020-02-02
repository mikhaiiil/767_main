/*
 * setpower.c
 *
 *  Created on: 25 џэт. 2020 у.
 *      Author: user
 */
#include <ch.h>
#include <hal.h>
#include "Control.h"


/***  PWM configuration pins    ***/
/***  PE9 - Driving wheels      ***/
/***  PE11 - Steering wheels     ***/
#define drivePWMch              0
#define steerPWMch              1

#define pwm1freq                1000000
#define pwm1period              10000


#define STEER_PWM_MAX           1650 //1650    // Left
#define STEER_PWM_NULL          1140
#define STEER_PWM_MIN           500  //650     // Right
#define K_LEFT                  5.1
#define K_RIGHT                 6.4


#define SPEED_MAX               1650
#define SPEED_NULL_FORWARD      1550
#define SPEED_ZERO              1500
#define SPEED_NULL_BACK         1450
#define SPEED_MIN               1350

PWMConfig pwm1conf = {
    .frequency = pwm1freq,
    .period    = pwm1period,
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH,    .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

void ControlInit()
{
    palSetLineMode( PAL_LINE( GPIOE, 11 ),  PAL_MODE_ALTERNATE(1) );
    palSetLineMode( PAL_LINE( GPIOE, 9 ),  PAL_MODE_ALTERNATE(1) );
    pwmStart( &PWMD1, &pwm1conf );
}

void ControlSetSteerMotorPower (int PowerPercent)
{
    int input_skv;

    if (PowerPercent > 0)
    {
        input_skv = STEER_PWM_NULL + K_LEFT * PowerPercent;
    }
    else if (PowerPercent < 0)
    {
        input_skv = STEER_PWM_NULL + K_RIGHT * PowerPercent;
    }
    else if (PowerPercent == 0)
    {
        input_skv = STEER_PWM_NULL;
    }

    if (input_skv >= STEER_PWM_MAX)
        input_skv = STEER_PWM_MAX;

    if (input_skv <= STEER_PWM_MIN)
        input_skv = STEER_PWM_MIN;

    pwmEnableChannel( &PWMD1, steerPWMch, input_skv );

}

void ControlSetSpeedMotorPower (int PowerPercent)
{
    int input_skv;

    if (PowerPercent > 0)
    {
        input_skv = SPEED_NULL_FORWARD + PowerPercent;
    }
    else if (PowerPercent < 0)
    {
        input_skv = SPEED_NULL_BACK + PowerPercent;
    }
    else if (PowerPercent == 0)
    {
        input_skv = SPEED_ZERO;
    }

    if (input_skv >= SPEED_MAX)
            input_skv = SPEED_MAX;

    if (input_skv <= SPEED_MIN)
            input_skv = SPEED_MIN;

    pwmEnableChannel( &PWMD1, drivePWMch, input_skv );
}
