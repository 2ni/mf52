#include "mf52.h"

/*
 * Get temperature from an ADC value
 */
int16_t get_temp(int16_t adc) {
  // find index where adc value is bigger than given value
  int16_t index = MF52_NUM_POINTS-1;
  for (int16_t i=0; i<MF52_NUM_POINTS; i++) {
    if (mf52_points[i].adc > adc) {
      index = i;
      break;
    }
  }

  int16_t temp_start = mf52_points[index-1].temp;
  int16_t temp_end = mf52_points[index].temp;
  int16_t adc_start = mf52_points[index-1].adc;
  int16_t adc_end = mf52_points[index].adc;


  return temp_start + (temp_end - temp_start) * (adc - adc_start) / (adc_end - adc_start);
}

