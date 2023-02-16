#include <iostream>
#include "graphics.h"
#include <random>
#include <time.h>
#include <math.h>

#include "control.h"
#include "task.h"

using namespace std;

int main()
{
   setlocale(LC_ALL,"Russian");
   setlocale(LC_ALL,"rus");
   srand(time(0));
   initwindow(800, 600);
   
   setlinestyle(SOLID_LINE, 0, 1);
   setbkcolor(WHITE);
   
   srand(time(0));
   
   IMAGE *imager;
   imager = loadBMP("Red.bmp");
   
   IMAGE *imageg;
   imageg = loadBMP("Green.bmp");
   
   IMAGE *imageb;
   imageb = loadBMP("Blue.bmp");
   
   IMAGE *image;
   image = loadBMP("flag.bmp");
   
   int col[3][2] = {{200, 0}, {200, 0}, {200, 0}};
   int r = 100, wrt[4] = {0};
   int x = 400, y = 200, n = 5;
   int fil = 0, p = 0, t = 0;
   
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      
      setfillstyle(SOLID_FILL, BLACK);
      setcolor(WHITE);
      rectangle(-1, -1, 801, 601);
      bar(0, 0, 800, 600);
      if(n==6) putimage(0, 0, image, COPY_PUT);
      
      drawPol(x, y, n, r, col);
      
      setlinestyle(SOLID_LINE, 0, 5);
      setcolor(BLACK);
      outtextxy(620, 440, "Закрасить"); 
      setcolor(WHITE);
      rectangle(725, 425, 775, 475);
      if(abs(mousex()-750) <= 25 and abs(mousey()-450) <= 25 and mousebuttons())
      {
         fil = 1-fil;
         while(mousebuttons());
      }
      if(fil) 
      {
         line(735, 435, 750, 450);
         line(750, 450, 780, 420);
         if(n > 4) fill(x, y, col);
      }
      setlinestyle(SOLID_LINE, 0, 1);
      
      if(mousebuttons() && abs(95-mousex()) < 65 && abs(560-mousey()) < 15) 
      {
         for(int i = 0; i < 4; i++) wrt[i] = 0;
         wrt[0] = 1;
      }
      if(mousebuttons() && abs(270-mousex()) < 85 && abs(560-mousey()) < 15)
      {
         for(int i = 0; i < 4; i++) wrt[i] = 0;
         wrt[1] = 1;
      }
      if(mousebuttons() && abs(470-mousex()) < 85 && abs(560-mousey()) < 15)
      {
         for(int i = 0; i < 4; i++) wrt[i] = 0;
         wrt[2] = 1;
      }
      if(mousebuttons() && abs(677-mousex()) < 92 && abs(560-mousey()) < 15)
      {
         for(int i = 0; i < 4; i++) wrt[i] = 0;
         wrt[3] = 1;
      }
      
      r = pole(30, 550, 125, 25, "Радиус: ", r, wrt[0], t);
      x = pole(190, 550, 165, 25, "X координата: ", x, wrt[1], t);
      y = pole(390, 550, 165, 25, "Y координата: ", y, wrt[2], t);
      n = pole(590, 550, 180, 25, "количество углов: ", n, wrt[3], t);
      
      lineColor(7, col, 0, imager);
      lineColor(270, col, 1, imageg);
      lineColor(533, col, 2, imageb);
      if(butSave(650, 0)) save();
      
      t = t+1;
      t = t%8;
      
      setvisualpage(p);
      delay(10);
   }
   
   getch();
}