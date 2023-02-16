#include <iostream>

using namespace std;

struct stackerror { // ������� ����� ��� ������
   virtual ~stackerror() {} // ����������
   virtual const char *what() const=0; // ��������� ��� ������
};

struct stackempty: stackerror {
   const char *what() const {return "���� ����";} // ��������� ��� ������
};

struct stackfull: stackerror {
   const char *what() const {return "���� �����";} // ��������� ��� ������
};

struct stacksmall: stackerror {
   const char *what() const {return "���� ������� ��� ��� �����������";} // ��������� ��� ������
};

template <typename T>
class Set {
   T *a; // ��������� �� ������ � �����
   int col, // ������� ����������
         size; // ������������ ������
public:
   // �����������
   Stack(int size): col(0), size(size),a(new T[size]) {} 
   // ����������� �����
   Stack(const Stack<T> &);
  // ����������
   ~Stack() throw() {delete []a;}
   // �������� ������������
   Stack<T> &operator=(const Stack<T> &);
   // �������� ���������� � ����
   Stack<T> &operator<<(const T &);
   // �������� ���������� �� �����
   Stack<T> &operator>>(T &);
};