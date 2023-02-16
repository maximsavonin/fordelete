//overleaf.com
#include <stdio.h>
#include <math.h>
#include <random>
#include <ctime>
#include "task.h"

#include "graphics.h"

#define W 1800
#define H 900

typedef struct Button
{
   int x, y;
   char text[20] = {0};
}Button;


int main()
{
   initwindow(W, H, "Win", 0, 0);
   Button btns[12] = {{500, 300, "1"}, {800, 300, "2"}, {1100, 300, "3"}, {1400, 300, "4"}, {500, 500, "5"}, {800, 500, "6"}, {1100, 500, "7"}, {1400, 500, "8"}, {650, 400, "Red"}, {950, 400, "Green"}, {1250, 400, "Blue"}, {200, 200, "Save"}};
   int p = 0, num = -1;
   int h = 30, w = 70;
   int c = -1;
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   setusercharsize(1, 1, 3, 2);
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
      if(num == -1)
      {
         for(int i = 0; i < 8; i++)
         {
            if(abs(mousex()-btns[i].x) < w && abs(mousey()-btns[i].y) < h)
            {
               if(mousebuttons()) num = i;
               setlinestyle(SOLID_LINE, 1, 3);
            }
            else setlinestyle(SOLID_LINE, 1, 1);
            rectangle(btns[i].x-w, btns[i].y-h, btns[i].x+w, btns[i].y+h);
            outtextxy(btns[i].x, btns[i].y+10, btns[i].text);
         }
      }
      else
      {
         for(int i = 8; i < 11; i++)
         {
            if(abs(mousex()-btns[i].x) < w && abs(mousey()-btns[i].y) < h)
            {
               if(mousebuttons()) c = i-8;
               setlinestyle(SOLID_LINE, 1, 3);
            }
            else setlinestyle(SOLID_LINE, 1, 1);
            rectangle(btns[i].x-w, btns[i].y-h, btns[i].x+w, btns[i].y+h);
            outtextxy(btns[i].x, btns[i].y+10, btns[i].text);
         }
      }
      
      if(c != -1)
      {
         clearviewport();
         switch(num)
         {
            case 0:
            {
               fill_1(0, 0, W, H, c);
               break;
            }
            case 1:
            {
               fill_2(0, 0, W, H, c);
               break;
            }
            case 2:
            {
               fill_3(0, 0, W, H, c);
               break;
            }
            case 3:
            {
               fill_4(0, 0, W, H, c);
               break;
            }
            case 4:
            {
               fill_5(0, 0, W, H, c);
               break;
            }
            case 5:
            {
               fill_6(0, 0, W, H, c);
               break;
            }
            case 6:
            {
               fill_7(0, 0, W, H, c);
               break;
            }
            case 7:
            {
               fill_8(0, 0, W, H, c);
               break;
            }
         }
         rectangle(btns[11].x-w, btns[11].y-h, btns[11].x+w, btns[11].y+h);
         outtextxy(btns[11].x, btns[11].y+10, btns[11].text);
         setvisualpage(p);
         if(abs(mousex()-btns[11].x) < w && abs(mousey()-btns[11].y) < h) save();
         num = -1;
         c = -1;
         while(1-mousebuttons());
         while(mousebuttons());
      }
      
      setvisualpage(p);
      delay(50);
   }
   save();
   getchar();
}