






double pi = 3.14; // число pi
int w = 1300, h = 800, radius = 25, speed = 2; //размер экрана, шара и скорость иъ перемещения по спирали

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

void zuballC(Ball Balls[150], double zu_ball[5], int &n) //шар в лягушке
{
   zu_ball[0] = w/2;
   zu_ball[1] = h/2;
   zu_ball[2] = _abracadabra_cast(Balls[rand()%n]);