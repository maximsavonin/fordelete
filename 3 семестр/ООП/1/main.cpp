#include <iostream>
#include <string>

using namespace std;

struct Data 
{ 
   long prioritet;
   string info;
};
class PQueue
{
   int n, size, firstNum;
   Data *data;
   public:
      PQueue(int maxsize=100);
      ~PQueue(){delete[] data;}
      void add(const Data &dat);    // добавить данные
      const Data& first();          // получить данные с наименьшим приоритетом
      void next(); // убрать данные с наименьшим приоритетом
      bool isEmpty();               // очередь пуста
      bool isFull();                // очередь полна
      void print();  // распечатать состояние объекта
};

PQueue::PQueue(int maxsize)
{
   size = maxsize;
   n = 0;
   firstNum = 0;
   data = new Data[maxsize];
}

void PQueue::add(const Data &dat)
{
   if(isFull())
   {
      cout << "Очередь переполнена" << endl;
      exit(1);
   }
   data[firstNum+n] = dat;
   n++;
}

const Data& PQueue::first()
{
   Data& a = data[firstNum];
   for(int i = 1; i < n; i++)
   {
      if(a.prioritet > data[firstNum+i].prioritet) a = data[firstNum+i];
   }
   return a;
}

void PQueue::next()
{
   Data& a = data[firstNum];
   int k=firstNum;
   for(int i = 1; i < n; i++)
   {
      if(a.prioritet > data[firstNum+i].prioritet)
      {
         a = data[firstNum+i];
         k = i;
      }
   }
   for(int i = k+firstNum; i > firstNum; i--)
   {
      data[i] = data[i-1];
   }
   n--;
   firstNum++;
}

bool PQueue::isEmpty()
{
   return n == 0;
}

bool PQueue::isFull()
{
   return n == size;
}

void PQueue::print()
{
   cout << n << ' ' << size << endl;
   for(int i = 0; i < n; i++)
   {
      cout << data[firstNum+i].info << ' ';
   }
   cout << endl;
   for(int i = 0; i < n; i++)
   {
      cout << data[firstNum+i].prioritet << ' ';
   }
   cout << endl;
}

int main()
{
   PQueue a = PQueue(10);
   Data b;
   for(int i = 0; i < 10; i++)
   {
      b.info = 'a'+i;
      b.prioritet = i;
      a.add(b);
   }
   b = a.first();
   cout << b.info << ' ' << b.prioritet << endl;
   a.print();
   a.next();
   a.print();
   cout << a.isFull() << ' ' << a.isEmpty();
}