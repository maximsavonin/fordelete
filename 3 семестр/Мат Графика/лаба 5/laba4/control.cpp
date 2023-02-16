#include <string>
#include <graphics.h>

#include "control.h"

using namespace std;

struct Button
{
   int x, y;
   IMAGE *image;
};

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
      bar(left, top, left+widht, top+height);
      setcolor(BLACK);
      if(t > 3)
      {
         char text[30];
         sprintf(text, "%s%d", Text.c_str(), data);
         outtextxy(left+2, top+2, text);
      }
      else
      {
         char text[30];
         sprintf(text, "%s%d|", Text.c_str(), data);
         outtextxy(left+2, top+2, text);
      }
   }
   else
   {
      setfillstyle(SOLID_FILL, WHITE);
      bar(left, top, left+widht, top+height);
      setcolor(BLACK);
      char text[30];
      sprintf(text, "%s%d", Text.c_str(), data);
      outtextxy(left+2, top+2, text);
   }
   return data;
}

void lineColor(int x, int col[3][2], int num, IMAGE *image)
{
   putimage(x, 660, image, COPY_PUT);
   
   setfillstyle(SOLID_FILL, WHITE);
   bar(col[num][0]*200/255+x-3, 660, col[num][0]*200/255+x+3, 689);
   
   if(mousebuttons())
   {
      if(abs(mousex()-col[num][0]*200/255-x) < 4 and abs(mousey() - 675) < 15 and col[(num+1)%3][1] == 0 and col[(num+2)%3][1] == 0)
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
      col[num][0] = (mousex()-x)*255/200;
      col[num][0] = (col[num][0]+abs(col[num][0]))/2;
      col[num][0] = col[num][0]>255 ? 255 : col[num][0];
   }
}

bool button(Button a)
{
   putimage(a.x, a.y, a.image, COPY_PUT);
   return abs(a.x+25-mousex()) < 25 && abs(a.y+15-mousey()) < 15 && mousebuttons();
}