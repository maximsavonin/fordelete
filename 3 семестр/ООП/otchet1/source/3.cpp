PQueue a = PQueue(10);
Data b;
for(int i = 0; i < 10; i++)
{
   b.info = 'a'+i;
   b.prioritet = i;
   a.add(b);
}
b = a.first();
cout << b.info << ' ' << b.prioritet << endl; // a 0
a.print(); \* 10 10
		  a b c d e f g h i j
		  0 1 2 3 4 5 6 7 8 9*/
a.next();
a.print(); \* 9 10
		  b c d e f g h i j
		  1 2 3 4 5 6 7 8 9*/
cout << a.isFull() << ' ' << a.isEmpty(); // 0 0