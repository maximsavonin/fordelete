

using namespace std;

struct seterror { // базовый класс для ошибок
   virtual ~seterror() {} // деструктор
   virtual const char *what() const=0; // сообщение для печати
};

struct setempty: seterror {
   const char *what() const {return "Множество пуст";} // сообщение для печати
};

struct setfull: seterror {
   const char *what() const {return "Множество переполнено";} // сообщение для печати
};

struct setsmall: seterror {
   const char *what() const {return "Множество слишком мало для копирования";} // сообщение для печати
};

struct setdiferent: seterror {
   const char *what() const {return "Множества разных размеров";} // сообщение для печати
};

struct sethave: seterror {
   const char *what() const {return "Элемент уже есть в множестве";} // сообщение для печати
};

struct sethavent: seterror {
   const char *what() const {return "Элемента нет в множестве";} // сообщение для печати
};

template <typename T>
class Set {
   T *a; // указатель на данные в множестве
   int col, // текущее количество
         size; // максимальный размер
public:
   Set(int size): col(0), size(size),a(new T[size]) {} // конструктор
   Set(const Set<T> &);// конструктор копий
   ~Set() throw() {delete []a;}// деструктор
   Set<T> &operator=(const Set<T> &); // операция присваивания
   Set<T> &operator+=(const T &); // операция добавления в стек
   Set<T> &operator-=(T &); // операция извлечения из стека
   bool operator==(const Set<T> &); // операция сравнения множеств
   bool operator==(const T &); // операция сравнения множеств
   Set<T> &operator-(const Set<T> &); // операция разность множеств
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