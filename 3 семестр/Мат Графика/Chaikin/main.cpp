#include <iostream>
#include <graphics.h>
#include <time.h>
#include <math.h>

using namespace std;

struct Point
{
   int x, y;
   Point *next;
};

Point *addPoint(int x, int y, Point *root)
{
   if(root == NULL)
   {
      root = new Point;
      root->x = x;
      root->y = y;
      root->next = NULL;
      return root;
   }
   root->next = addPoint(x, y, root->next);
   return root;
}

Point *chaikin(Point *root)
{
   if(root == NULL) return NULL;
   if(root->next == NULL) return root;
   Point *r = root->next;
   Point *a, *b;
   a = new Point;
   b = new Point;
   a->x = root->x+(r->x-root->x)/4;
   a->y = root->y+(r->y-root->y)/4;
   
   b->x = root->x+(r->x-root->x)*3/4;
   b->y = root->y+(r->y-root->y)*3/4;
   b->next = chaikin(r);
   a->next = b;
   return a;
}

void drawLine(Point *root)
{
   if(root == NULL) return;
   if(root->next == NULL) return;
   Point *a = root->next;
   line(root->x, root->y, a->x, a->y);
   drawLine(a);
}

void drawCircle(Point *root)
{
   if(root == NULL) return;
   circle(root->x, root->y, 5);
   drawCircle(root->next);
}

int main()
{
   initwindow(800, 600);
   Point *root = NULL;
   int n = -1;
   Point *a = NULL;
   while(1)
   {
      while(1-mousebuttons())
      {
         n = -1;
         a = root;
      }
      while(a != NULL and n == -1)
      {
         if(abs(mousex()-a->x)<=5 and abs(mousey()-a->y)<=5)
         {
            n = 1;
            break;
         }
         a = a->next;
      }
      if(n == -1)
      {
         root = addPoint(mousex(), mousey(), root);
         while(mousebuttons());
      }
      else 
      {
         a->x = mousex();
         a->y = mousey();
      }
      clearviewport();
      Point *r = chaikin(root);
      r->x = root->x;
      r->y = root->y;
      for(int i = 0; i < 4; i++)
      {
         r = chaikin(r);
         r->x = root->x;
         r->y = root->y;
      }
      drawCircle(root);
      drawLine(r);
   }
}