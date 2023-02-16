#define _USE_MATH_DEFINES









using namespace std;

struct Point
{
   int x, y;
};

struct Fill
{
   int x, y;
   int color;
};

struct act
{
   int num = 0;
   lineB lin;
   star sta;
   circl circ;
   Fill fil;
   lineBez linBz;
};

void pefog(int pef[100], int k, int n)
{
   if(n <= k) return;
   int a[100] = {0};
   for(int i = 0; i < k; i++) a[i] = pef[i];
   for(int i = 1; i < k+1; i++)
   {
      pef[i] = a[i-1]+a[i];
   }
   pefog(pef, k+1, n);
}

int main()
{
   setlocale(LC_ALL,"Russian");
   setlocale(LC_ALL,"rus");
   srand(time(0));
   initwindow(1200, 900);
   
   setlinestyle(SOLID_LINE, 0, 1);
   setbkcolor(WHITE);
   
   srand(time(0));
   
   IMAGE *imager;
   imager = loadBMP("Red.bmp");
   
   IMAGE *imageg;
   imageg = loadBMP("Green.bmp");
   
   IMAGE *imageb;
   imageb = loadBMP("Blue.bmp");
   
   int col[3][2] = {{255, 0}, {255, 0}, {255, 0}};
   int r = 0, wrt[2] = {0};
   int n = 5, p = 0, t = 0;
   int mode = 0;
   
   lineB but1 = lineB(20, 25, 50, 45, BLACK, 3);
   star but2 = star(85, 35, 24, 5, 0, BLACK);
   circl but3 = circl(135, 35, 21, BLACK);
   lineB but4[5];
   but4[0].setStart(160, 43);
   but4[0].setEnd(177, 60);
   but4[0].setColor(BLACK);
   but4[0].setWidth(2);
   but4[1].setStart(160, 27);
   but4[1].setEnd(193, 60);
   but4[1].setColor(BLACK);
   but4[1].setWidth(2);
   but4[2].setStart(160, 10);
   but4[2].setEnd(210, 60);
   but4[2].setColor(BLACK);
   but4[2].setWidth(2);
   but4[3].setStart(177, 10);
   but4[3].setEnd(210, 43);
   but4[3].setColor(BLACK);
   but4[3].setWidth(2);
   but4[4].setStart(193, 10);
   but4[4].setEnd(210, 26);
   but4[4].setColor(BLACK);
   but4[4].setWidth(2);
   lineBez but5 = lineBez(BLACK, 3);
   but5.add(220, 20);
   but5.add(250, 20);
   but5.add(220, 50);
   but5.add(250, 50);
   but5.setStep(0.02);
   
   lineB butsave[18] = {lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(545, 10, 550, 15, BLACK, 1),
                                  lineB(550, 15, 550, 50, BLACK, 1),
                                  lineB(550, 50, 510, 50, BLACK, 1),
                                  lineB(510, 50, 510, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1),
                                  lineB(510, 10, 545, 10, BLACK, 1)};
   
   act acts[1000];
   int countDo = 0;
   int start[2] = {0}, end[2] = {0};
   
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
      setfillstyle(SOLID_FILL, BLACK);
      bar(10, 70, 1190, 800);
      for(int i = 0; i < countDo; i++)
      {
         switch(acts[i].num)
         {
            case 1: acts[i].lin.draw(); break;
            case 2: acts[i].sta.draw(); break;
            case 3: acts[i].circ.draw(); break;
            case 4: fillIn(acts[i].fil.x, acts[i].fil.y, acts[i].fil.color, getpixel(acts[i].fil.x, acts[i].fil.y)); break;
            case 5: acts[i].linBz.draw(); break;
         }
      }
      
      setcolor(BLACK);
      rectangle(10, 10, 60, 60);
      but1.draw();
      
      setcolor(BLACK);
      rectangle(60, 10, 110, 60);
      but2.draw();
      
      setcolor(BLACK);
      rectangle(110, 10, 160, 60);
      but3.draw();

      setcolor(BLACK);
      rectangle(160, 10, 210, 60);
      for(int i = 0; i < 5; i++) but4[i].draw();
      
      setcolor(BLACK);
      rectangle(210, 10, 260, 60);
      but5.draw();
      
      for(int i = 0; i < 18; i++)
      {
         _abracadabra_cast(butsave);