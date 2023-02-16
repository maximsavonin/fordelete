

using namespace std;

struct seqerror { // ������� ����� ��� ������
   virtual ~seqerror() {} // ����������
   virtual const char *what() const=0; // ��������� ��� ������
};

struct seqempty: seqerror {
   const char *what() const {return "������������������ �����";} // ��������� ��� ������
};

struct seqhavent: seqerror {
   const char *what() const {return "� ������������������ ��� ������ ��� ���� ��������";} // ��������� ��� ������
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
Array<T>:: Array(const Array <T> &array): a(new T[1+array.end-array.first]), first(array.first), end(_abracadabra_cast(array);