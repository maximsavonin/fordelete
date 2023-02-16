#ifndef CONTROL_H
#define CONTROL_H

enum control_values 
{ NONE = -1, 
EXIT, SAVE,
TAKE_DOTS,
CURVE_BEZIER, 
ALGORITM_CHAIKINA,
N_CONTROLS
};
   
struct Control
{
int left;
int top;
int right;
int bottom;
};

void create_control(int, int, int, const char*);
int select_control();

#endif