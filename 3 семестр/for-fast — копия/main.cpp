#include <iostream>
#include <graphics.h>
#include <time.h>
#include <math.h>

#define TIM 1000

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

Point *abc(Point *root)
{
   Point *a = root->next;
   if(a == NULL) return root;
   Point *b = a->next;
   if(b == NULL) return root;
   Point c = {root->x + (a->x - root->x), root->y + (a->y - root->y), NULL};
   Point d = {a->x + (b->x - a->x), a->y + (b->y - a->y), NULL};
   d.next = abc(a);
   c.next = &d;
   root = &c;
   return root;
}

Point *popitka(Point *root)
{
   if(root == NULL) return root;
   Point *a = root->next;
   if(a == NULL) return root;
   Point *b;
   root->x = root->x + (a->x - root->x)/4;
   root->y = root->y + (a->y - root->y)/4;
   
   b->x = root->x + (a->x - root->x)*3/4;
   b->y = root->y + (a->y - root->y)*3/4;
   
   b->next = popitka(a);
   root->next = b;
   return root;
}

Point *chaikin(Point *root)
{
   Point *a = addPoint(0, 0, NULL);
   cout << '!';
   a->x = root->x;
   cout << '!';
   a->y = root->y;
   cout << '!';
   a->next = popitka(root);
   return a;
}

void draw(Point *root)
{
   if(root == NULL) return;
   Point *a = root->next;
   if(a == NULL) return;
   cout << root->x << ' ' << root->y << endl;
   cout << a->x << ' ' << a->y << endl;
   line(root->x, root->y, a->x, a->y);
   draw(a);
}

int main()
{
   initwindow(800, 600);
   
   setfillstyle(SOLID_FILL, RED);
   bar(0, 550, 50, 600);
   
   Point *root = NULL;
   int n = 0;
   
   while(1)
   {
      Point *rootCop;
      while(1-mousebuttons());
      if(abs(mousex()-25) <= 25 and abs(mousey()-575) <= 25)
      {
         clearviewport();
         setfillstyle(SOLID_FILL, RED);
         bar(0, 550, 50, 600);
         while(mousebuttons());
         continue;
      }
      root = addPoint(mousex(), mousey(), root);
      while(mousebuttons());
      rootCop = chaikin(root);
      clearviewport();
      setfillstyle(SOLID_FILL, RED);
      bar(0, 550, 50, 600);
      cout << '!';
      draw(rootCop);
   }
}