#include <iostream>

using namespace std;

class ASet
{
   int a, b;
   bool *f;
  public:
    ASet(int a, int b): a(a), b(b), f(new bool[b-a+1]) {for(int i = 0; i < b-a+1; i++) f[i] = 1;}
    ASet(int){ASet(0, b);}    // a �� ��������� 0
    ~ASet(){delete[] f;};
    void incl(int);  // �������� ����� � ���������
                     // ���� ����� ����� ��� ����, �� ������ �� ������
    void excl(int);  // ���������
    bool contain(int); // ���������� � ���������?
    void print(); // ����������� ��������� �������
};

void ASet::incl(int n)
{
   if(n < a or n > b) return;
   f[n-a] = 1;
}

void ASet::excl(int n)
{
   if(n < a or n > b) return;
   f[n-a] = 0;
}

bool ASet::contain(int n)
{
   if(n < a or n > b) return false;
   return f[n-a];
}

void ASet::print()
{
   for(int i = 0; i < b-a+1; i++)
   {
      if(f[i]) cout << a+i << ' ';
   }
}

int main()
{
   ASet obj(1, 8);
   obj.print();
   cout << endl;
   obj.excl(0);
   obj.excl(2);
   obj.excl(4);
   obj.print();
   cout << endl;
   obj.incl(0);
   obj.incl(2);
   obj.incl(1);
   obj.print();
   cout << endl;
   cout << obj.contain(0) << endl;
   cout << obj.contain(1) << endl;
   cout << obj.contain(2) << endl;
   return 0;
}