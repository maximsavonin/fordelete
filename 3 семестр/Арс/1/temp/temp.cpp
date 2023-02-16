

using namespace std;

class ASet
{
   int a, b;
   bool *f;
  public:
    ASet(int a, int b): a(a), b(b), f(new bool[b-a+1]) {for(int i = 0; i < b-a+1; i++) f[i] = 1;}
    ASet(int){ASet(0, b);}    // a по умолчанию 0
    ~ASet(){delete[] f;};
    void incl(int);  // включить число в множество
                     // если такое число уже есть, то ничего не делать
    void excl(int);  // исключить
    bool contain(int); // содержится в множестве?
    void print(); // распечатать состояние объекта
};

void ASet::incl(int n)
{
   if(n < a or n > b) return;
   f[n-a] = 1;
}

void ASet::excl(int n)
{
   if(n < a or n > b) return;
   f[n] = 0;
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
      if(f[i]) cout << b+i << ' ';
   }
}

int main()
{
   ASet obj(1, 8);
   obj.print();
   obj.excl(0);
   obj.excl(2);
   obj.excl(4);
   obj.print();
   _abracadabra_cast(obj);