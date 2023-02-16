






double pi = 3.14; // число pi
int w = 1300, h = 800, radius = 20, speed = 5; //размер экрана, шара и скорость иъ перемещени€ по спирали

struct Ball
{
   double x = 0;
   double y = 0;
   double fi = 0;
   int color = 0;
};

void copyball(Ball a, Ball &b) // копирование одной структуры в другую
{
   b.x = a.x;
   b.y = a.y;
   b.fi = a.fi;
   b.color = a.color;
}

void Ballgo(Ball &Balls) //движиение по троектории одного шара
{
   while(1)
   {
      Balls.fi -= 0.001;
      double x, y;
      x = 25*Balls.fi*(-cos(Balls.fi))+w/2;
      y = 18*Balls.fi*(-sin(Balls.fi))+h/2;
      if(pow(Balls.x-x, 2)+pow(Balls.y-y, 2) > pow(speed, 2))
      {
         if(pow(Balls.x-x, 2)+pow(Balls.y-y, 2) > pow(speed, 2) + 2)
         {
            Balls.fi += 0.0011;
         }
         else break;
      }
   }
}

void zuballC(double zu_ball[5]) //шар в л€гушке
{
   zu_ball[0] = w/2;
   zu_ball[1] = h/2;
   zu_ball[2] = 8;
   zu_ball[4] = 0;
}

void setBall(Ball &a, double fi) // функци€ задани€ координат шара по углу
{
   a.fi = fi;
   a.x = 25*a.fi*(-cos(a.fi))+w/2;
   a.y = 18*a.fi*(-sin(a.fi))+h/2;
}

void creatball(Ball &a) // создаЄт новый шар в начале пути
{
   a.color = rand() % 6 + 1;
   setBall(a, 6.5*pi);
}

void flyb(Ball Balls[150], double zu_ball[5], int &n) // полЄт шара после выстрела
{
   zu_ball[0] += 30*cos(zu_ball[3]);
   zu_ball[1] += 30*sin(zu_ball[3]);
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
            copyball(Balls[k-1], Balls[k]);
         }
         Balls[i].color = zu_ball[2];
         zuballC(zu_ball);
         n++;
         for(int k = 0; k <= i; k++)
         {
            for(int j = 0; j < 2*radius/speed; j++) Ballgo(Balls[k]);
            clearviewport();
            for(int i = 0; i < n; i++)
            {
               setfillstyle(SOLID_FILL, Balls[i].color);
               fillellipse(Balls[i].x, Balls[i].y, radius, radius);
            }
            delay(500);
         }
         for(int i = 0; i < n; i++) printf("%lf %lf %d\n", Balls[i].x, _abracadabra_cast(Balls[i]);