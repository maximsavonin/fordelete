#define _USE_MATH_DEFINES

#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
#include <vector>

#include "graphics.h"

using namespace std;

struct Point
{
   int x, y;
};

class Figure
{
   protected:
      int x0 ,y0; // базовая точка
      int color, thickness;
   public:
      Figure(int x0, int y0, int color = WHITE, int thickness = 1): x0(x0), y0(y0), color(color), thickness(thickness) {}
      void setCoord(int x0, int y0){this->x0 = x0; this->y0 = y0;}
      void setColor(int color){this->color = color;}
      void setThickness(int thickness){this->thickness = thickness;}
      virtual void draw(); // нарисовать
};

class Line: public Figure
{
   private:
      int x1, y1;
   
   public:
      Line(int x0, int y0, int x1, int y1, int color = WHITE, int thickness = 1): Figure(x0, y0, color, thickness), x1(x1), y1(y1){}
      Line(const Line &a): Figure(a.x0, a.y0, a.color, a.thickness), x1(a.x1), y1(a.y1){}
      void setCoordEnd(int x1, int y1){this->x1 = x1; this->y1 = y1;}
      void draw();
};

class Rect: public Figure
{
   protected:
      int x1, y1;
   public:
      Rect(int x0, int y0, int x1, int y1, int color = WHITE, int thickness = 1): Figure(x0, y0, color, thickness), x1(x1), y1(y1){}
      Rect(const Rect &a): Figure(a.x0, a.y0, a.color, a.thickness), x1(a.x1), y1(a.y1){}
      void setCoordEnd(int x1, int y1){this->x1 = x1; this->y1 = y1;}
      void draw();
};

class FillRec: public Rect
{
   private:
      int fillColor;
      void draw();
   public:
      FillRec(int x0, int y0, int x1, int y1, int fillColor, int color = WHITE, int thickness = 1): Rect(x0, y0, x1, y1, color, thickness), fillColor(fillColor){}
      FillRec(const FillRec &a): Rect(a.x0, a.y0, a.x1, a.y1, a.color, a.thickness), fillColor(a.fillColor){}
      void setFillColor(int fillColor){this->fillColor = fillColor;}
};

class Circl: public Figure
{
   protected:
      int r;

   public:
      Circl(int x, int y, int r, int color = WHITE, int thickness = 1): Figure(x, y, color, thickness), r(r){}
      Circl(const Circl &a): Figure(a.x0, a.y0, a.color, a.thickness), r(a.r){}
      void setRadius(int r){this->r = r;}
      void draw();
};

class FillCircl: public Circl
{
   private:
      int fillColor;
   public:
      FillCircl(int x, int y, int r, int fillColor, int color = WHITE, int thickness = 1): Circl(x, y, r, color, thickness), fillColor(fillColor){}
      FillCircl(const FillCircl &a): Circl(a.x0, a.y0, a.r, a.color, a.thickness), fillColor(a.fillColor){}
      void setFillColor(int fillColor){this->fillColor = fillColor;}
      void draw();
};

class Curve: public Figure
{
   private:
      vector<vector<int>> data;
      double step = 0.02;
      void pefog(int[100], int, int);
   
   public:
      Curve(): Figure(0, 0, WHITE, 1) {}
      Curve(int data[][2], int n, int color = WHITE, int thickness = 1) : Figure(0, 0, color, thickness)
      {
          for (int i = 0; i < n; i++)
          {
              this->data.push_back({0, 0});
              this->data[i][0] = data[i][0];
              this->data[i][1] = data[i][1];
          }
      }
      Curve(vector<vector<int>> data, int color = WHITE, int thickness = 1) : Figure(0, 0, color, thickness), data(data) {}
      Curve(const Curve&);
      ~Curve();
      void add(int, int);
      void setStep(double a){step = a;}
      void setPoints(int **, int);
      void getPoints(int **, int&);
      void draw();
};

