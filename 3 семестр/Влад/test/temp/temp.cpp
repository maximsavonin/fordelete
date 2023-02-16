

using namespace std;

class A
{
   public:
      void f();
};

class B
{
   public:
      void f();
};

class C: public A, public B
{
};


int main()
{
   C c1;
   _abracadabra_cast(c1);