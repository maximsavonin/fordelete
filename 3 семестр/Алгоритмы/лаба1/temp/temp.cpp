




using namespace std;

int checkCoef(double a, double b, double c)
{
   if(a != 0) return 1;
   if(b != 0) return 2;
   if(c != 0) return 0;
   return 3;
}

string calcRoots(double a, double b, double c)
{
   string roots = "";
   int typeSoluth = checkCoef(a, b, c);
   if(typeSoluth == 0)
   {
      roots = "не правильные коэфициенты";
      return roots;
   }
   if(typeSoluth == 3)
   {
      roots = "корней нет";
      return roots;
   }
   if(typeSoluth == 2)
   {
      double x = -c/b;
      roots = "корень " + to_string(x);
      return roots;
   }
   
   double D = b*b - 4*a*c;
   if(D == 0)
   {
      double x = -b/(2*a);
      roots = "корень " + to_string(x);
      return roots;
   }
   if(D > 0)
   {
      double x1, x2;
      x1 = (-b+sqrt(D))/(2*a);
      x2 = (-b-sqrt(D))/(2*a);
      roots = "корни " + to_string(x1) + ' ' + to_string(x2);
      return roots;
   }
   double c1, c2;
   c1 = -b/(2*a);
   c2 = sqrt(-D)/(2*a);
   roots = "корни " + to_string(c1) + "+/-i" + to_string(c2);
   return roots;
}

int main()
{
   double a, b, c;
   cin >> a >> b >> c;
   string roots = calcRoots(a, b, c);
   cout << roots;
   vector<int> a;
   _abracadabra_cast(a);