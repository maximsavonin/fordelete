 #define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;

int* definFigur(string name)
{
   int typeSoluth[3] = {0};
   // уменьшаем регистр слова
   for(int i = 0; i < name.size(); i++) name[i] = tolower(name[i]);
   // двухмерные фигуры
   if(name == "круг")
   {
      typeSoluth[0] = 1;
      typeSoluth[1] = 1;
      typeSoluth[2] = 1;
      return typeSoluth;
   }
   if(name == "эллипс")
   {
      typeSoluth[0] = 1;
      typeSoluth[1] = 2;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "прямоугольник")
   {
      typeSoluth[0] = 1;
      typeSoluth[1] = 3;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "квадрат")
   {
      typeSoluth[0] = 1;
      typeSoluth[1] = 4;
      typeSoluth[2] = 1;
      return typeSoluth;
   }
   // трёхмерные фигуры
   if(name == "четырехугольный тетраэдр")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 1;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "конус")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 2;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "куб")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 3;
      typeSoluth[2] = 1;
      return typeSoluth;
   }
   if(name == "призма пятиугольная")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 4;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "цилиндр")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 5;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "эллипсоид")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 6;
      typeSoluth[2] = 1;
      return typeSoluth;
   }
   
   return typeSoluth;
}

string findParam(string name)
{
   int typeSoluth[3] = {0};
   typeSoluth = definFigur(name);
   double param[3] = {0};
   for(int i = 0; i < typeSoluth[2]; i++) 
      cin >> param[i];
   string answer = "Не определённая фигура";
   if(typeSoluth[0] == 1)
   {
      double s, p;
      if(typeSoluth[1] == 1) // круг  r
      {
         s = M_PI*param[0]*param[0];
         p = 2*M_PI*param[0];
         answer =  "S=" + to_string(s) + ", P=" + to_string(p);
         return answer;
      }
      if(typeSoluth[1] == 2) // эллипс  r1, r2
      {
         s = M_PI*param[0]*param[1];
         p = 4*(M_PI*param[0]*param[1]+param[0]-param[1])/(param[0]+param[1]);
         answer =  "S=" + to_string(s) + ", P=" + to_string(p);
         return answer;
      }
      if(typeSoluth[1] == 3) // прямоугольник  a, b
      {
         s = param[0]*param[1];
         p = 2*(param[0]+param[1]);
         answer =  "S=" + to_string(s) + ", P=" + to_string(p);
         return answer;
      }
      if(typeSoluth[1] == 4) // квадрат  a
      {
         s = param[0]*param[0];
         p = 4*param[0];
         answer =  "S=" + to_string(s) + ", P=" + to_string(p);
         return answer;
      }
      return answer;
   }
   
   if(typeSoluth[0] == 2)
   {
      double v, s;
      if(typeSoluth[1] == 1) // четырехугольный тетраэдр  a, h
      {
         v = param[0]*param[0]*param[1]/3;
         double l = sqrt(h*h+a*a/4);
         s = a*a+l*a*2;
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 2) // конус r, h
      {
         v = M_PI*param[0]*param[0]*param[1]/3;
         double l;
         l = sqrt(param[0]*param[0]+param[1]*param[1]);
         s = M_PI*param[0]*(param[0]+l);
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 3) // куб a
      {
         v = param[0]*param[0]*param[0];
         s = 6*param[0]*param[0];
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 4) // призма пятиугольная a, h
      {
         double p = 3*param[0]/2;
         double sba = sqrt(p*pow(p-param[0], 3));
         v = sba*param[1];
         s = sba*2+5*param[0]*param[1];
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 5) // цилиндр r, h
      {
         v = M_PI*param[0]*param[0]*param[1];
         s = M_PI*param[0]*param[0]*2+2*M_PI*param[0]*param[1];
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 6) // эллипсоид r
      {
         int n = 1.6075;
         v = 4*M_PI*param[0]*param[0]*param[0]/3;
         s = 4*M_PI*param[0]*param[0];
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      return answer;
   }
   return answer;
}

int main()
{
   string name, answer;
   cin >> name;
   answer = findParam(typeSoluth, param);
   cout << answer;
   return 0;
}