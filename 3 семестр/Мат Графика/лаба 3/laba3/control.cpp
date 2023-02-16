#include <string>
#include <graphics.h>

#include "control.h"

using namespace std;

int pole(int left, int top, int widht, int height, string Text, int data, int &wrt, int t)
{
   if(wrt)
   {
      if(kbhit())
      {
         int key = getch();
         if(key == 13) wrt = 0;
         if(key == 8) data = data/10;
         if(key > 47 && key < 58) data = data*10+key-48;
      }
      
      setfillstyle(SOLID_FILL, WHITE);
      bar(left-5, top-5, left+widht, top+height);
      setcolor(BLACK);
      if(t > 3)
      {
         char text[30];
         sprintf(text, "%s%d", Text.c_str(), data);
         outtextxy(left, top, text);
      }
      else
      {
         char text[30];
         sprintf(text, "%s%d|", Text.c_str(), data);
         outtextxy(left, top, text);
      }
   }
   else
   {
      setfillstyle(SOLID_FILL, WHITE);
      bar(left-5, top-5, left+widht, top+height);
      setcolor(BLACK);
      char text[30];
      sprintf(text, "%s%d", Text.c_str(), data);
      outtextxy(left, top, text);
   }
   return data;
}

void lineColor(int x, int col[3][2], int num, IMAGE *image)
{
   putimage(x, 500, image, COPY_PUT);
   
   setfillstyle(SOLID_FILL, WHITE);
   bar(col[num][0]+x-3, 500, col[num][0]+x+3, 529);
   
   
   if(mousebuttons())
   {
      if(abs(mousex()-col[num][0]-x) < 4 and abs(mousey() - 515) < 15 and col[(num+1)%3][1] == 0 and col[(num+2)%3][1] == 0)
      {
         col[num][1] = 1;
      }
   }
   else
   {
      col[num][1] = 0;
   }
   
   if(col[num][1]) 
   {
      col[num][0] = mousex()-x;
      col[num][0] = (col[num][0]+abs(col[num][0]))/2;
      col[num][0] = col[num][0]>255 ? 255 : col[num][0];
   }
}

bool butSave(int left, int top)
{
   setcolor(WHITE);
   bar(left, top, left+150, top+50);
   setcolor(BLACK);
   outtextxy(left+30, top+15, "Сохранить");
   return abs(mousex()-left-75) < 75 && abs(mousey()-top-25) < 25 && mousebuttons();
}