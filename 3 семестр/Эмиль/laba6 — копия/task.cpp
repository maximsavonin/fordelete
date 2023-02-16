#define _USE_MATH_DEFINES
#include <math.h>
#include "graphics.h"
#include "task.h"
bool debug=false;
Figure::Figure(int N,double X0,double Y0,double *X,double *Y){
   x=X;
   y=Y;
   x0=X0;
   y0=Y0;
   n=N;
}

Figure::~Figure(){
   delete [] x;
   delete [] y;
}

void Figure::Draw(int C){
   setfillstyle(SOLID_FILL,C);
   int *temp;
   temp=new int[2*n]();
   for(int j=0,i=0;j<n;i+=2,j++){
      temp[i]=x[j];
      temp[i+1]=y[j];
   }
   fillpoly(n,temp);
   setfillstyle(SOLID_FILL,GREEN);
   if(debug){
      for(int i=0;i<n;i++){
         fillellipse(x[i],y[i],5,5);
         delay(200);
      }
      fillellipse(x0,y0,5,5);
   }
   delete [] temp;
}

void Figure::GoTo(int dx,int dy){
   for(int i=0;i<n;i++){
      x[i]+=dx;
      y[i]+=dy;
   }
   x0+=dx;
   y0+=dy;
}

void Figure::Scale(double S){
   for(int i=0;i<n;i++){
      x[i]=(x[i]-x0)*S+x0;
      y[i]=(y[i]-y0)*S+y0;
   }
}

void Figure::Spin(double A){
   double temp;
   for(int i=0;i<n;i++){
      temp=x[i];
      x[i]=x0+cos(A)*(x[i]-x0)-sin(A)*(y[i]-y0);
      y[i]=y0+sin(A)*(temp-x0)+cos(A)*(y[i]-y0);
   }
}

void save()
{
   int width, height;
   IMAGE *output;

   width  = getmaxx() + 1;
   height = getmaxy() + 1;
   output = createimage(width, height);

   getimage(0, 0, width - 1, height - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}
