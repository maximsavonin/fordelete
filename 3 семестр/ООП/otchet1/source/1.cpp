struct Data 
{ 
   long prioritet;
   string info;
};
class PQueue
{
   public:
      PQueue(int maxsize=100);
      ~PQueue(){ delete[] data;}
      void add(const Data &dat); //добавить данные
      const Data& first();  //получить данные с наименьшим приоритетом
      void next(); //убрать данные с наименьшим приоритетом
      bool isEmpty(); //очередь пуста
      bool isFull(); //очередь полна
      void print(); //распечатать состояние объекта
};