class Picture: public Figure
{
   private:
      IMAGE *file;
   public:
      Picture(int x, int y, string fileName): Figure(x, y), file(loadBMP(fileName.c_str())){}
      void draw() {putimage(x0, y0, file, COPY_PUT);}
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Line::draw()
{
   int dx = abs(x1-x0);
   int dy = abs(y1-y0);
   int err = 0;
   if(dy < dx)
   {
      if(x0 > x1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int d = dy == 0 ? 0 : (y1-y0)/dy;
      int y = y0;
      for(int x = x0; x <= x1; x++)
      {
         for(int i = 0; i < thickness; i++)
         {
            int yd;
            yd = (i+1)/2*pow(-1, i);
            putpixel(x, y+yd, color);
         }
         err = err+dy;
         if(err >= dx)
         {
            y += d;
            err -= dx;
         }
      }
   }
   else
   {
      if(y0 > y1)
      {
         int a = x0;
         x0 = x1;
         x1 = a;
         a = y0;
         y0 = y1;
         y1 = a;
      }
      int d = dx == 0 ? 0 : (x1-x0)/dx;
      int x = x0;
      for(int y = y0; y <= y1; y++)
      {
         for(int i = 0; i < thickness; i++)
         {
            int xd;
            xd = (i+1)/2*pow(-1, i);
            putpixel(x+xd, y, color);
         }
         err = err+dx;
         if(err >= dy)
         {
            x += d;
            err -= dy;
         }
      }
   }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Rect::draw()
{
   Line a(x0, y0, x1, y0, color, thickness);
   a.draw();
   a.setCoord(x1, y0);
   a.setCoordEnd(x1, y1);
   a.draw();
   a.setCoord(x1, y1);
   a.setCoordEnd(x0, y1);
   a.draw();
   a.setCoord(x0, y0);
   a.setCoordEnd(x0, y1);
   a.draw();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void FillRec::draw()
{
   Rect::draw();
   setfillstyle(SOLID_FILL, fillColor);
   floodfill((x1-x0)/2+x0, (y1-y0)/2+y0, color);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Circl::draw()
{
   for(int i = 1; i < thickness+1; i++)
   {
      int x1 = 0;
      int y1 = r+i/2*pow(-1, i-1);
      int delta = 1-2*(r+i/2*pow(-1, i-1));
      int err = 0;
      while(y1 >= x1)
      {
         putpixel(x0+x1, y0+y1, color);
         putpixel(x0+x1, y0-y1, color);
         putpixel(x0-x1, y0+y1, color);
         putpixel(x0-x1, y0-y1, color);
         putpixel(x0+y1, y0+x1, color);
         putpixel(x0+y1, y0-x1, color);
         putpixel(x0-y1, y0+x1, color);
         putpixel(x0-y1, y0-x1, color);
         err = 2*(delta+y1)-1;
         if(delta < 0 && err <= 0)
         {
            delta += 2*++x1+1;
            continue;
         }
         if(delta > 0 && err > 0)
         {
            delta -= 2*--y1+1;
            continue;
         }
         delta += 2*(++x1- --y1);
      }
   }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void FillCircl::draw()
{
   Circl::draw();
   setfillstyle(SOLID_FILL, fillColor);
   floodfill(x0, y0, color);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Curve::pefog(int pef[100], int k, int n)
{
   if(n <= k) return;
   int a[100] = {0};
   for(int i = 0; i < k; i++) a[i] = pef[i];
   for(int i = 1; i < k+1; i++)
   {
      pef[i] = a[i-1]+a[i];
   }
   pefog(pef, k+1, n);
}

Curve::Curve(const Curve &a): Figure(a.x0, a.y0, a.color, a.thickness), data(a.data), step(a.step)
{
   for(int i = 0; i < n; i++)
   {
      data[i] = new int[2];
      data[i][0] = a.data[i][0];
      data[i][1] = a.data[i][1];
   }
}

Curve::~Curve()
{
   for(int i = 0; i < n; i++)
   {
      delete[] data[i];
   }
   delete[] data;
}

void Curve::add(int x, int y)
{
   data[n] = new int[2];
   data[n][0] = x;
   data[n][1] = y;
   n++;
}

void Curve::setPoints(int **data, int n)
{
   this->n = n;
   for(int i = 0; i < n; i++)
   {
      this->data[i] = new int[2];
      this->data[i][0] = data[i][0];
      this->data[i][1] = data[i][1];
   }
}

void Curve::getPoints(int **data, int &n)
{
   n = this->n;
   for(int i = 0; i < n; i++)
   {
      data[i] = new int[2];
      data[i][0] = this->data[i][0];
      data[i][1] = this->data[i][1];
   }
}

void Curve::draw()
{
   if(n>1)
   {
      int pef[100] = {0};
      pef[0] = 1;
      pef[1] = 1;
      pefog(pef, 2, n);
      Point b = {data[0][0], data[0][1]};
      for(double t = step; t <= 1; t += step)
      {
         Point a = {0, 0};
         for(int i = 0; i < n; i++)
         {
            a.x += pef[i]*pow(1-t, n-i-1)*pow(t, i)*data[i][0];
            a.y += pef[i]*pow(1-t, n-i-1)*pow(t, i)*data[i][1];
         }
         Line c = Line(b.x, b.y, a.x, a.y, color, thickness);
         c.draw();
         b = a;
      }
      Line c = Line(b.x, b.y, data[n-1][0], data[n-1][1], color, thickness);
      c.draw();
   }
   if(n == 1) for(int i = 0; i < thickness; i++)
   {
      putpixel(data[0][0]+i, data[0][1], color);
      putpixel(data[0][0], data[0][1]+i, color);
      putpixel(data[0][0]-i, data[0][1], color);
      putpixel(data[0][0], data[0][1]-i, color);
   }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
   if(t > 3)
   {
      char str[30];
      sprintf(str, "%s", text.c_str());
      outtextxy(left+5, top, str);
   }
   else
   {
      char str[30];
      sprintf(str, "%s|", text.c_str());
      outtextxy(left+5, top, str);
   }
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

void drawAll(vector<Figure*> acts)
{
   setfillstyle(SOLID_FILL, BLACK);
   bar(10, 70, 1190, 800);
   for(int i = 0; i < acts.size(); i++)
   {
      acts[i]->draw();
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

void addRect(vector<Figure*> &acts, int color, int fill)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   Rect *a;
   if(fill) a = new FillRec(x, y, mousex(), mousey(), color, color);
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
      acts.push_back(new FillRec(x, y, mousex(), mousey(), color, color));
   else
      acts.push_back(new Rect(x, y, mousex(), mousey(), color));
}

void addCircle(vector<Figure*> &acts, int color, int fill)
{
   int p = 0;
   int x = mousex();
   int y = mousey();
   int r = 0;
   Circl *a;
   if(fill) a = new FillCircl(mousex(), mousey(), r, color, color);
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
{/*
    vector<vector<int>> all;
    int brea = 0, p = 0;
    int count = 0;
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
            acts.push_back(new Curve(all, count, color, 1));
            delay(200);
            break;
        }
        for (int i = 0; i < count; i++)
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
            count++;
            while (mousebuttons());
        }
        else
        {
            all[numer][0] = mousex();
            all[numer][1] = mousey();
        }
        for (int i = 0; i < count; i++)
        {
            Circl dot = Circl(all[i][0], all[i][1], 5);
            dot.draw();
        }
        Curve a(all, count, color, 1);
        a.draw();

        setvisualpage(p);
        delay(10);
    }*/;
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
      if(pole(800, 10, 150, 50, text, t))
      {
         acts.push_back(new Picture(10, 70, text));
         break;
      }
      t++;
      t = t%8;
      setvisualpage(p);
      delay(50);
   }
   cout << 1;
}

void save(int left = 0, int top = 0, int width = 0, int height = 0)
{
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
    saveBMP("output.bmp", output);
    freeimage(output);
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
   
   IMAGE *imager;
   imager = loadBMP("Red.bmp");
   
   IMAGE *imageg;
   imageg = loadBMP("Green.bmp");
   
   IMAGE *imageb;
   imageb = loadBMP("Blue.bmp");
   
   int col[3] = {255, 255, 255};
   int r = 0, wrt[2] = {0};
   int n = 5, p = 0, t = 0;
   int mode = 0, fill = 0;
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
               addLine(acts, COLOR(col[0], col[1], col[2]));
               break;
            }
            case 2:
            {
               addRect(acts, COLOR(col[0], col[1], col[2]), fill);
               break;
            }
            case 3:
            {
               addCircle(acts, COLOR(col[0], col[1], col[2]), fill);
               break;
            }
            case 4:
            {
                addCurve(acts, COLOR(col[0], col[1], col[2]));
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
          if (abs(mousex() - 1065) <= 25)
          {
              acts.pop_back();
              while (mousebuttons());
          }
          if (abs(mousex() - 1015) <= 25)
          {
             addPicture(acts);
          }
      }
      delay(100);
   }
   return 0;
}