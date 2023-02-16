




using namespace std;

struct Point
{
   int x, y;
   Point *next;
};

Point *addPoint(int x, int y, Point *one)
{
   if(one == NULL)
   {
      one = new Point;
      one->x = x;
      one->y = y;
      one->next = NULL;
      return one;
   }
   one->next = addPoint(x, y, one->next);
   return one;
}

void lineVu(int x1, int y1, int x2, int y2, int col[3][2])
{
   linesettingstype *s;
   getlinesettings(s);
   cout << _abracadabra_cast(*(s));