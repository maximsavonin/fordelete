// Вариант 2
#include <iostream>
#include <random>
#include <time.h>

using namespace std;

int main()
{
   srand(time(0));
   int a, b, n, kol = 0;
   cout << "Ведите количество элементов и их границы:";
   cin >> n >> a >> b;
   int *data = new int[n];
   for(int i = 0; i < n; i++)
   {
      data[i] = rand()%abs(b-a)+a;
   }
   for(int i = 0; i < n; i++)
   {
      cout << data[i] << ' '; 
   }
   cout << endl;
   
   for(int i = 0; i < n; i++)
   {
      for(int k = i+1; k < n; k++)
      {
         if(data[i] == data[k]) kol++;
      }
   }
   
   cout << kol; 
   
   delete[] data;
}