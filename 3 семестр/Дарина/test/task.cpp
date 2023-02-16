#include "graphics.h"
#include "task.h"
#include <cmath>
#include <iostream>

using namespace std;

Figure::Figure() 
{
   ifstream f("crystal.txt");
   f >> VertexNum >> FaceNum;
   vertices.resize(VertexNum, vector <double> (3));
   for (int i = 0; i < VertexNum; i++)
      for (int j = 0; j < 3; j++)
         f >> vertices[i][j];
   
   faces.resize(FaceNum, vector <int> (VertexNum));
   for (int i = 0; i < FaceNum; i++)
      for (int j = 0; j < 3; j++)
         f >> faces[i][j];
   
   cx = cy = cz  =0;
   
   f.close();
}

void Figure::move(int plot, int direct){
   cx += direct*dx[plot];
   cy += direct*dy[plot];
   cz += direct*dz[plot];
   for (int i = 0; i < VertexNum; i++){
      vertices[i][0] += direct*dx[plot];
      vertices[i][1] += direct*dy[plot];
      vertices[i][2] += direct*dz[plot];
   }
}

void Figure::rotate(int plot)
{
   double temp, angle  = acos(-1) / 20;
   
   for (int i = 0; i < VertexNum; i++)
   {
      vertices[i][0] -= cx;
      vertices[i][1] -= cy;
      vertices[i][2] -= cz;
   }
   
   if(plot == 0)
   {
      for (int i = 0; i < VertexNum; i++)
      {
         temp = vertices[i][0];
         vertices[i][0] = vertices[i][0]*cos(angle)
                           + vertices[i][1]*sin(angle);
         vertices[i][1] = - temp * sin(angle)
                     + vertices[i][1]*cos(angle);
      }
   }
   if(plot == 1)
   {
      for (int i = 0; i < VertexNum; i++)
      {
         temp = vertices[i][0];
         vertices[i][0] = vertices[i][0]*cos(angle)
                              + vertices[i][2]*sin(angle);
         vertices[i][2] = - temp * sin(angle)
                        + vertices[i][2]*cos(angle);
      }
   }
   if(plot == 2)
   {
      for (int i = 0; i < VertexNum; i++)
      {
         temp = vertices[i][1];
         vertices[i][1] = vertices[i][1] * cos(angle)
                        + vertices[i][2] * sin(angle);
         vertices[i][2] = - temp * sin(angle)
                     + vertices[i][2]*cos(angle);
      }
   }
   for (int i = 0; i < VertexNum; i++)
   {
      vertices[i][0] += cx;
      vertices[i][1] += cy;
      vertices[i][2] += cz;
   }
}

void Figure::draw(int plot)
{
   int k;
   setcolor(COLOR(0,255,127));
   setfillstyle(SOLID_FILL, COLOR(0,255,127));
   setlinestyle(SOLID_LINE, 0, 2);
   if(plot == 0)
   {
      for(int i=0; i<FaceNum; i++)
      {
         k = 0;
         for(int j=0; j<3; j++)
         {
               p[2*k] = WIDTH/4 + vertices[faces[i][j]][0];
               p[2*k+1] = HEIGHT/2 - vertices[faces[i][j]][1];
               k++;
         }
         p[2*k] = p[0];
         p[2*k+1] = p[1];
         k++;
         drawpoly(k, p);
      }
   }
   if(plot == 1)
   {
      for(int i=0; i<FaceNum; i++)
      {
         k = 0;
         for(int j=0; j<3; j++)
         {
               p[2*k] = WIDTH/2 + vertices[faces[i][j]][0];
               p[2*k+1] = 5*HEIGHT/8 - vertices[faces[i][j]][2];
               k++;
         }
         p[2*k] = p[0];
         p[2*k+1] = p[1];
         k++;
         drawpoly(k, p);
      }
   }
   if(plot == 2)
   {
      for(int i=0; i<FaceNum; i++)
      {
         k = 0;
         for(int j=0; j<3; j++)
         {
               p[2*k] = 3*WIDTH/4 + vertices[faces[i][j]][1];
               p[2*k+1] = 5*HEIGHT/8 - vertices[faces[i][j]][2];
               k++;
         }
         p[2*k] = p[0];
         p[2*k+1] = p[1];
         k++;
         drawpoly(k, p);
      }
   }
}

void save()
{
   int W, H;
   IMAGE *output;

   W = getmaxx() + 1;
   H = getmaxy() + 1;
   output = createimage(W, H);

   getimage(0, 0, W - 1, H - 1, output);
   getimage(0, 0, W - 1, H - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}
