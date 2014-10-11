#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <X11/Xlib.h>

#include "battery.h"

Display *dpy;

void
open_display(void)
{
  if (!(dpy = XOpenDisplay(NULL))) 
    exit(1);
}

void
close_display()
{
  XCloseDisplay(dpy);
  exit(0);
}

void
set_status(char *str)
{
  XStoreName(dpy, DefaultRootWindow(dpy), str);
  XSync(dpy, False);
}

main(void)
{
  time_t current_time;
  char timest[128];
  char barbuff[256];
  bstate_t bstate;
  char bar[10];
  float percentage;
  char status[] = { '+', '-', '?', '=' };

  daemon(0,0);
  open_display();
  for (;;sleep(1)) {
    current_time = time(NULL);
    bstate = get_status();
    percentage = get_battery_percentage(bar);
    strftime(timest, sizeof(timest), "%d.%m.%Y | %H:%M:%S", localtime(&current_time));
    sprintf(barbuff, "(%c)[%s] %.f%% [%s]", status[bstate], bar, (percentage*100.0), timest);
    set_status(barbuff);
  }
  close_display();
  return 0;
}
