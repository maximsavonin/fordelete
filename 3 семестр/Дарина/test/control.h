#ifndef CONTROL_H
#define CONTROL_H

enum control_values { NONE = -1, EXIT, SAVE, MOVE_X_PLUS,
   MOVE_Y_PLUS, MOVE_X_MINUS, MOVE_Y_MINUS,
   ROTATE_X, ROTATE_Y, ROTATE_Z,
   N_CONTROLS };
                     
struct Control {
   int left;
   int top;
   int right;
   int bottom;
};

void create_control(int, int, int, int, int);
int select_control();

#endif