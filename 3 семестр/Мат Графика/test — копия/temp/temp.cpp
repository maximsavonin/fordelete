



using namespace std;

struct Point
{
   int x, y;
};

void change_figure(Point romb[5], Point &param, int i, double &fi)
{
   if(i < 5)
   {
      int x0 = romb[i].x, y0 = romb[i].y;
      double a = asin(y0 / pow(x0*x0 + y0*y0, 1.0/2));
      if(x0 < 0)
      {
         a = acos(-1) - a;
      }
      a+=fi;
      int x = cos(a)*abs(param.x*x0+param.y*y0);
      int y = sin(a)*abs(param.x*x0+param.y*y0);
      int del = sqrt(pow(_abracadabra_cast(romb[0]);