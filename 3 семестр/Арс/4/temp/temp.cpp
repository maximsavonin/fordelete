

using namespace std;

struct seqerror { // базовый класс для ошибок
   virtual ~seqerror() {} // деструктор
   virtual const char *what() const=0; // сообщение для печати
};

struct seqempty: seqerror {
   const char *what() const {return "Последовательность пуста";} // сообщение для печати
};

struct seqhavent: seqerror {
   const char *what() const {return "В последовательности нет ячейки под этим индексом";} // сообщение для печати
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
Array<T>:: Array(const Array <T> &array): a(new T[1+array.end-array.first]), first(array.first), end(_abracadabra_cast(array);