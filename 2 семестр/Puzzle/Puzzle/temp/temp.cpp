


typedef struct Button { // ������
   int x, y, x1, y1,// ����������
       w, h, w1, h1;// �������
   IMAGE *bmp;  // ��������
} Button;

typedef struct Puzzle {
   int x, y, index, now;
   IMAGE *img;
} Puzzle;

// ���������� ���������
#define NMENU 3
#define MENU_W 200
#define MENU_H 56
#define IMG_COUNT 5

enum _special_keys { KEY_SPECIAL=0x100, MOUSE_CLICK=0x200};

//  ���������� ����������
Button mn[NMENU]; // ������ ����
Button img[IMG_COUNT]; // ������ � ����������
IMAGE *Picture;
IMAGE *Pazl[16];
IMAGE *fon; // ��� ��� ����
int map[4][4];
int inmouse = 0; //����� �������� �� �����
Puzzle all[16];

// ��������� �������
int menu();
void init();
void menu2();
void init2();
void draw_menu();
void get_variant();
int get_image();
void draw_variant();
void about_program();
void start_game();
void GameInit();
void DrawMap();

int main() {
   int st;
   init();
   do {
      st = menu();
      switch (st) {
      case 1:
         menu2();
         break;
      case 2:
         about_program();
         break;
      }
   } while (st != 3);
   closegraph();
   return 0;
}
//----------------------------------------------------------------
Button new_button(int x, int y, const char *t) {
   Button b;
   b.x=x;
   b.y=y;
   b.w=MENU_W;
   b.h=MENU_H;
   b.w1 = 285,
   b.h1 = 178,
   b.bmp=loadBMP(t);
   return b;
}
//������ �������� ����
void init() {
   initwindow(1200, 600);
   fon=loadBMP("main.jpg");
   int top = 150;
   int left = (getmaxx() - MENU_W)/2;
   int skip = MENU_H + 50;
   mn[0]=new_button(left,top,"Start game.bmp");
   top+=skip;
   mn[1]=new_button(left,top,"Program.bmp");
   top+=skip;
   mn[2]=new_button(left,top,"Exit.bmp");
}
//��������� ������ �������� ����
void draw_menu() {
   clearviewport();
   putimage(0,0,fon,COPY_PUT);
   for (int i=0; i < NMENU; i++)
   {
      // ������ ������
      putimage(mn[i].x, mn[i].y, mn[i].bmp, COPY_PUT);
   }
}
//------------------------------------------------------
int wait_click() {  
   while (1) 
   {
      if (kbhit()) {
         int k=getch();
         if (k==0) k=getch()+KEY_SPECIAL;
         return k;
      }
      int b=mousebuttons();
      if (b)
      {
         while (mousebuttons()); // ���� ���������� ������
         return MOUSE_CLICK+b;
      }
   }
}
// ������� ����
int menu() {
   while (1) {
      draw_menu();
      int k=wait_click();
      if (k&MOUSE_CLICK)
      {
         int x = mousex();
         int y = mousey();
         for (int i=0; i < NMENU; i++)
            if (x >= mn[i].x && y>=mn[i].y
                  && x <= mn[i].x+mn[i].w && y<=mn[i].y+mn[i].h)
               return i+1;
      }
      if (k==KEY_ESC) return NMENU;
   }
}
//������ � ����������
void init2() {
   fon=loadBMP("main.jpg");
   int top1 = 100;
   int top2 = 370;
   int left1 = 183;
   int left2 = 733;
   img[0]=new_button(left1,top1,"11.bmp");
   img[1]=new_button(left2,top1,"22.bmp");
   img[2]=new_button(left1,top2,"33.bmp");
   img[3]=new_button(left2,top2,"44.bmp");
   img[4]=new_button(60,30,"Back.bmp");
}
//��������� ������ � ����������
void draw_variant() {
   clearviewport();
   putimage(0,0,fon,COPY_PUT);
   for (int i=0; i < IMG_COUNT; i++)
   {
      // ������ ������
      putimage(img[i].x, img[i].y, img[i].bmp, COPY_PUT);
   }
}
//-----------------------------------------------------------------
int get_image() {
   while (1) {
      draw_variant();
      int k=wait_click();
      if (k & MOUSE_CLICK)
      {
         int x = mousex();
         int y = mousey();
         for (int i=0; i < IMG_COUNT; i++)
            if (x >= img[i].x && y >= img[i].y
                  && x <= img[i].x+img[i].w1 && y <= img[i].y+img[i].h1)
               return i+1;
      }
      if (k==KEY_ESC) return IMG_COUNT;
   }
}
//����� ��������
void menu2() {
   clearviewport();
   init2();
   int choose;
   do {
      choose = get_image();
      switch (choose) {
      case 1:
         clearviewport();
         Picture = loadBMP("111.jpg");
         putimage(0, 100, Picture, COPY_PUT);
         start_game();
         break;
      case 2:
         clearviewport();
         Picture = loadBMP("222.jpg");
         putimage(0, 100, Picture, COPY_PUT);
         start_game();
         break;
      case 3:
         clearviewport();
         Picture = loadBMP("333.jpg");
         putimage(0, 100, Picture, COPY_PUT);
         start_game();
         break;
      case 4:
         clearviewport();
         Picture = loadBMP("444.jpg");
         putimage(0, 100, Picture, COPY_PUT);
         start_game();
         break;
      }
   } while (choose != 5);
}
//� ���������
void about_program() {
   clearviewport();
   putimage(0,0,fon,COPY_PUT);
   IMAGE *p=loadBMP("About program.jpg");
   putimage(382, 202, p, COPY_PUT);
   wait_click();
   freeimage(p);
}
//���������� ��������
void GameInit() {
   int N = 4;
   for (int y = 0; y < N; y++)
   {
      for (int x = 0; x < N; x++)
      {
         int i = y*4+x;
         all[i].img = createimage(127, 100);
         getimage(x *124, 100 + y * 100, (x + 1) * 124, 100 + (y + 1) * 100, all[i].img);
         all[i].index = i;
         all[i].now = -1;
      }
   }
   for(int i = 0; i < 20; i++)
   {
      int j = rand()%16, k = rand()%16;
      Puzzle swap;
      swap = all[j];
      all[j] = all[k];
      all[k] = swap;
   }
   for (int y = 0; y < N; y++)
   {
      for (int x = 0; x < N; x++)
      {
         int i = y*4+x;
         all[i].x = 600+x*144;
         all[i].y = 60+y*120;
      }
   }
   /*
   int k=0;
   int N = 4;
   for (int y = 0; y < N; y++)
   {
      for (int x = 0; x < N; x++)
      {
         printf("k=%d", k);
         Pazl[k] = createimage(127, 100);
         getimage(x *124, 100 + y * 100, (x + 1) * 124, 100 + (y + 1) * 100, Pazl[k]);
         //putimage(600 + j + x * 124, 50 + i + y * 100, Pazl[k], COPY_PUT);
         k++;
      }
   }
   int index;
   int size = 16; // ���������� ��������� � �������
   int a[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         index = rand() % size; // �������� �������� ���� �� 16 �����
         map[i][j] = a[index]; // �������� �������� ��������� ����� �� ����� ���� �� ������
         for (int p = index; p < size; p++)
         {
            a[p] = a[p + 1]; // ���������� ����� �� ���� ������� ������ ����������� �������
         }
         size--; // ��������� ������ �������, ��������� ����� ����������� ����� ����
      }
   }*/
}
//
void DrawMap() {
   setbkcolor(WHITE);
   clearviewport();
   for(int i = 0; i < 16; i++)
   {
      putimage(all[i].x, all[i].y, all[i].img, COPY_PUT);
   }
   setcolor(BLACK);
   rectangle(49, 99, 547, 501);
   /*int i = 0, j = 0;
   for (int y = 0; y < 4; y++)
   {
      for (int x = 0; x < 4; x++)
      {
         putimage(620 + j + x * 124, 80 + i + y * 100, Pazl[map[x][y]], COPY_PUT);
         j += 20;
      }
      j = 0;
      i += 20;
   }*/
}

void toch() {
   int x = mousex();
   int y = mousey();
   if(mousebuttons())
   {
      if(inmouse != -1)
      {
         all[inmouse].x = x-62;
         all[inmouse].y = y-50;
      }
      else
      {
         for(int i = 0; i < 16; i++)
         {
            if(x >= all[i].x && x <= all[i].x + 124 && y >= _abracadabra_cast(all[i]);