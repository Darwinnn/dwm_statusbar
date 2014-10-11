#include <stdio.h>
#include <stdlib.h>

#include "battery.h"

float
get_battery_percentage(char *bar)
{
  float percentage;
  int now;
  int full;
  FILE *f_full;
  FILE *f_now;
  
  f_full = fopen(CHARGE_FULL, "r");
  f_now  = fopen(CHARGE_NOW, "r");

  fscanf(f_full, "%d", &full);
  fscanf(f_now, "%d", &now);

  fclose(f_full);
  fclose(f_now);

  percentage = (float)now / (float)full;
  
  int i;
  for(i=0;i!=10;i++)
  {
      if((percentage*10) > i)
          bar[i] = '*';
      else
          bar[i] = '-';
  }
  bar[10] = '\0';
  return percentage;
}

bstate_t
get_status()
{
  char status;
  FILE *f_status;

  f_status = fopen(STATUS, "r");
  status = fgetc(f_status);
  fclose(f_status);

  switch(status) {
    case 'C': return CHARGING;
    case 'D': return DISCHARGING;
    case 'U': return UNKNOWN;
    case 'F': return FULL;
  }
}
