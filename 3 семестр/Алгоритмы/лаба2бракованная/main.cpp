 #define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;

int* definFigur(string name)
{
   int typeSoluth[3] = {0};
   // ��������� ������� �����
   for(int i = 0; i < name.size(); i++) name[i] = tolower(name[i]);
   // ���������� ������
   if(name == "����")
   {
      typeSoluth[0] = 1;
      typeSoluth[1] = 1;
      typeSoluth[2] = 1;
      return typeSoluth;
   }
   if(name == "������")
   {
      typeSoluth[0] = 1;
      typeSoluth[1] = 2;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "�������������")
   {
      typeSoluth[0] = 1;
      typeSoluth[1] = 3;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "�������")
   {
      typeSoluth[0] = 1;
      typeSoluth[1] = 4;
      typeSoluth[2] = 1;
      return typeSoluth;
   }
   // ��������� ������
   if(name == "��������������� ��������")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 1;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "�����")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 2;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "���")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 3;
      typeSoluth[2] = 1;
      return typeSoluth;
   }
   if(name == "������ ������������")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 4;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "�������")
   {
      typeSoluth[0] = 2;
      typeSoluth[1] = 5;
      typeSoluth[2] = 2;
      return typeSoluth;
   }
   if(name == "���������")
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
   string answer = "�� ����������� ������";
   if(typeSoluth[0] == 1)
   {
      double s, p;
      if(typeSoluth[1] == 1) // ����  r
      {
         s = M_PI*param[0]*param[0];
         p = 2*M_PI*param[0];
         answer =  "S=" + to_string(s) + ", P=" + to_string(p);
         return answer;
      }
      if(typeSoluth[1] == 2) // ������  r1, r2
      {
         s = M_PI*param[0]*param[1];
         p = 4*(M_PI*param[0]*param[1]+param[0]-param[1])/(param[0]+param[1]);
         answer =  "S=" + to_string(s) + ", P=" + to_string(p);
         return answer;
      }
      if(typeSoluth[1] == 3) // �������������  a, b
      {
         s = param[0]*param[1];
         p = 2*(param[0]+param[1]);
         answer =  "S=" + to_string(s) + ", P=" + to_string(p);
         return answer;
      }
      if(typeSoluth[1] == 4) // �������  a
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
      if(typeSoluth[1] == 1) // ��������������� ��������  a, h
      {
         v = param[0]*param[0]*param[1]/3;
         double l = sqrt(h*h+a*a/4);
         s = a*a+l*a*2;
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 2) // ����� r, h
      {
         v = M_PI*param[0]*param[0]*param[1]/3;
         double l;
         l = sqrt(param[0]*param[0]+param[1]*param[1]);
         s = M_PI*param[0]*(param[0]+l);
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 3) // ��� a
      {
         v = param[0]*param[0]*param[0];
         s = 6*param[0]*param[0];
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 4) // ������ ������������ a, h
      {
         double p = 3*param[0]/2;
         double sba = sqrt(p*pow(p-param[0], 3));
         v = sba*param[1];
         s = sba*2+5*param[0]*param[1];
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 5) // ������� r, h
      {
         v = M_PI*param[0]*param[0]*param[1];
         s = M_PI*param[0]*param[0]*2+2*M_PI*param[0]*param[1];
         answer =  "V=" + to_string(v) + ", S=" + to_string(s);
         return answer;
      }
      if(typeSoluth[1] == 6) // ��������� r
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