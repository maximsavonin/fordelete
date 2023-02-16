#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>

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
      Example(Example * left,char oper,Example * right);//����������� ������� � ����� � ������ ������
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
      friend void generateFile(string fileName); //������������� � ����, ��� �������� ����������   � ����� � �������� ���������
      friend void generateVector(vector<string> &);
      Example* generateOneExample();//������������� ���� ������
};

Example::Example(Example *left,char oper,Example *right):left(left),oper(oper),right(right)
{
   if (oper == '+')
   {
      prior = 1;
      answer = left->answer+right->answer;
   }
   if (oper == '-')
   {
      prior = 2;
      answer = left->answer-right->answer;
   }
   if (oper == '*')
   {
      prior = 3;
      answer = left->answer*right->answer;
   }
   if (oper == ':')
   {
      prior = 4;
      answer = left->answer/right->answer;
   }
   if (oper == '(')
   {
      prior = 0;
      res = "-";
      if (answer < 0) res += "(";
      res += right->res;
      if (answer < 0) res += ")";
      answer =- right->answer;
      return;
   }
   if (prior > left->prior && left->prior)
   {
      res += '(';
      res += left->res;
      res += ')';
   }
   else res += left->res;
   res += ' ';
   res += oper;
   res += ' ';
   if (prior > right->prior || right->prior == 2 || right->prior == 4)
   {
      res += '(';
      res += right->res;
      res += ')';
   }
   else res += right->res;
}

Generator::Generator(int numExample,int numOperations,int rangeLeft,int rangeRight,int *checkBox)
{
   this->numExample=numExample;
   this->numOperations=numOperations;
   this->rangeLeft=rangeLeft;
   this->rangeRight=rangeRight;
   for(int i = 0;i < 5;i++) 
      this->checkBox[i]=checkBox[i];
   srand(time(0));
}
void Generator::generateFile(string fileName)
{
   Example *AS;
   ofstream to(fileName.c_str());
   for(int i =0 ;i < numExample;i++)
   {
      AS = this->generateOneExample();
      to<<AS->exampleString()<<" = \n\n"<<"�����: "<<AS->answer<<"\n\n";
      delete AS;
   }
}
void Generator::generateVector(vector<string> &h)
{
   string res;
   Example*AS;
   for(int i=0;i<numExample;i++)
   {
      AS = this->generateOneExample();
      res = AS->exampleString();
      res += " = ";
      ostringstream out;
      out << AS->answer;
      res += out.str();
      h.push_back(res);
      delete AS;
   }
}
Example* Generator::rec(int num,int numberOperations)
{
   int operandLeft,operandRight;
   int N,M,random,cnt(0);
   char operation;
   string operations = "+-*:(";
   ostringstream out;
   if (numberOperations == 0)
   return new Example(num);
   while (1)
   {
      cnt++;
      if (cnt >= 10000)
      random=rand()%5;
      if (!checkBox[random]) continue;
      operation = operations[random];
      operandLeft = rand()%(rangeRight-rangeLeft+1)+rangeLeft;
      if (operation ==  '+')
         operandRight = num-operandLeft;
      if (operation =='-')
         operandRight = operandLeft-num;
      if (operation == '*')
      {
         if (operandLeft == 0) continue;
         if (num%operandLeft) continue;
         operandRight = num/operandLeft;
      }
      if (operation == ':')
      {
         if (num == 0) continue;
         if (operandLeft%num) continue;
         operandRight = operandLeft/num;
         if (operandRight == 0) continue;
      }
      if (operation == '(')
      {
         if (-num > rangeRight || -num < rangeLeft || num == 0) continue;
         return new Example(new Example(0),operation,rec(-num,numberOperations-1));
      }
      if (operandRight >rangeRight || operandRight < rangeLeft) continue;
      
      break;
   }
   N=rand()%numberOperations;
   M=numberOperations-N-1;
   return new Example(rec(operandLeft,N),operation,rec(operandRight,M));
}
Example* Generator::generateOneExample()
{
   int num=rand()%(rangeRight-rangeLeft+1)+rangeLeft;
   return rec(num,numOperations);
}
