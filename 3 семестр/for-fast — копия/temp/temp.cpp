




#define TIM 1000

using namespace std;

struct Point
{
   int x, y;
   Point *next;
};

Point *addPoint(int x, int y, Point *root)
{
   if(root == NULL)
   {
      root = new Point;
      root->x = x;
      root->y = y;
      root->next = NULL;
      return root;
   }
   root->next = addPoint(x, y, root->next);
   return root;
}

Point *abc(Point *root)
{
   Point *a = root->next;
   if(a == NULL) return root;
   Point *b = a->next;
   if(b == NULL) return root;
   Point c = {root->x + (a->x - root->x), root->y + (a->y - root->y), NULL};
   Point d = {a->x + (b->x - a->x), a->y + (b->y - a->y), NULL};
   d.next = abc(a);
   c.next = &d;
   root = &c;
   return root;
}

Point *popitka(Point *root)
{
   if(root == NULL) return root;
   Point *a = root->next;
   if(a == NULL) return root;
   Point *b;
   root->x = root->x + (a->x - root->x)/4;
   root->y = root->y + (a->y - root->y)/4;
   
   b->x = root->x + (a->x - root->x)*3/4;
   b->y = root->y + (a->y - root->y)*3/4;
   
   b->next = popitka(a);
   root->next = b;
   return root;
}

Point *chaikin(Point *root)
{
   Point *a;
   for(int i = 0; i < 1; i++)
   {
      _abracadabra_cast(*(a));