#include <iostream>
#include <math.h>
#include <random>
#include <ctime>

#include "graphics.h"

using namespace std;

void add(double a[3], double b[3], double c[3])
{
   c[0] = a[0]+b[0];
   c[1] = a[1]+b[1];
   c[2] = a[2]+b[2];
}

void sub(double a[3], double b[3], double c[3])
{
   c[0] = a[0]-b[0];
   c[1] = a[1]-b[1];
   c[2] = a[2]-b[2];
}

void mul(double a[3], double b[3], double c[3])
{
   c[0] = a[0]*b[0];
   c[1] = a[1]*b[1];
   c[2] = a[2]*b[2];
}

void muls(double a[3], double b[3], double c)
{
   b[0] = a[0]*c;
   b[1] = a[1]*c;
   b[2] = a[2]*c;
}

double dot(double a[3], double b[3])
{
   return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

double lenght(double a[3])
{
   return sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]);
}

void norm(double a[3], double b[3])
{
   double l = lenght(a);
   muls(a, b, 1/l);
}

void reflect(double a[3], double b[3], double c[3])
{
   double d[3];
   muls(b, d, 2*dot(b, a));
   sub(a, d, c);
}

void sph(double a[3], double b[3], double c, double d[2])
{
   double i = dot(a, b);
   double k = dot(a, a) - c*c;
   double h = i*i - k;
   d[0] = -1;
   d[1] = -1;
   if(h < 0) return;
   h = sqrt(h);
   d[0] = -i-h;
   d[1] = -i+h;
}

void CastRay(double a[3], double b[3], double c[3])
{
   double it[2];
   sph(a, b, 1.0, it);
   c[0] = 0;
   c[1] = 0;
   c[2] = 0;
   if(it[0] < 0) return;
   double n[3];
   n[0] = a[0] + b[0]*it[0];
   n[1] = a[1] + b[1]*it[0];
   n[2] = a[2] + b[2]*it[0];
   muls(b, b, -1);
   c[0] = dot(b, n);
   c[1] = c[0];
   c[2] = c[0];
}

void save()
{
   int width, height;
   IMAGE *output;
   
   width  = getmaxx() + 1;
   height = getmaxy() + 1;
   output = createimage(width, height);
   
   getimage(0, 0, width - 1, height - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}

int main()
{
   initwindow(1920, 1080, "Win", 0, 40);
   double cam[3] = {-3, 0, 0};
   for(double i = 0; i < 1080; i++)
   {
      for(double k = 0; k < 1920; k++)
      {
         /*double camf[3], a[3] = {1, k, i};
         norm(a, camf); 
         double col[3];
         CastRay(cam, camf, col);
         //cout << col[0] << col[1] << col[2] << '\n';*/
         putpixel(k, i, COLOR(i*255/1080, k*255/1920, 0));
      }
   }
   save();
   cout << 0;
   getchar();
}