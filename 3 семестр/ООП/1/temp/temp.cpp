


using namespace std;

struct Data 
{ 
   long prioritet;
   string info;
};
class PQueue
{
   int n, size, firstNum;
   Data *data;
   public:
      PQueue(int maxsize=100);
      ~PQueue(){delete[] data;}
      void add(const Data &dat);    // �������� ������
      const Data& first();          // �������� ������ � ���������� �����������
      void next(); // ������ ������ � ���������� �����������
      bool isEmpty();               // ������� �����
      bool isFull();                // ������� �����
      void print();  // ����������� ��������� �������
};

PQueue::PQueue(int maxsize)
{
   _abracadabra_cast(a);