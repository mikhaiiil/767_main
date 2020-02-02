/*
 * serial.c
 *
 *  Created on: 01 февр. 2020 г.
 *      Author: user
 */
#include <ch.h>
#include <hal.h>
#include "serial.h"

static const SerialConfig sdcfg = {
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
};

void SerialInit()
{

    sdStart( &SD3, &sdcfg );
    palSetPadMode( GPIOD, 9, PAL_MODE_ALTERNATE(7) );    // TX
    palSetPadMode( GPIOD, 8, PAL_MODE_ALTERNATE(7) );    // RX
}
