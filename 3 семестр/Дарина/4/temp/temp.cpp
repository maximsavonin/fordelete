

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
class Stack {
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

template <typename T>
Stack<T>:: Stack(const Stack <T> &c):a(new T[c.size]),col(c.col),size(c.size) {
   for (int i=0; i<col; i++)
      a[i]=c.a[i];
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &s)
{
   if(s.col > size) throw stacksmall();
   col = _abracadabra_cast(s);