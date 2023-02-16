#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <math.h>

#include "graphics.h"

#define MAX_WIDTH 370 // ширина экрана
#define MAX_HEIGHT 590 // высота экрана

char str[101]; // основной пример выведеный на экран

typedef struct button{ // структура кнопка
   char name[15]; // название
   int x = 0; // место находние на сетке
   int y = 0;
   int code = -1; // код клавиши на клавиатуре
}button;

void tostr(double a, char test[100]) // удаление лишних нулей
{
   sprintf(test,"%lf",a);
   for(int i = 0; i < 100; i++)
   {
      if(test[i] == ',')
      {
         for(int k = 6; (test[i+k] == '0' || test[i+k] == ',') && k >= 0; k--) test[i+k] = 0;
         return;
      }
   }
}

void math() // основные вычисления
{
   double num1 = 0, num2 = 0;
   double res = 0;
   char sign = ' ';
   
   sscanf(str,"%lf%c%lf", &num1, &sign, &num2);
   
   switch(sign)
   {
      case '+':
      {
         res = num1 + num2;
         break;
      }
      case '-':
      {
         res = num1 - num2;
         break;
      }
      case '*':
      {
         res = num1 * num2;
         break;
      }
      case '/':
      {
         res = num1 / num2;
         break;
      }
      case ' ':
      {
         return;
      }
   }
   strcpy(str, "");
   tostr(res, str);
}

void percent(){ // обработка процента
   double num1 = 0, num2 = 0;
   char sign;
   
   sscanf(str,"%lf%c%lf",&num1,&sign,&num2);
   
   if(sign == '+' || sign == '-'){
      num2 = num1/100*num2;
   }
   if(sign == '*' || sign == '/'){
      num2 /= 100;
   }
   
   char test1[100] = "", test2[100] = "";
   tostr(num1, test1);
   tostr(num2, test2);
   sprintf(str, "%s%c%s", test1, sign, test2);
}

void back(){//отрисовка и ожидание нажатия стрелки назад
   rectangle(0, 0, 40, 40);
   rectangle(0, 0, 369, 40);
   line(10, 20, 35, 20);
   line(10, 20, 20, 5);
   line(10, 20, 20, 35);
   while(!mousebuttons() || mousex() > 50 || mousey() > 50);
   while(mousebuttons());
}

void help(){ //отрисовка окна помощь
   clearviewport();
   setusercharsize(2, 4, 1, 1);
   settextjustify(LEFT_TEXT,CENTER_TEXT);
   setlinestyle(SOLID_LINE, 1, 1);
   outtextxy(140, 30, "Техподдержка");
   outtextxy(10, 70, "техподдержка");
   outtextxy(10, 100, "временно не работает");
   back();
}

void about(){ // отрисовка окна о приложении
   clearviewport();
   setlinestyle(SOLID_LINE, 1, 1);
   setusercharsize(2, 4, 1, 1);
   settextjustify(LEFT_TEXT,CENTER_TEXT);
   outtextxy(140, 30, "О приложении");
   outtextxy(10, 70, "Designed by Lilz Corporate");
   outtextxy(10, 100, "in Chelyabinsk Assembled");
   outtextxy(10, 130, "in Obshyaga");
   back();
}
int main(){
   setlocale(LC_NUMERIC,"Russian");
   initwindow(MAX_WIDTH, MAX_HEIGHT, "Калькулятор", 500, 200);
   setbkcolor(COLOR(255, 220, 220));
   clearviewport();
   button bs[22] = {{"CE", 0, 0, 27}, {"MS", 1, 0, -1}, {"MR", 2, 0, -1}, {"/ ", 3, 0, 47}, {"7", 0, 1, 55}, {"8", 1, 1, 56}, {"9", 2, 1, 57}, {"*", 3, 1, 42}, {"4", 0, 2, 52}, {"5", 1, 2, 53}, {"6", 2, 2, 54}, {"-", 3, 2, 45}, {"1", 0, 3, 49}, {"2", 1, 3, 50}, {"3", 2, 3, 51}, {"+", 3, 3, 43}, {"%", 0, 4, -1}, {"0", 1, 4, 48}, {",", 2, 4, 46}, {"=", 3, 4, 13}, {"Помощь", 0, 0, -1}, {"О приложении", 1, 0, -1}}; //массив кнопок
   setcolor(BLACK);
   
   int p = 0, but; // номер отображаемой страницы и кнопка на которую навелись или нажали
   char mem[101]; //дополнительная память работающая по кнопкам MS MR
   
   strcpy(str, "");
   strcpy(mem, "");
   str[100] = 0;
   mem[100] = 0;
   

   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(2, 3, 3, 2);
   while (1) {
      but = -1;
      
      if(mousex()%90>10 && (mousey()-130)%90>10 || kbhit() || mousey() < 50){
         if(mousey() < 50) but = mousex()/185 + 20;
         else but = mousex()/90 + (mousey()-130)/90*4;
         if(mousebuttons() == 1 || kbhit()){
            if(kbhit()){ // ввод с клавиатуры
               int key = getch();
               for(int i = 0; i < 20; i++){
                  if(bs[i].code == key){
                     but = i;
                     break;
                  }
               }
               while(kbhit());
            }
            while(mousebuttons());
            switch(but){
               case 0: {
                  strcpy(str, "");
                  str[100] = 0;
                  break;
               }
               case 1: {
                  math();
                  strcpy(mem, str);
                  strcpy(str, "");
                  break;
               }
               case 2: {
                  if(mem == ""){
                     break;
                  }
                  strcat(str,mem);
                  break;
               }
               case 16: {
                  percent();
                  break;
               }
               case 19: {
                  math();
                  break;
               }
               case 20: {
                  help();
                  break;
               }
               case 21: {
                  about();
                  break;
               }
               default:{
                  if(but == -1) break;
                  if(bs[but].x == 3 || bs[but].y == 0){
                     math();
                  }
                  strcat(str, bs[but].name);
               }
            }
         }
      }
      p = 1-p;
      setactivepage(p);
      clearviewport();
      setusercharsize(2, 3, 3, 2);
      for(int i = 0; i<20; i++){
         if(but == i) setlinestyle(SOLID_LINE, 1, 2);
         else setlinestyle(SOLID_LINE, 1, 1);
         rectangle(10*(bs[i].x+1)+80*bs[i].x, 140+90*bs[i].y, 90*(bs[i].x+1), 220+90*bs[i].y);
         settextjustify(CENTER_TEXT,TOP_TEXT);
         outtextxy(10*(bs[i].x+1)+80*bs[i].x+40, 140+90*bs[i].y+19, bs[i].name);
      }
      setusercharsize(2, 4, 1, 1);
      for(int i = 20; i<22; i++){
         if(but == i) setlinestyle(SOLID_LINE, 1, 2);
         else setlinestyle(SOLID_LINE, 1, 1);
         rectangle(bs[i].x*185, 1, (bs[i].x+1)*184+1, 50);
         settextjustify(CENTER_TEXT,CENTER_TEXT);
         outtextxy(92+bs[i].x*185, 35, bs[i].name);
      }
      setusercharsize(9, 10, 7, 4);
      settextjustify(RIGHT_TEXT,TOP_TEXT);
      outtextxy(360, 80, str);
      
      setvisualpage(p);
      delay(30);
   }
}