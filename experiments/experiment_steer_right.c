/*
 * experiment_steer_right.c
 *
 *  Created on: 01 февр. 2020 г.
 *      Author: user
 */

#include "experiments.h"
#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include "Control.h"
#include "SteerAngle.h"
#include "serial.h"

int SteerRightPowerPercent = -80;
int SteerRightAngleADCval = 0;
int experiment_steer_right_enabled = 0;
int SteerRightPowerisSet = 0;

void experiment_steer_right()
{
            SteerRightAngleADCval = GetSteerAngleADCval();

            systime_t sleep_to_time = chVTGetSystemTime() + MS2ST(2);

            msg_t msg = sdGetTimeout( &SD3, TIME_IMMEDIATE );

            if ( msg >= 0 )
            {
                  uint8_t byte = msg;

                  if ( byte == 1)
                      experiment_steer_right_enabled = 1;

                  else  if (byte == 2)
                      {experiment_steer_right_enabled = 0;
                      ControlSetSteerMotorPower(0);
                      }
            }

            if (experiment_steer_right_enabled == 1)
            {
                if (SteerRightPowerisSet == 0)
                {
                    ControlSetSteerMotorPower(SteerRightPowerPercent);
                    SteerRightPowerisSet = 1;
                }
                uint16_t current_value_adc = SteerRightAngleADCval;
                sdWrite( &SD3, (uint8_t *)&current_value_adc, sizeof( current_value_adc ) );
                chThdSleepUntil(sleep_to_time);
            }
}

