#ifndef _LDR_MF52_
#define _LDR_MF52_

#include <avr/io.h>

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
static temp_vector mf52_points[] = {
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

int16_t get_temp(int16_t adc);
int16_t find_index(int16_t adc);

#endif // end LDR_MF52_


