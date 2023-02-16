







using namespace std;

//Интерфейс класса Example:

class Example{
   Example *left,*right; //левая и правая части примера
   int answer; //ответ на пример
   int prior;
   string res;
   char oper; //арифметическая операция
   public:
      Example(int answer); //конструктор  примера
      Example(Example *left,char oper,Example *right);//конструктор примера с левой и правой частью
      ~Example(){delete[] left; delete[] right;}; //деструктор
      string exampleString()const{return res;} //возвращает пример в виде строки
};

//Интерфейс класса Generator:

class Generator{
   int numExample; // количество примеров
   int numOperations; //число действий
   int rangeLeft,rangeRight; //левая и правая границы
   int checkBox[5]; //допустимые операции(значение элемента равно 1 если операция допустима)
   Example *rec(int numExample,int numfOperations); //вспомогательный рекурсивный метод для генерации объекта класса Sum
   public:
      Generator(int numExample, int numOperations, int rangeLeft, int rangeRight, int *checkBox); //конструктор
      void generateFile(string fileName); //сгенерировать в файл, имя которого передается   в метод в качестве аргумента
      void generateVector(vector<string> &h);
      Example* generateOneExample();//сгенерировать один пример
};

Example::Example(Example *left,char oper,Example *right):left(left),oper(oper),right(right)
{
   if (oper == '+')
   {
      prior = 1;
      answer = _abracadabra_cast(*(left));