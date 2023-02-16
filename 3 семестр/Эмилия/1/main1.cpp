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

    void add(int dt, Event obj);  // �������� ������� � ������ (������+dt)
    Event get();                  // �������� ������ �������
    void del();                   // ������� ������ �������
    bool isReady();               // ������� ����� ���������� �-� �������
    bool isEmpty();               // ������� �����
    bool isFull();                // ������� �����
    void print();  // ����������� ��������� �������
};

//����������� �������
TQueue::TQueue(int maxsize):
    SIZE(maxsize)//������������ ���������
   {
      queue = new Event[SIZE];
      head = tail = 0;
   }
   
//������� ����������� �������
TQueue::~TQueue()
   {
      delete [] queue;//������� �������
   }

//�������� ������� � ������ (������+dt)
void TQueue::add ( int dt, Event obj ) 
{ 
   if(!isFull()){
      queue[tail++]=dt+obj;
   }
} 

//�������� ������ �������
Event TQueue:: get(){
   return queue[head];
}

//������� ������ �������
void TQueue::del() { 
   if(!isEmpty()){
      head++;
   }
}

//������� ����� ���������� �-� �������
bool TQueue::isReady(){
   int now=time(0);
   for(int i=0;i<SIZE;i++){
      if(now>=queue[i]){
         return true;
      }
   }
   return false;
}

//������� �����
bool TQueue::isEmpty() 
{ 
    return (head == tail);
} 
 

//������� �����
bool TQueue::isFull(){
    return (tail == SIZE);
}

//������� ������� 
void TQueue:: print(){
   for(int i=0; i<SIZE; i++){
      cout<< queue[i] << "  ";
   }
}

int main(){
    TQueue EventQueue(7);//������������� ������ 7

    //�������� �������
    Event now_t = time(0);
    cout << "time now: " << now_t << endl;//������� �����, � ������� �������� ���������

    for (int i = 0; i < 100 && !EventQueue.isFull(); i++) {//��������� ������
        EventQueue.add(i * 2, now_t);//��������� �������
    }

    //������� ������� 
    cout << "queue : ";
    EventQueue.print();
    cout << endl;

    while (!EventQueue.isEmpty()) {//��������� ����� �� �������
        if (EventQueue.isReady()) {//���� ������� ���������
            cout << "event happened " << EventQueue.get() << endl;//������� ��� �������
            EventQueue.del();//������� ��� �������
        }
    }
   return 0;
}
