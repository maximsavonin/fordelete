 #define _USE_MATH_DEFINES




using namespace std;

int definFigur(string name)
{
   int numberParam = 0;
   // ���������� ������
   if(name == "����")
   {
      numberParam = 1;
      return numberParam;
   }
   if(name == "������")
   {
      numberParam = 2;
      return numberParam;
   }
   if(name == "�������������")
   {
      numberParam = 2;
      return numberParam;
   }
   // ��������� ������
   if(name == "��������������� ��������")
   {
      numberParam = 2;
      return numberParam;
   }
   if(name == "�����")
   {
      numberParam = 2;
      return numberParam;
   }
   if(name == "���")
   {
      numberParam = 1;
      return numberParam;
   }
   if(name == "������ ������������")
   {
      numberParam = 2;
      return numberParam;
   }
   if(name == "�������")
   {
      numberParam = 2;
      return numberParam;
   }
   if(name == "���������")
   {
      numberParam = 1;
      return numberParam;
   }
   
   return numberParam;
}

string considerCircle(double param[3]);
string considerAlips(double param[3]);
string considerRectangle(double param[3]);
string consider5(double param[3]);
string consider4Tetr(double param[3]);
string considerConus(double param[3]);
string considerCub(double param[3]);
string considerPrizma5(double param[3]);
string considerCilindr(double param[3]);
string considerAlipsoid(double param[3]);

string considerCircle(double param[3])
{
   double s = M_PI*param[0]*param[0];
   double p = 2*M_PI*param[0];
   string answer =  "S=" + to_string(s) + ", P=" + to_string(p);
   return answer;
}

string considerAlips(double param[3])
{
   if(param[0] == param[1]) return considerCircle(param);
   double s = M_PI*param[0]*param[1];
   double p = 4*(M_PI*param[0]*param[1]+param[0]-param[1])/(param[0]+param[1]);
   string answer =  "S=" + to_string(s) + ", P=" + to_string(p);
   return answer;
}

string considerRectangle(double param[3])
{
   double s = param[0]*param[1];
   double p = 2*(param[0]+param[1]);
   string answer =  "S=" + to_string(s) + ", P=" + to_string(p);
   return answer;
}

string consider5(double param[3])
{
   double p = 3*param[0]/2;
   double sba = sqrt(p*pow(p-param[0], 3));
   double v = sba*param[1];
   double s = sba*2+5*param[0]*param[1];
   string answer =  "V=" + to_string(v) + ", S=" + to_string(s);
   return answer;
}

string consider4Tetr(double param[3])
{
   if(param[1] == 0) return considerRectangle(param);
   double v = param[0]*param[0]*param[1]/3;
   double l = sqrt(param[1]*param[1]+param[0]*param[0]/4);
   double s = param[0]*param[0]+l*param[0]*2;
   string answer =  "V=" + to_string(v) + ", S=" + to_string(s);
   return answer;
}

string considerConus(double param[3])
{
   if(param[0] == 0)
   {
      param[0] = param[1];
      return considerCircle(param);
   }
   double v = M_PI*param[0]*param[0]*param[1]/3;
   double l = sqrt(param[0]*param[0]+param[1]*param[1]);
   double s = M_PI*param[0]*(param[0]+l);
   string answer =  "V=" + to_string(v) + ", S=" + to_string(s);
   return answer;
}

string considerCub(double param[3])
{
   double v = param[0]*param[0]*param[0];
   double s = 6*param[0]*param[0];
   string answer =  "V=" + to_string(v) + ", S=" + to_string(s);
   return answer;
}

string considerPrizma5(double param[3])
{
   double p = 3*param[0]/2;
   double sba = sqrt(p*pow(p-param[0], 3));
   double v = sba*param[1];
   double s = sba*2+5*param[0]*param[1];
   string answer =  "V=" + to_string(v) + ", S=" + to_string(s);
   return answer;
}

string considerCilindr(double param[3])
{
   if(param[0] == 0)
   {
      param[0] = param[1];
      return considerCircle(param);
   }
   double v = M_PI*param[0]*param[0]*param[1];
   double s = M_PI*param[0]*param[0]*2+2*M_PI*param[0]*param[1];
   string answer =  "V=" + to_string(v) + ", S=" + to_string(s);
   return answer;
}

string considerAlipsoid(double param[3])
{
   if(param[0] == 0)
   {
      param[0] = param[2];
      return considerAlips(param);
   }
   if(param[1] == 0)
   {
      param[1] = param[2];
      return considerAlips(param);
   }
   if(param[2] == 0)
   {
      return considerAlips(param);
   }
   int n = 1.6075;
   double v = 4*M_PI*param[0]*param[0]*param[0]/3;
   double s = 4*M_PI*param[0]*param[0];
   string answer =  "V=" + to_string(v) + ", S=" + to_string(s);
   return answer;
}

string findParam(string name)
{
   int numberParam = 0;
   // ��������� ������� �����
   for(int i = 0; i < name.size(); i++) name[i] = tolower(name[i]);
   numberParam = definFigur(name);
   if(numberParam == 0) return "�� ����������� ������"; 
   double param[3] = {0};
   for(int i = 0; i < numberParam; i++)
   {
      cin >> param[i];
      if(param[i] < 0)
      {
         cout << "������� ������������� ��������, �� ���� �� ������" << "\n";
         param[i] = -param[i];
      }
   }
   
   if(name == "����") return considerCircle(param);
   if(name == "������") return considerAlips(param);
   if(name == "�������������") return considerRectangle(param);
   if(name == "��������������� ��������") return consider4Tetr(param);
   if(name == "�����") return considerConus(param);
   if(name == "���") return considerCub(param);
   if(name == "������ ������������") return considerPrizma5(param);
   if(name == "�������") return considerCilindr(param);
   if(name == "���������") return considerAlipsoid(param);
   
   return "�� ����������� ������";
}

int main()
{
   string name, answer, a;
   cin >> a;
   while(a != "/n")
   {
      name += a + ' ';
      cin >> a;
   }
   _abracadabra_cast(name);