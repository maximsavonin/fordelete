#include "graphics.h"
#include "control.h"
Control controls[N_CONTROLS];
void create_control(int i, int left, int top, int right, int bottom) {
   controls[i].left = left;
   controls[i].top = top;
   controls[i].right = right;
   controls[i].bottom = bottom;
}
int select_control() {
   int x, y;
   x = mousex();
   y = mousey();
   for (int i = 0; i < N_CONTROLS; i++) {
      if (x > controls[i].left && x < controls[i].right &&
          y > controls[i].top  && y < controls[i].bottom) {
         return i;
      }
   }
   return NONE;
}