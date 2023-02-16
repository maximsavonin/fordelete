#ifndef CONTROL_H
#define CONTROL_H

enum control_values { NONE = -1,UP,DOWN,RIGHT,LEFT,
   L_SPIN,R_SPIN,U_SCALE,D_SCALE,SAVE,EXIT,N_CONTROLS };

struct Control
{
   int left;
   int top;
   int right;
   int bottom;
};
void init_control(int, int, int, const char *);
void free_image();
void draw_image(int);
int select_control();

#endif