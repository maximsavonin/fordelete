#include <iostream>
#include <graphics.h>
#include <time.h>
#include <math.h>

#define TIM 1000

using namespace std;

struct Point
{
   int x, y;
};

Point bez(Point all[100], int n, double t)
{
   Point sop[100];
   for(int i = 0; i < n-1; i++)
   {
      sop[i].x = all[i].x+(all[i+1].x-all[i].x)*t;
      sop[i].y = all[i].y+(all[i+1].y-all[i].y)*t;
   }
   if(n<= 2) return sop[0];
   return bez(sop, n-1, t);
}

void pefog(int pef[100], int k, int n)
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

int main()
{
   initwindow(800, 600);
   
   setfillstyle(SOLID_FILL, RED);
   bar(0, 550, 50, 600);
   
   Point all[100];
   int n = 0;
   
   while(1)
   {
      while(1-mousebuttons());
      if(abs(mousex()-25) <= 25 and abs(mousey()-575) <= 25)
      {
         n = 0;
         clearviewport();
         setfillstyle(SOLID_FILL, RED);
         bar(0, 550, 50, 600);
         while(mousebuttons());
         continue;
      }
      all[n] = {mousex(), mousey()};
      n++;
      while(mousebuttons());
      if(n>1)
      {
         clearviewport();
         setfillstyle(SOLID_FILL, RED);
         bar(0, 550, 50, 600);
         for(int i = 0; i < TIM; i++)
         {
            double t = 1.0*i/TIM;
            Point a = {0, 0};
            int pef[100] = {0};
            pef[0] = 1;
            pef[1] = 1;
            pefog(pef, 2, n);
            for(int k = 0; k < n; k++)
            {
               a.x += pef[k]*pow(1-t, n-k-1)*pow(t, k)*all[k].x;
               a.y += pef[k]*pow(1-t, n-k-1)*pow(t, k)*all[k].y;
            }
            //Point a = bez(all, n, t);
            putpixel(a.x, a.y, WHITE);
         }
      }
   }
}