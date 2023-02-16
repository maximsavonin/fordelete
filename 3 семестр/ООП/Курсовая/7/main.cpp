#define _USE_MATH_DEFINES

#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
#include <vector>

#include "graphics.h"
#include "draw.h"

using namespace std;

int pole(int left, int top, int widht, int height, string &text, int t)
{
   if(kbhit())
   {
      int key = getch();
      switch(key)
      {
         case 8: text.erase(text.size()-1, 1); break;
         case 13: return 1;
         default:
            text += key;
            break;
      }
   }
   
   setfillstyle(SOLID_FILL, WHITE);
   bar(left, top, left+widht, top+height);
   setcolor(BLACK);
   rectangle(left, top, left+widht, top+height);
   settextjustify(LEFT_TEXT, CENTER_TEXT);
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(1, 2, 1, 1);
   if(t > 3)
   {
      char str[30];
      sprintf(str, "%s", text.c_str());
      outtextxy(left+5, top+height/2+5, str);
   }
   else
   {
      char str[30];
      sprintf(str, "%s|", text.c_str());
      outtextxy(left+5, top+height/2+5, str);
   }
   settextstyle(3, HORIZ_DIR, 1);
   return 0;
}

void tick(int left, int top, int widht, int height, string text, int &fill)
{
   setlinestyle(SOLID_LINE, 0, 3);
   setcolor(BLACK);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy(left+widht/2, top+height+15, text.c_str()); 
   rectangle(left, top, left+widht, top+height);
   if(abs(mousex()-left-widht/2) <= widht/2 and abs(mousey()-top-height/2) <= height/2 and mousebuttons())
   {
      fill = 1-fill;
      while(mousebuttons());
   }
   if(fill) 
   {
      line(left, top, left+widht, top+height);
      line(left, top+height, left+widht, top);
   }
   setlinestyle(SOLID_LINE, 0, 1);
}

void lineColor(int x, int y, int col[3][2], int num, IMAGE *image)
{
   putimage(x, y, image, COPY_PUT);
   
   setfillstyle(SOLID_FILL, WHITE);
   setcolor(BLACK);
   bar(col[num][0]+x-3, y, col[num][0]+x+3, y+19);
   rectangle(col[num][0]+x-3, y, col[num][0]+x+3, y+19);
   
   
   if(mousebuttons())
   {
      if(abs(mousex()-col[num][0]-x) < 4 and abs(mousey() - y-10) < 10 and col[(num+1)%3][1] == 0 and col[(num+2)%3][1] == 0)
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

void addLine(vector<Figure*> &acts, int color)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   Line a(x, y, mousex(), mousey(), color);
   while(mousebuttons() and abs(mousex()-600) <= 590 and abs(mousey()-435) <= 365)
   {
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts);
      
      a.setCoord(x, y);
      a.setCoordEnd(mousex(), mousey());
      
      a.draw();
      
      setvisualpage(p);
      delay(10);
   }
   acts.push_back(new Line(x, y, mousex(), mousey(), color));
}

void addRect(vector<Figure*> &acts, int fill, int color, int fillcolor)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   Rect *a;
   if(fill) a = new FillRec(x, y, mousex(), mousey(), fillcolor, color);
   else a = new Rect(x, y, mousex(), mousey(), color);
   
   while(mousebuttons() and abs(mousex()-600) <= 590 and abs(mousey()-435) <= 365)
   {
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts);
      
      a->setCoord(x, y);
      a->setCoordEnd(mousex(), mousey());
      a->draw();
      
      setvisualpage(p);
      delay(10);
   }
   if(fill)
      acts.push_back(new FillRec(x, y, mousex(), mousey(), fillcolor, color));
   else
      acts.push_back(new Rect(x, y, mousex(), mousey(), color));
}

