#include <avr/io.h>
#include "mf52.h"

typedef struct {
  int16_t temp;
  int16_t adc;
} temp_vector;

/*
 * temperature is given in centi-degrees to get better precision
 * values are adc values from  VCC - 100kΩ - LDR - GND
 *
 * see https://docs.google.com/spreadsheets/d/1a3KXmudcpWfhWYVWFE6oMQExikhBC05OGW9-anG_0Dc/edit#gid=0
 * see table on https://datasheet.lcsc.com/szlcsc/Nanjing-Shiheng-Elec-MF52A1104F3950-P209-15A_C13424.pdf
 */

#define MF52_NUM_POINTS 16
static temp_vector mf52Points[] = {
  {-250, 950},
  {-200, 928},
  {-150, 900},
  {-100, 867},
  {-50,  828},
  {0,    784},
  {50,   735},
  {100,  681},
  {150,  626},
  {200,  569},
  {250,  512},
  {300,  457},
  {350,  404},
  {400,  355},
  {450,  310},
  {500,  270},
};

/*
 * Get temperature from an ADC value
 */
int16_t getMF52Temp(int16_t adc) {
  // find index where adc value is bigger than given value
  int16_t index = MF52_NUM_POINTS-1;
  for (int16_t i=0; i<MF52_NUM_POINTS; i++) {
    if (mf52Points[i].adc > adc) {
      index = i;
      break;
    }
  }

  int16_t tempStart = mf52Points[index-1].temp;
  int16_t tempEnd = mf52Points[index].temp;
  int16_t adcStart = mf52Points[index-1].adc;
  int16_t adcEnd = mf52Points[index].adc;


  return tempStart + (tempEnd - tempStart) * (adc - adcStart) / (adcEnd - adcStart);
}

