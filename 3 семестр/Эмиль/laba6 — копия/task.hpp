#ifndef TASK_HPP
#define TASK_HPP
class Figure{
   double *x;
   double *y;
   double x0,y0;
   int n;
   public:
   Figure(int,double,double,double *,double *);
   ~Figure();
   void Draw(int);
   void GoTo(int,int);
   void Scale(double);
   void Spin(double);
};
void save();
#endif