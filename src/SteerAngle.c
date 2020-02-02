#include "SteerAngle.h"
#include <ch.h>
#include <hal.h>

#define ADC1_NUM_CHANNELS   1
#define ADC1_BUF_DEPTH      1

int steer_ADC_val = 0;

static adcsample_t adc_buffer[ADC1_NUM_CHANNELS * ADC1_BUF_DEPTH];

/*
 * GPT4 configuration. This timer is used as trigger for the ADC.
 */
static const GPTConfig gpt4cfg1 = {
  .frequency =  1000000,
  .callback  =  NULL,
  .cr2       =  TIM_CR2_MMS_1,  /* MMS = 010 = TRGO on Update Event.        */
  .dier      =  0U
  /* .dier field is direct setup of register, we don`t need to set anything here until now */
};


/* ADC streaming callback */
static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
  (void)adcp;
  (void)buffer;
  (void)n;

  adcsample_t value = buffer[0];
  steer_ADC_val = (int16_t) value;

}

/* ADC errors callback, should never happen */
static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

  (void)adcp;
  (void)err;


}

static const ADCConversionGroup steer_adc_1_cnfg = {
  .circular     = true,                                           // working mode = looped
  .num_channels = ADC1_NUM_CHANNELS,
  .end_cb       = adccallback,
  .error_cb     = adcerrorcallback,
  .cr1          = 0,
  .cr2          = ADC_CR2_EXTEN_RISING | ADC_CR2_EXTSEL_SRC(12),  // Commutated from GPT, Timer =4
  .smpr1        = ADC_SMPR1_SMP_AN10(ADC_SAMPLE_480), // for AN10  - 480 samples
  .sqr1         = ADC_SQR1_NUM_CH(ADC1_NUM_CHANNELS),
  .sqr2         = 0,
  .sqr3         = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10)
  /* If we can macro ADC_SQR2_SQ... we need to write to .sqr2 */
};

void SteerAngleInit()
{
    // Timer starts
    gptStart(&GPTD4, &gpt4cfg1);
    // Trigger starts
    gptStartContinuous(&GPTD4, gpt4cfg1.frequency/2000); // how often we need ADC value - every 2 ms
    // ADC driver starts
    adcStart(&ADCD1, NULL);
    palSetLineMode( PAL_LINE( GPIOC, 0 ), PAL_MODE_INPUT_ANALOG );  // PC0
    adcStartConversion(&ADCD1, &steer_adc_1_cnfg, adc_buffer, ADC1_BUF_DEPTH);

}

int GetSteerAngleADCval()
{
    return steer_ADC_val;
}