void addCircle(vector<Figure*> &acts, int fill, int color, int fillcolor)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   int r = 0;
   Circl *a;
   if(fill) a = new FillCircl(mousex(), mousey(), r, fillcolor, color);
   else a = new Circl(mousex(), mousey(), r, color);
   while(mousebuttons() and abs(mousex()-600) <= 590 and abs(mousey()-435) <= 365)
   {
      p = 1-p;
      setactivepage(p);
      
      drawAll(acts);

      r = fmin(abs(mousex()-x)/2, abs(mousey()-y)/2);
      a->setCoord(x+(mousex()-x)/2, y+(mousey()-y)/2);
      a->setRadius(r);

      a->draw();
      
      setvisualpage(p);
      delay(10);
   }
   
   acts.push_back(a);
}

void addCurve(vector<Figure*> &acts, int color)
{
   vector<vector<int>> all;
   int brea = 0, p = 0;
   int numer = -1;
   while (1)
   {
      p = 1 - p;
      setactivepage(p);

      drawAll(acts);

      while (1 - mousebuttons() or abs(mousex() - 600) > 590 or abs(mousey() - 435) > 365)
      {
         numer = -1;
         if (kbhit()) if (getch() == 13)
         {
             brea = 1;
             break;
         }
      }
      if (brea)
      {
         acts.push_back(new Curve(all, color, 1));
         delay(200);
         break;
      }
      for (int i = 0; i < all.size(); i++)
      {
         if (abs(mousex() - all[i][0]) <= 7 and abs(mousey() - all[i][1]) <= 7)
         {
             numer = i;
             break;
         }
      }
      if (numer == -1)
      {
         all.push_back({mousex(), mousey()});
         while (mousebuttons());
      }
      else
      {
         all[numer][0] = mousex();
         all[numer][1] = mousey();
      }
      for (int i = 0; i < all.size(); i++)
      {
         Circl dot = Circl(all[i][0], all[i][1], 5);
         dot.draw();
      }
      Curve a(all, color, 1);
      a.draw();

      setvisualpage(p);
      delay(10);
   }
}

void addPicture(vector<Figure*> &acts)
{
   string text;
   int t = 0, p = 0;
   while(1)
   {
      p = 1 - p;
      setactivepage(p);
      setcolor(BLACK);
      if(pole(800, 15, 150, 40, text, t))
      {
         acts.push_back(new Picture(10, 70, text));
         break;
      }
      t++;
      t = t%8;
      setvisualpage(p);
      delay(50);
   }
}

void save(int left = 0, int top = 0, int width = 0, int height = 0)
{
   string text;
   int t = 0, p = 0;
   while(1)
   {
      p = 1 - p;
      setactivepage(p);
      setcolor(BLACK);
      if(pole(800, 15, 150, 40, text, t))
      {
         break;
      }
      t++;
      t = t%8;
      setvisualpage(p);
      delay(50);
   }
   IMAGE* output;

   if (width == 0)
   {
      width = getmaxx();
      height = getmaxy();
   }
   width++;
   height++;
   output = createimage(width - left, height - top);

   getimage(left, top, width - 1, height - 1, output);
   saveBMP(text.c_str(), output);
   freeimage(output);
}

