






using namespace std;

void creatPoint(Circ a[2], int left, int top, int width, int height)
{
   setfillstyle(SOLID_FILL, BLACK);
   bar(left, top, width, height);
   srand(time(0));
   
   left += 100;
   top += 100;
   width -= 100;
   height -= 100;
   for(int i = 0; i < 2; i++)
   {
      a[i].x = rand()%(width-left)+left;
      a[i].y = rand()%(height-top)+top;
      a[i].r = rand()%50 + 50;
      
      setfillstyle(SOLID_FILL, BLACK);
      setcolor(WHITE);
      circle(a[i].x, a[i].y, a[i].r);
   }
}

void draw(double x, double y)
{
   if(getpixel(x, y) == 0)
   {
      delay(10);
      putpixel(x, y, WHITE);
      draw(x+1, y);
      draw(x-1, y);
      draw(x, y+1);
      draw(x, y-1);
   }
}

void treat(Circ a[2])
{
   double x = abs(a[0].x-a[1].x);
   double y = abs(a[0].y-a[1].y);
   
   if(sqrt(x*x+y*y) < a[0].r+a[1].r)
   {
      //double d[2] = {abs(x-a[0].r+a[1].r)/2.0, abs(y-a[0].r+a[1].r)/2.0};
      double d[2] = {(a[0].r+a[1].r-sqrt(x*x+y*y))/2, 0};
      d[1] = d[0];
      cout << a[0].x << ' ' << a[0].y << ' ' << a[0].r << ' ' << a[1].x << ' ' << a[1].y << ' ' << a[1].r << endl;
      cout << d[0] << ' ' << x << ' ' << y<< endl;
      if(a[0].x > a[1].x)
      {
         d[0] = (a[1].r-d[0])/sqrt(x*x+y*y);
         x = a[1].x+d[0]*x;
         y = a[0].y > _abracadabra_cast(a[1]);