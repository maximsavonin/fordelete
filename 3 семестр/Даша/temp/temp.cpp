







using namespace std;

//��������� ������ Example:

class Example{
   Example *left,*right; //����� � ������ ����� �������
   int answer; //����� �� ������
   int prior;
   string res;
   char oper; //�������������� ��������
   public:
      Example(int answer); //�����������  �������
      Example(Example *left,char oper,Example *right);//����������� ������� � ����� � ������ ������
      ~Example(){delete[] left; delete[] right;}; //����������
      string exampleString()const{return res;} //���������� ������ � ���� ������
};

//��������� ������ Generator:

class Generator{
   int numExample; // ���������� ��������
   int numOperations; //����� ��������
   int rangeLeft,rangeRight; //����� � ������ �������
   int checkBox[5]; //���������� ��������(�������� �������� ����� 1 ���� �������� ���������)
   Example *rec(int numExample,int numfOperations); //��������������� ����������� ����� ��� ��������� ������� ������ Sum
   public:
      Generator(int numExample, int numOperations, int rangeLeft, int rangeRight, int *checkBox); //�����������
      void generateFile(string fileName); //������������� � ����, ��� �������� ����������   � ����� � �������� ���������
      void generateVector(vector<string> &h);
      Example* generateOneExample();//������������� ���� ������
};

Example::Example(Example *left,char oper,Example *right):left(left),oper(oper),right(right)
{
   if (oper == '+')
   {
      prior = 1;
      answer = _abracadabra_cast(*(left));