void chooseColor(int x, int y, int n, int colors[], int col[3][2], int &choosed)
{
   IMAGE *imager;
   imager = loadBMP("Red.bmp");
   IMAGE *imageg;
   imageg = loadBMP("Green.bmp");
   IMAGE *imageb;
   imageb = loadBMP("Blue.bmp");
   
   lineColor(10, 810, col, 0, imager);
   lineColor(10, 840, col, 1, imageg);
   lineColor(10, 870, col, 2, imageb);
   
   freeimage(imager);
   freeimage(imageg);
   freeimage(imageb);
   
   for(int i = 0; i < n; i++)
   {
      FillRec a(x+i/2*45, y+i%2*45, x+35+i/2*45, y+35+i%2*45, colors[i+2], BLACK, 3);
      a.draw();
   }
   for(int i = 0; i < 2; i++)
   {
      FillRec a(x+(n/2+i)*45+i*20, y+20, x+40+(n/2+i)*45+i*20, y+60, colors[i], BLACK, 3);
      a.draw();
   }
   
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy(x+n/2*45+20, y+80, "Линия");
   outtextxy(x+n/2*45+85, y+80, "Заливка");
   
   if(mousebuttons())
   {
      if(choosed < 2 and choosed != -1)
      {
         int a = -1;
         for(int i = 0; i < n; i++)
         {
            if(abs(mousex()-(x+i/2*45+17)) < 18 and abs(mousey()-(y+i%2*45+17)) < 18) a = i+2;
         }
         if(a != -1)
         {
            colors[choosed] = colors[a];
            choosed = -1;
         }
      }
      else
      {
         if(choosed != -1) colors[choosed] = COLOR(col[0][0], col[1][0], col[2][0]);
         for(int i = 0; i < n; i++)
         {
            if(abs(mousex()-(x+i/2*45+17)) < 18 and abs(mousey()-(y+i%2*45+17)) < 18) choosed = i+2;
         }
         if(abs(mousex()-(x+n/2*45+20)) < 20 and abs(mousey()-(y+40)) < 20) choosed = 0;
         if(abs(mousex()-(x+n/2*45+85)) < 20 and abs(mousey()-(y+40)) < 20) choosed = 1;
      }
   }
}

