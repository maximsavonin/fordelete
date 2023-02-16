#include <iostream>

using namespace std;

struct maperror { // ������� ����� ��� ������
   virtual ~maperror() {} // ����������
   virtual const char *what() const=0; // ��������� ��� ������
};

struct mapempty: maperror {
   const char *what() const {return "������ ����";} // ��������� ��� ������
};

struct mapnotfound: maperror {
   const char *what() const {return "������� �� ������";} // ��������� ��� ������
};

struct maphave: maperror {
   const char *what() const {return "���� ��� ������������";} // ��������� ��� ������
};

template <typename K, typename V>
class Map {
   K *key; // ��������� �� ����� � �������
   V *value; // ��������� �� �������� � �������
   int col; // ������� ����������
public:
   Map(): col(0), key(new K[0]), value(new V[0]) {} // �����������
   Map(const Map<K, V> &);// ����������� �����
   ~Map() throw() {delete []key; delete []value;}// ����������
   Map<K, V> &operator=(const Map<K, V> &);// �������� ������������
   V &operator[](K); // ����� �� �����
   V operator[](K) const; // ����� �� �����
   Map<K, V> &del(K); // �������� �� �����
   Map<K, V> &add(K, V); // ���������� �� �����
   bool operator==(Map<K, V>&);  // ��������� ��������
};

template <typename K, typename V>
Map<K, V>::Map(const Map <K, V> &m): key(new K[m.col]), value(new V[m.col]), col(m.col) {
   for (int i=0; i<col; i++)
   {
      key[i] = m.key[i];
      value[i] = m.value[i];
   }
}

template <typename K, typename V>
Map<K, V> &Map<K, V>::operator=(const Map<K, V> &m)
{
   delete []key;
   delete []value;
   col = m.col;
   key = new K[col];
   value = new V[col];
   for (int i=0; i<col; i++)
   {
      key[i] = m.key[i];
      value[i] = m.value[i];
   }
   return *this;
}

template <typename K, typename V>
V &Map<K, V>::operator[](K k)
{
   for(int i = 0; i < col; i++)
   {
      if(key[i] == k) return value[i];
   }
   throw mapnotfound();
}

template <typename K, typename V>
V Map<K, V>::operator[](K k) const
{
   for(int i = 0; i < col; i++)
   {
      if(key[i] == k) return value[i];
   }
   throw mapnotfound();
}

template <typename K, typename V>
Map<K, V> &Map<K, V>::del(K k)
{
   if(col == 0) throw mapempty();
   for(int i = 0; i < col; i++)
   {
      if(key[i] == k)
      {
         for(int j = i; j < col-1; j++)
         {
            key[j] = key[j+1];
            value[j] = value[j+1];
         }
         col--;
         return *this;
      }
   }
   throw mapnotfound();
}

template <typename K, typename V>
Map<K, V> &Map<K, V>::add(K k, V v)
{
   K *keycop = new K[col];
   V *valuecop = new V[col];
   for(int i = 0; i < col; i++)
   {
      keycop[i] = key[i];
      valuecop[i] = value[i];
      if(key[i] == k) throw maphave();
   }
   delete []key;
   delete []value;
   key = new K[col+1];
   value = new V[col+1];
   for(int i = 0; i < col; i++)
   {
      key[i] = keycop[i];
      value[i] = valuecop[i];
   }
   key[col] = k;
   value[col] = v;
   col++;
   delete []keycop;
   delete []valuecop;
   return *this;
}

template <typename K, typename V>
bool Map<K, V>::operator==(Map<K, V>& m)
{
   if(m.col != col) return false;
   try {
      for(int i = 0; i < col; i++)
      {
         if(m[key[i]] != value[i]) return false;
      }
   }
   catch (maperror &e) {
      return false;
   }
   return true;
}

int main()
{
   Map<char, int> obj;
   cout<<"���� 1. ����������\n";
   try {
      for (char i = 'a'; i < 'a'+10; i++) {
         obj.add(i, int(i-'a'));
      }
      obj.add('a', int('a'));
   }
   catch (maperror &e) {
      cout<<e.what();
   }
   
   Map<char, int> obj2;
   cout<<"\n���� 2. ����� �� �����\n";
   try {
      for (char i = 'a'; i < 'a'+11; i++) {
         cout << obj[i];
         obj2.add(i, obj[i]);
      }
   }
   catch (maperror &e) {
      cout<<e.what();
   }
   
   cout<<"\n���� 3. ��������� ��������\n";
   try {
      cout << (obj == obj2) << endl;
      obj2['a'] = 10;
      cout << (obj == obj2) << endl;
      obj2['a'] = 0;
      obj2.add('k', 10);
      cout << (obj == obj2) << endl;
      obj2.del('k');
      obj2.del('a');
      cout << (obj == obj2) << endl;
   }
   catch (maperror &e) {
      cout<<e.what();
   }
   
   cout<<"\n���� 4. �������� �� �����\n";
   try {
      for (char i = 'a'; i < 'a'+11; i++) {
         obj.del(i);
      }
   }
   catch (maperror &e) {
      cout<<e.what();
   }
   
   return 0;
}
