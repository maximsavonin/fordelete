





using namespace std;

double pi = 3.14; // число pi
int w = 1300, h = 800, radius = 20; //размер экрана и шара

struct Ball
{
   double x = 0;
   double y = 0;
   double fi = 0;
   int color = 0;
};

void zuballC(double zu_ball[5])
{
   zu_ball[0] = w/2;
   zu_ball[1] = h/2;
   zu_ball[2] = rand() % 6 + 1;
   zu_ball[4] = 0;
}

void setBall(Ball &a, double fi) // функция задания координат шара по углу
{
   a.fi = fi;
   a.x = 25*a.fi*(-cos(a.fi))+w/2;
   a.y = 18*a.fi*(-sin(a.fi))+h/2;
}

void creatball(Ball &a, double fi)
{
   a.color = rand() % 6 + 1;
   setBall(a, fi);
}

void shot(double zu_ball[5])
{
   ;
}

void flyb(Ball Balls[150], double zu_ball[5], int &n)
{
   zu_ball[0] += 10*cos(zu_ball[3]);
   zu_ball[1] += 10*sin(zu_ball[3]);
   if(abs(zu_ball[0]-w/2) > w/2 || abs(zu_ball[1]-h/2) > h/2)
   {
      zuballC(zu_ball);
      return;
   }
   for(int i = 0; i < n; i++)
   {
      double x = Balls[i].x-zu_ball[0];
      double y = Balls[i].y-zu_ball[1];
      if(sqrt(x*x+y*y) <= radius+1)
      {
         for(int k = n; k > i; k--)
         {
            Balls[k] = Balls[k-1];
         }
         Balls[i].color = zu_ball[2];
         zuballC(zu_ball);
         n++;
         break;
      }
   }
}

int main()
{
   double fim; //угол отклонения муши от оси Ox
   int n = 1, l = 0; // количество шаров и таймер появления нового
   int po[8]; // вершины центрального треугольника
   initwindow( w, h,"ZUMA",75,25);
   setbkcolor(WHITE);
   Ball Balls[150];
   double zu_ball[5];
   zuballC(zu_ball);
   creatball(Balls[0], pi*6.5);
   setcolor(BLACK);
   delay(1000);
   while(1)
   {
      
      int xv, yv, xk, yk;
      double xpi, ypi;
      xv = mousex() - w/2;
      yv = mousey() - h/2;
      fim = asin(yv / pow(xv*xv + yv*yv, 1.0/2));
      if(xv < 0)
      {
         fim = pi - fim;
      }
      po[0] = w/2.0 + 70*cos(fim);
      po[1] = h/2.0 + 70*sin(fim);
      po[2] = w/2.0 + 70*cos(fim+2*pi/3);
      po[3] = h/2.0 + 70*sin(fim+2*pi/3);
      po[4] = w/2.0 + 70*cos(fim+4*pi/3);
      po[5] = h/2.0 + 70*sin(fim+4*pi/3);
      po[6] = po[0];
      po[7] = po[1];
      drawpoly(4, po);
      if(mousebuttons() == 1 && zu_ball[4] == 0)
      {
         zu_ball[4] = 1;
         zu_ball[3] = fim;
      }
      if(zu_ball[4])
      {
         flyb(Balls, zu_ball, n);
      }
      
      for(int i = 0; i < n; i++)
      {
         while(1)
         {
            Balls[i].fi -= 0.001;
            double x, y;
            x = 25*Balls[i].fi*(-cos(Balls[i].fi))+w/2;
            y = 18*Balls[i].fi*(-sin(Balls[i].fi))+h/2;
            if(pow(Balls[i].x-x, 2)+pow(Balls[i].y-y, 2) > 16)
            {
               if(pow(Balls[i].x-x, 2)+pow(Balls[i].y-y, 2) > 25)
               {
                  Balls[i].fi += 0.0011;
               }
               else break;
            }
         }
         setBall(Balls[i], Balls[i].fi);
         setfillstyle(SOLID_FILL, _abracadabra_cast(Balls[i]);