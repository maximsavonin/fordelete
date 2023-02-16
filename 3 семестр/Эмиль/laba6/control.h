#ifndef CONTROL_H
#define CONTROL_H

enum control_values { NONE = -1,UP,DOWN,RIGHT,LEFT,
   SPIN, DSPIN, UP_SCALE,DOWN_SCALE,SAVE,EXIT,N_CONTROLS };

struct Control
{
   int left;
   int top;
   int right;
   int bottom;
};
void create_control(int, int, int, int, int);
int select_control();

#endif