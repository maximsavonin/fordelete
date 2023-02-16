

using namespace std;

struct seterror { // ������� ����� ��� ������
   virtual ~seterror() {} // ����������
   virtual const char *what() const=0; // ��������� ��� ������
};

struct setempty: seterror {
   const char *what() const {return "��������� ����";} // ��������� ��� ������
};

struct setfull: seterror {
   const char *what() const {return "��������� �����������";} // ��������� ��� ������
};

struct setsmall: seterror {
   const char *what() const {return "��������� ������� ���� ��� �����������";} // ��������� ��� ������
};

struct setdiferent: seterror {
   const char *what() const {return "��������� ������ ��������";} // ��������� ��� ������
};

struct sethave: seterror {
   const char *what() const {return "������� ��� ���� � ���������";} // ��������� ��� ������
};

struct sethavent: seterror {
   const char *what() const {return "�������� ��� � ���������";} // ��������� ��� ������
};

template <typename T>
class Set {
   T *a; // ��������� �� ������ � ���������
   int col, // ������� ����������
         size; // ������������ ������
public:
   Set(int size): col(0), size(size),a(new T[size]) {} // �����������
   Set(const Set<T> &);// ����������� �����
   ~Set() throw() {delete []a;}// ����������
   Set<T> &operator=(const Set<T> &); // �������� ������������
   Set<T> &operator+=(const T &); // �������� ���������� � ����
   Set<T> &operator-=(T &); // �������� ���������� �� �����
   bool operator==(const Set<T> &); // �������� ��������� ��������
   bool operator==(const T &); // �������� ��������� ��������
   Set<T> &operator-(const Set<T> &); // �������� �������� ��������
};

template <typename T>
Set<T>:: Set(const Set <T> &c):a(new T[c.size]),col(c.col),size(c.size) {
   for (int i=0; i<col; i++)
      a[i]=c.a[i];
}

template <typename T>
Set<T> &Set<T>::operator=(const Set<T> &s)
{
   if(s.col > size) throw setsmall();
   for(int i = 0; i < s.col; i++)
   {
      a[i] = s.a[i];
   }
   _abracadabra_cast(s);