int main()
{
   setlocale(LC_ALL,"Russian");
   setlocale(LC_ALL,"rus");
   srand(time(0));
   initwindow(1200, 900);
   
   setlinestyle(SOLID_LINE, 0, 1);
   setbkcolor(WHITE);
   
   srand(time(0));
   
   int col[3][2] = {{255, 0}, {255, 0}, {255, 0}};
   int colors[10] = {WHITE, WHITE, RED, GREEN, BLUE, WHITE, WHITE, WHITE, WHITE, WHITE};
   int p = 0, t = 0;
   int mode = 0, fill = 0, choosed = -1;
   vector<Figure*> acts;
   
   const int numButton = 4;
   Figure *button[numButton][2];

   for(int i = 0; i < numButton; i++)
      button[i][0] = new Rect(10+i*50, 10, 59+i*50, 60, BLACK);
   button[0][1] = new Line(20, 25, 50, 45, BLACK, 3);
   button[1][1] = new Rect(65, 20, 105, 50, BLACK);
   button[2][1] = new Circl(135, 35, 21, BLACK);
   int pointsbut[4][2] = { {170, 20}, {200, 20}, {170, 50}, {200, 50} };
   button[3][1] = new Curve(pointsbut, 4, BLACK, 2);
   
   Line butsave[18] = { Line(1150, 20, 1177, 20, BLACK, 1),
                                  Line(1177, 20, 1180, 23, BLACK, 1),
                                  Line(1180, 23, 1180, 50, BLACK, 1),
                                  Line(1180, 50, 1150, 50, BLACK, 1),
                                  Line(1150, 50, 1150, 20, BLACK, 1),
                                  Line(1155, 20, 1155, 28, BLACK, 1),
                                  Line(1155, 28, 1175, 28, BLACK, 1),
                                  Line(1175, 28, 1175, 20, BLACK, 1),
                                  Line(1170, 22, 1173, 22, BLACK, 1),
                                  Line(1173, 22, 1173, 26, BLACK, 1),
                                  Line(1173, 26, 1170, 26, BLACK, 1),
                                  Line(1170, 26, 1170, 22, BLACK, 1),
                                  Line(1155, 50, 1155, 31, BLACK, 1),
                                  Line(1155, 31, 1175, 31, BLACK, 1),
                                  Line(1175, 31, 1175, 50, BLACK, 1),
                                  Line(1157, 35, 1173, 35, BLACK, 1),
                                  Line(1157, 40, 1173, 40, BLACK, 1),
                                  Line(1157, 45, 1173, 45, BLACK, 1) };

   Line butclear[13] = { Line(1130, 20, 1115, 35, BLACK, 5),
                                 Line(1116, 36, 1099, 49, BLACK, 1),
                                 Line(1114, 34, 1101, 51, BLACK, 1),
                                 Line(1116, 36, 1098, 48, BLACK, 1),
                                 Line(1114, 34, 1102, 52, BLACK, 1),
                                 Line(1117, 37, 1097, 47, BLACK, 1),
                                 Line(1113, 33, 1103, 53, BLACK, 1),
                                 Line(1117, 37, 1096, 46, BLACK, 1),
                                 Line(1113, 33, 1104, 54, BLACK, 1),
                                 Line(1118, 38, 1095, 45, BLACK, 1),
                                 Line(1112, 32, 1105, 55, BLACK, 1),
                                 Line(1118, 38, 1094, 44, BLACK, 1),
                                 Line(1112, 32, 1106, 56, BLACK, 1) };

   Line butback[3] = { Line(1080, 35, 1050, 35, BLACK, 3),
                                 Line(1050, 35, 1065, 20, BLACK, 3),
                                 Line(1050, 35, 1065, 50, BLACK, 3) };

   Figure *butload[4] = { new Rect(1005, 35, 1025, 55, BLACK, 2),
                                    new Line(1015, 45, 1015, 15, BLACK, 2),
                                    new Line(1015, 15, 1006, 24, BLACK, 2),
                                    new Line(1015, 15, 1024, 24, BLACK, 2)};
   settextstyle(3, HORIZ_DIR, 1);
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      clearviewport();
      for(int i = 0; i < numButton; i++)
      {
         for(int k = 0; k < 2; k ++)
         {
            button[i][k]->draw();
         }
      }
      
      tick(250, 10, 30, 30, "Закрасить", fill);
      chooseColor(300, 810, 8, colors, col, choosed);
      setcolor(BLACK);
      rectangle(1140, 10, 1190, 60);
      for (int i = 0; i < 18; i++)
      {
          butsave[i].draw();
      }
      setcolor(BLACK);
      rectangle(1090, 10, 1140, 60);
      for (int i = 0; i < 13; i++)
      {
          butclear[i].draw();
      }

      setcolor(BLACK);
      rectangle(1040, 10, 1090, 60);
      for (int i = 0; i < 3; i++)
      {
          butback[i].draw();
      }
      
      setcolor(BLACK);
      rectangle(990, 10, 1040, 60);
      for (int i = 0; i < 4; i++)
      {
          butload[i]->draw();
      }
      
      drawAll(acts);
      if(abs(mousey()-35) <= 25 and mousebuttons())
      {
         for(int i = 0; i < numButton; i++)
            if(abs(mousex()-35-i*50) <= 25) mode = i+1;
      }
      if(abs(mousex()-630) <= 560 and abs(mousey()-450) <= 350 and mousebuttons() and mode != 0)
      {
         switch(mode)
         {
            case 1:
            {
               addLine(acts, colors[0]);
               break;
            }
            case 2:
            {
               addRect(acts, fill, colors[0], colors[1]);
               break;
            }
            case 3:
            {
               addCircle(acts, fill, colors[0], colors[1]);
               break;
            }
            case 4:
            {
                addCurve(acts, colors[0]);
                break;
            }
         }
      }
      setvisualpage(p);
      if (abs(mousey() - 35) <= 25 and mousebuttons())
      {
          if (abs(mousex() - 1165) <= 25)
          {
              save(10, 70, 1190, 800);
          }
          if (abs(mousex() - 1115) <= 25)
          {
              acts.clear();
          }
          if (abs(mousex() - 1065) <= 25 and acts.size() > 0)
          {
              acts.pop_back();
              while (mousebuttons());
          }
          if (abs(mousex() - 1015) <= 25)
          {
             addPicture(acts);
          }
      }
      delay(20);
   }
   return 0;
}