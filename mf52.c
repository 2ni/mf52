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
  {-250, 950}, // 0
  {-200, 928}, // 1
  {-150, 900}, // 2
  {-100, 867}, // 3
  {-50,  828}, // 4
  {0,    784}, // 5
  {50,   735}, // 6
  {100,  681}, // 7
  {150,  626}, // 8
  {200,  569}, // 9
  {250,  512}, // 10
  {300,  457}, // 11
  {350,  404}, // 12
  {400,  355}, // 13
  {450,  310}, // 14
  {500,  270}, // 15
};

/*
 * Get temperature from an ADC value
 */
int16_t getMF52Temp(uint16_t adc) {
  // find index where adc value is bigger than given value
  uint8_t index = MF52_NUM_POINTS-1;
  for (uint8_t i=0; i<MF52_NUM_POINTS; i++) {
    if (adc > mf52Points[i].adc) {
      index = i;
      break;
    }
  }

  if (index==0) {
    return mf52Points[0].temp;
  } else if (index==(MF52_NUM_POINTS-1)) {
    return mf52Points[MF52_NUM_POINTS-1].temp;
  }

  int16_t tempStart = mf52Points[index-1].temp;
  int16_t tempEnd = mf52Points[index].temp;
  uint16_t adcStart = mf52Points[index-1].adc;
  uint16_t adcEnd = mf52Points[index].adc;

  /*
   * for some reasons it's not possible to calculate
   * all in one line :-(
   */
  int16_t r = (tempEnd - tempStart) * (adc - adcStart);
  int16_t d = adcEnd - adcStart;
  r /= d;
  return tempStart + r;
}

