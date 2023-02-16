#include <iostream>

using namespace std;

struct arrayerror { // ������� ����� ��� ������
   virtual ~arrayerror() {} // ����������
   virtual const char *what() const=0; // ��������� ��� ������
};

struct arrayoutofrange: arrayerror {
   const char *what() const {return "������ ��� ���������";} // ��������� ��� ������
};

template <typename T>
class Array {
   T *a; // ��������� �� ������ � �����
   int first, // ������� ����������
        end;
public:
   Array(int first, int end): first(first), end(end), a(new T[1+end-first]) {} // �����������
   Array(const Array<T> &); // ����������� �����
   ~Array() throw() {delete []a;} // ����������
   T &operator[](int); // ����� �� �����
   T operator[](int) const; // ����� �� �����
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
   cout<<"���� 1. ����������\n";
   try {
      for (int i=2;; i++) {
         obj[i] = i;
      }
   }
   catch (arrayerror &e) {
      cout<<e.what();
   }
   
   cout<<"\n���� 2. ��������� �� �������\n";
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
