#include <iostream>
#include <format>
#include <cstdlib>
#include <cmath>

using namespace std;

int checkCoefficient(float a, float b, float c)
{
   if (a != 0) return 1;
   if (b != 0) return 2;
   if (c != 0) return 3;
   return 4;
}

int checkD(float D)
{
   if (D == 0) return 1;
   if (D > 0) return 2;
   return 3;
}

string calculateRoots(float a, float b, float c)
{
   float D;
   string roots;

   int typeExpressions = checkCoefficient(a, b, c);
   if (typeExpressions == 4)
   {
      roots = "Корень: любое число";
      return roots;
   }
   if (typeExpressions == 3)
   {
      roots = "Ошибка входных значений";
      return roots;
   }
   if (typeExpressions == 2)
   {
      float x = - c / b;
      sprintf(roots, "Корень: %f", x);
      return roots;
   }
   if (typeExpressions == 1)
   {
      D = b * b - 4 * a * c;
      int numberSolution = checkD(D);
      if (numberSolution == 1)
      {
         float x = - b / (2 * a);
         sprintf(roots, "Корень: %f", x);
         return roots;
      }
      if (numberSolution == 2)
      {
         float x1 = (- b + sqrt(D)) / (2 * a);
         float x2 = (- b - sqrt(D)) / (2 * a);
         sprintf(roots, "Корени: %f; %f", x1, x2);
         return roots;
      }
      if (numberSolution == 3)
      {
         float c1 = - b / a;
         float c2 = sqrt(fabs(D)) / (2 * a);
         sprintf(roots, "Корни: %f+%fi; %f-%fi", c1, c2, c1, c2);
         return roots;
      }
   }
   return roots;
}

int main()
{
   float a, b, c;
   string roots;

   cin>> a >> b >> c;

   roots = calculateRoots(a, b, c);

   cout << roots;

   return 0;
}