#include <iostream>
#include <time.h>

using namespace std;

typedef long long Event;
class TQueue
{
private:
   Event *queue;
   const int SIZE;
   int head;
   int tail;
public:
    TQueue(int maxsize=100);
    ~TQueue();

    void add(int dt, Event obj);  // добавить событие в момент (сейчас+dt)
    Event get();                  // получить первое событие
    void del();                   // удалить первое событие
    bool isReady();               // подошло время обработать к-л события
    bool isEmpty();               // очередь пуста
    bool isFull();                // очередь полна
    void print();  // распечатать состояние объекта
};

//конструктор очереди
TQueue::TQueue(int maxsize):
    SIZE(maxsize)//иницализация константы
   {
      queue = new Event[SIZE];
      head = tail = 0;
   }
   
//функция деструктора очереди
TQueue::~TQueue()
   {
      delete [] queue;//удаляем очередь
   }

//добавить событие в момент (сейчас+dt)
void TQueue::add ( int dt, Event obj ) 
{ 
   if(!isFull()){
      queue[tail++]=dt+obj;
   }
} 

//получить первое событие
Event TQueue:: get(){
   return queue[head];
}

//удалить первое событие
void TQueue::del() { 
   if(!isEmpty()){
      head++;
   }
}

//подошло время обработать к-л события
bool TQueue::isReady(){
   int now=time(0);
   for(int i=0;i<SIZE;i++){
      if(now>=queue[i]){
         return true;
      }
   }
   return false;
}

//очередь пуста
bool TQueue::isEmpty() 
{ 
    return (head == tail);
} 
 

//очередь полна
bool TQueue::isFull(){
    return (tail == SIZE);
}

//вывести очередь 
void TQueue:: print(){
   for(int i=0; i<SIZE; i++){
      cout<< queue[i] << "  ";
   }
}

int main(){
    TQueue EventQueue(7);//устанавливаем размер 7

    //заполним очередь
    Event now_t = time(0);
    cout << "time now: " << now_t << endl;//выведем время, в которое началась программа

    for (int i = 0; i < 100 && !EventQueue.isFull(); i++) {//проверяем размер
        EventQueue.add(i * 2, now_t);//заполняем очередь
    }

    //выведем очередь 
    cout << "queue : ";
    EventQueue.print();
    cout << endl;

    while (!EventQueue.isEmpty()) {//проверяем пуста ли очередь
        if (EventQueue.isReady()) {//если событие произошло
            cout << "event happened " << EventQueue.get() << endl;//выводим это событие
            EventQueue.del();//удаляем это событие
        }
    }
   return 0;
}
