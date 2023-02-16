#include <iostream>

using namespace std;

struct arrayerror { // базовый класс для ошибок
   virtual ~arrayerror() {} // деструктор
   virtual const char *what() const=0; // сообщение для печати
};

struct arrayoutofrange: arrayerror {
   const char *what() const {return "Индекс вне диапозона";} // сообщение для печати
};

template <typename T>
class Array {
   T *a; // указатель на данные в стеке
   int first, // текущее количество
        end;
public:
   Array(int first, int end): first(first), end(end), a(new T[1+end-first]) {} // конструктор
   Array(const Array<T> &); // конструктор копий
   ~Array() throw() {delete []a;} // деструктор
   T &operator[](int); // поиск по ключу
   T operator[](int) const; // поиск по ключу
};

template <typename T>
Array<T>:: Array(const Array <T> &array): a(new T[1+array.end-array.first]), first(array.first), end(array.end) {
   for (int i = first; i <= end; i++)
      a[i]=array.a[i];
}

template <typename T>
T &Array<T>::operator[](int index)
{
   if(index < first or index > end) throw arrayoutofrange();
   return a[index-first];
}

template <typename T>
T Array<T>::operator[](int index) const
{
   if(index < first or index > end) throw arrayoutofrange();
   return a[index-first];
}

int main()
{
   Array<int> obj(2, 10);
   cout<<"Тест 1. Добавление\n";
   try {
      for (int i=2;; i++) {
         obj[i] = i;
      }
   }
   catch (arrayerror &e) {
      cout<<e.what();
   }
   
   cout<<"\nТест 2. Получение по индексу\n";
   try {
      for (int i=2;; i++) {
         cout << (obj[i]) << ' ';
      }
   }
   catch (arrayerror &e) {
      cout<<"\n"<<e.what();
   }
   return 0;
}
