








using namespace std;

struct Circl
{
   int x, y, r, thickness;
};

struct Pole
{
   int x, y, value;
};

struct Button
{
   int x, y;
   IMAGE *image;
};

int main()
{
   setlocale(LC_ALL,"Russian");
   setlocale(LC_ALL,"rus");
   srand(time(0));
   initwindow(850, 700);
   
   setlinestyle(SOLID_LINE, 0, 1);
   setbkcolor(WHITE);
   
   srand(time(0));
   
   IMAGE *imager;
   imager = loadBMP("Red.bmp");
   
   IMAGE *imageg;
   imageg = loadBMP("Green.bmp");
   
   IMAGE *imageb;
   imageb = loadBMP("Blue.bmp");
   
   int col[3][2] = {{200, 0}, {200, 0}, {200, 0}};
   int numCircle = 0, wrt[4] = {0};
   int fil = 0, p = 0, t = 0;
   int fillPoint[1000][3] = {0};
   int numFill = 0;
   
   Circl data[100];
   Pole r = {40, 660, 100};
   Pole thickness = {190, 660, 1};
   
   IMAGE *image;
   image = loadBMP("fill.bmp");
   Button BFill = {640, 660, image};
   image = loadBMP("circle.bmp");
   Button BCircle = {640, 660, image};
   image = loadBMP("clear.bmp");
   Button BClear = {690, 660, image};
   image = loadBMP("save.bmp");
   Button BSave = {740, 660, image};
   image = loadBMP("exit.bmp");
   Button BExit = {790, 660, image};
   
   while(1)
   {
      if(1-fil)
      {
         p = 1-p;
         setactivepage(p);
         
         setfillstyle(SOLID_FILL, BLACK);
         setcolor(WHITE);
         rectangle(-1, -1, 851, 701);
         bar(0, 0, 850, 700);
         
         if(mousebuttons() and mousey()+r.value < 650)
         {
            data[numCircle] = {mousex(), mousey(), r.value, thickness.value};
            numCircle++;
            while(mousebuttons());
         }
         
         if(mousebuttons() && abs(r.x+75-mousex()) < 75 && abs(r.y+13-mousey()) < 13) 
         {
            for(int i = 0; i < 2; i++) wrt[i] = 0;
            wrt[0] = 1;
         }
         if(mousebuttons() && abs(thickness.x+75-mousex()) < 75 && abs(thickness.y+13-mousey()) < 13) 
         {
            for(int i = 0; i < 2; i++) wrt[i] = 0;
            wrt[1] = 1;
         }
         
         setfillstyle(SOLID_FILL, COLOR(100, 100, 100));
         bar(0, 650, 850, 700);
         
         circleBre(360, 675, 20, 1);
         setfillstyle(SOLID_FILL, COLOR(255, 0, 0));
         floodfill(360, 675, WHITE);
         circleBre(400, 675, 20, 1);
         setfillstyle(SOLID_FILL, COLOR(255, 255, 0));
         floodfill(400, 675, WHITE);
         circleBre(440, 675, 20, 1);
         setfillstyle(SOLID_FILL, COLOR(0, 255, 0));
         floodfill(440, 675, WHITE);
         circleBre(480, 675, 20, 1);
         setfillstyle(SOLID_FILL, COLOR(0, 255, 255));
         floodfill(480, 675, WHITE);
         circleBre(520, 675, 20, 1);
         setfillstyle(SOLID_FILL, COLOR(0, 0, 255));
         floodfill(520, 675, WHITE);
         circleBre(560, 675, 20, 1);
         setfillstyle(SOLID_FILL, COLOR(255, 0, 255));
         floodfill(560, 675, WHITE);
         circleBre(600, 675, 20, 1);
         setfillstyle(SOLID_FILL, COLOR(255, 255, 255));
         floodfill(600, 675, WHITE);
         
         r.value = pole(r.x, r.y, 130, 25, "Радиус: ", r.value, wrt[0], t);
         thickness.value = pole(thickness.x, thickness.y, 130, 25, "Толщина: ", thickness.value, wrt[1], t);
         
         setcolor(WHITE);
         for(int i = 0; i < numCircle; i++) circleBre(data[i].x, data[i].y, data[i].r, data[i].thickness);
         
         if(button(BClear)) 
         {
            numFill = 0;
            numCircle = 0;
            while(mousebuttons());
         }
         if(button(BSave)) 
         {
            save();
            while(mousebuttons());
         }
         if(button(BFill))
         {
            fil = 1;
            while(mousebuttons());
         }
         if(button(BExit)) return 0;
         
         t = t+1;
         t = t%8;
         
         setvisualpage(p);
         delay(10);
      }
      else
      {
         p = 1-p;
         setactivepage(p);
         
         setfillstyle(SOLID_FILL, BLACK);
         setcolor(WHITE);
         rectangle(-1, -1, 851, 701);
         bar(0, 0, 850, 700);
         
         if(mousebuttons() and mousey() < 650)
         {
            fillPoint[numFill][0] = mousex();
            fillPoint[numFill][1] = mousey();
            fillPoint[numFill][2] = COLOR(col[0][0], col[1][0], col[2][0]);
            numFill++;
         }
         
         setcolor(WHITE);
         for(int i = 0; i < numCircle; i++) circleBre(data[i].x, data[i].y, data[i].r, _abracadabra_cast(data[i]);