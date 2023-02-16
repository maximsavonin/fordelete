

using namespace std;

struct stackerror { // базовый класс для ошибок
   virtual ~stackerror() {} // деструктор
   virtual const char *what() const=0; // сообщение для печати
};

struct stackempty: stackerror {
   const char *what() const {return "Стек пуст";} // сообщение для печати
};

struct stackfull: stackerror {
   const char *what() const {return "Стек полон";} // сообщение для печати
};

struct stacksmall: stackerror {
   const char *what() const {return "Стек слишком мал для копирования";} // сообщение для печати
};

template <typename T>
class Stack {
   T *a; // указатель на данные в стеке
   int col, // текущее количество
         size; // максимальный размер
public:
   // конструктор
   Stack(int size): col(0), size(size),a(new T[size]) {} 
   // конструктор копий
   Stack(const Stack<T> &);
  // деструктор
   ~Stack() throw() {delete []a;}
   // операция присваивания
   Stack<T> &operator=(const Stack<T> &);
   // операция добавления в стек
   Stack<T> &operator<<(const T &);
   // операция извлечения из стека
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