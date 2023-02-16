






int points[100]; // массив точек карты и их связей
int player[2]; // место нахождение каждого игрока
int num = 0, p = 0; // число выпавшее на кости и номер отображаемой страницы
int play = 0, button = 0; // играем или в меню и на какую кнопку навёлся игрок
int nplayer = 0;

typedef struct Button{
   int x, y;
   char str[20];
}

Button buts[3];

void startgame(){
   player[0] = -1;
   player[1] = -1;
}

void draw(IMAGE *pic){ // отрисовка игры
   p = 1-p;
   setactivepage(p);
   clearviewport();
   int pol[8];
   setusercharsize(4, 10, 1, 2);
   putimage(150, 0, pic, COPY_PUT);
   for(int i = 1; i >= 0; i--){
      if(player[i] == -1){
         pol[0] = 125;
         pol[1] = 690-i*15;
      }
      else{
         if(player[i] % 20 > 9){
            pol[0] = 825-player[i]%10*70;
            pol[1] = 690-i*15-player[i]/10*70;
         }
         else{
            pol[0] = 195+player[i]%10*70;
            pol[1] = 690-i*15-player[i]/10*70;
         }
      }
      pol[2] = pol[0]-20;
      pol[3] = pol[1];
      pol[4] = pol[0]-10;
      pol[5] = pol[1]-20;
      pol[6] = pol[0];
      pol[7] = pol[1];
      
      if(i == 0) setfillstyle(SOLID_FILL, RED);
      else setfillstyle(SOLID_FILL, BLUE);
      fillpoly(4, pol);
   }
   rectangle(20, 400, 130, 450);
   if(abs(mousex()-75) <= 55 && abs(mousey()-425) <= 25){
      setfillstyle(SOLID_FILL, WHITE);
      bar(21, 401, 129, 449);
   }
   outtextxy(26, 415, "Бросить кость");
   char text[1];
   sprintf(text, "%d", num);
   outtextxy(70, 350, text);
   
   setvisualpage(p);
}

void rand_num(IMAGE *pic){ // бросание кости, ход игрока и компьютера и отрисовка всего этого
   if(abs(mousex()-75) <= 55 && abs(mousey()-425) <= 25 && mousebuttons() == 1){
      for(int i = 0; i < 15; i++){
         num = rand()%6 + 1;
         draw(pic);
         delay(100);
      }
      bool bl = false;
      for(int i = 0; i < num; i++){
         if(bl){
            player[nplayer]--;
         }
         else{
            player[nplayer]++;
         }
         if(player[nplayer] > 99){
            bl = true;
            player[nplayer] = 98;
         }
         draw(pic);
         delay(100);
      }
      if(points[player[nplayer]] != player[nplayer]){
         player[nplayer] = points[player[nplayer]];
      }
      if(player[nplayer] == 99){
         play = 0;
         setfillstyle(SOLID_FILL, BLACK);
         bar(150, 280, 650, 420);
         settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
         setusercharsize(3, 2, 3, 2);
         outtextxy(300, 300, "Конец");
         if(player[nplayer] == 0) outtextxy(170, 350, "Победа игрока 0");
         else outtextxy(170, 350, "Победа игрока 1");
         delay(2000);
         startgame();
         return;
      }
      if(num != 6){
         nplayer = (nplayer+1)%2;
      }
      delay(700);
   }
}

void drawmenu(){ // отрисовка меню
   p = 1-p;
   setactivepage(p);
   clearviewport();
   
   if(button != -1){
      bar(326, 301+button*100, 524, 349+button*100);
   }
   
   settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(1, 1, 3, 2);
   outtextxy(220, 150, "Фантастические змеи");
   outtextxy(200, 190, "и деревянные листницы");
   
   setusercharsize(4, 5, 1, 1);
   rectangle(325, 300, 525, 350);
   outtextxy(380, 310, "Играть");
   
   rectangle(325, 400, 525, 450);
   outtextxy(365, 410, "Об игре");
   
   rectangle(325, 500, 525, 550);
   outtextxy(375, 510, "Выход");
   
   setvisualpage(p);
}

void above(){ // отрисовка об игре
   while(1){
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
      settextstyle(SIMPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
      setusercharsize(1, 1, 3, 2);
      outtextxy(350, 150, "Об игре");
      
      setusercharsize(1, 2, 1, 2);
      outtextxy(50, 250, "– Игрок ходит первый, бросает игральную кость и двигает свою фишку на");
      outtextxy(50, 275, "такое количество ячеек, которое выпало на игральной кости.");
      outtextxy(50, 305, "– Если на игральной кости выпадает число 6, то игрок делает ещё один ход,");
      outtextxy(50, 330, "иначе ход переходит компьютеру.");
      outtextxy(50, 360, "– Целью игры является добраться до ячейки 100.");
      outtextxy(50, 390, "– По пути игрокам будут попадаться лестницы, которые поднимут их вверх,");
      outtextxy(50, 415, "или змеи, которые спустят их вниз.");
      outtextxy(50, 445, "– Игрок, добравшийся первым до ячейки 100, считается победителем.");
      
      if(abs(425-mousex()) < 100 && abs(575-mousey()) < 25){
         bar(326, 551, 524, 599);
         if(mousebuttons() == 1){
            return;
         }
      }
      
      setusercharsize(4, 5, 1, 1);
      rectangle(325, 550, 525, 600);
      outtextxy(375, 560, "Выход");
      
      setvisualpage(p);
      delay(50);
   }
}

void treatmenu(){ // обработка меню
   int x = mousex(), y = mousey();
   button = -1;
   if(abs(425-x) < 100 && abs(325-y) < 25){
      button = 0;
   }
   if(abs(425-x) < 100 && abs(425-y) < 25){
      button = 1;
   }
   if(abs(425-x) < 100 && abs(525-y) < 25){
      button = 2;
   }
   
   if(button == 0 && mousebuttons() == 1){
      play = 1;
   }
   if(button == 1 && mousebuttons() == 1){
      above();
   }
   if(button == 2 && mousebuttons() == 1){
      exit(0);
   }
}

int main(){
   initwindow(850, 700, "Win", 50, 50);
   IMAGE *picm;
   picm=loadBMP("map.bmp"); // Загрузка картинки
   if(picm==NULL) exit(1); // Ошибка при загрузке
   srand(time(0));
   startgame();
   for(int i = 0; i < 100; i++){
      points[i] = i;
   }
   points[0] = 37; // создание связей между клетками поля
   points[3] = 13;
   points[8] = 30;
   points[15] = 5;
   points[20] = 41;
   points[27] = 83;
   points[35] = 43;
   points[46] = 25;
   points[48] = 29;
   points[50] = 66;
   points[55] = 52;
   points[61] = 18;
   points[62] = 59;
   points[70] = 90;
   points[61] = 18;
   points[79] = 99;
   points[86] = 23;
   points[92] = 72;
   points[94] = 74;
   points[97] = 77;
   
   for(int i = 0; i < 3; i++){
      buts[i].x = 425;
      buts[i].y = 325+i*100
   }
   _abracadabra_cast(buts[0]);