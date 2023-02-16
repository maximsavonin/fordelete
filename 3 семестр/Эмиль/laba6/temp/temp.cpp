#define _USE_MATH_DEFINES




struct Point
{
   int x, y;
};

void draw(Point center, Point *figure){
   setfillstyle(SOLID_FILL, COLOR(255, 255, 0));
   int *points;
   points = new int[8]();
   for(int i=0; i<4; i++){
      points[2*i] = figure[i].x+center.x;
      points[2*i+1] = figure[i].y+center.y;
   }
   fillpoly(4, points);
   setfillstyle(SOLID_FILL,GREEN);
   delete [] points;
}

void scale(Point figure, double s){
   for(int i=0; i<4; i++){
      figure[i].x *= s;
      figure[i].y *= s;
   }
}

void spin(Point figure, double fi){
   double x;
   for(int i=0;i<n;i++){
      x = figure[i].x;
      figure[i].x = cos(fi)*figure[i].x-sin(fi)*_abracadabra_cast(figure[i]);