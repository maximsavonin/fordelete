#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <math.h>

#include "graphics.h"

#define MAX_WIDTH 370 // ширина экрана
#define MAX_HEIGHT 590 // высота экрана

int str[101]; // основной пример выведеный на экран

typedef struct button{ // структура кнопка
   char name[3] = {' ', ' ', 0}; // название
   int x = 0; // место находние на сетке
   int y = 0;
}button;

//sscanf(str,"%lf%c%lf",&num1,&sign,&num2); rror: cannot convert 'int*' to 'const char*'
double readnum(int s=0){ // считывание числа из главной строки начина€ с s символа
   double num = 0;
   int drob = 0;
   int kof = 1, dot = 0;
   if(str[s] == '-'){
      kof = -1;
      s++;
   }
   for(int i = s; i < 100; i++){
      if(str[i] >= '0' && str[i] <= '9'){
         if(dot == 0){
            num = num*10 + (str[i]-'0');
         }
         else{
            drob++;
            num += 1.0*(str[i]-'0')/pow(10, drob);
         }
      }
      else if(str[i] == ',') dot = 1;
      else break;
   }
   return num*kof;
}

void math() // основные вычислени€
{
   double num1 = 0, num2 = 0;
   double res = 0, dubres = 0;
   int dl = 0;
   char sign = ' ', resstr[100];
   
   for(int i = 0; i < 100; i++)
   {
      resstr[i] = ' ';
   }
   
   num1 = readnum();
   int i = 0;
   if(str[0] == '-') i++;
   for(i; i < 100; i++){
      if(!(str[i] >= '0' && str[i] <= '9' || str[i] == ',')) break;
   }
   sign = str[i];
   i++;
   printf("%c", str[i]);
   num2 = readnum(i);
   if(str[0] == '-') i++;
   for(i; i < 100; i++){
      if(!(str[i] >= '0' && str[i] <= '9' || str[i] == ',')) break;
   }
   printf("%lf %c %lf\n", num1, sign, num2);
   
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
   //sprintf(str,"%lf",res);  error: cannot convert 'int*' to 'char*'
   if(res == 0){
      str[0] = '0';
      for(int k = 1; k < 100; k++){
         str[k] = ' ';
      }
   }
   else{
      int k = 0;
      if(res < 0){
         resstr[0] = '-';
         res *= -1;
         k++;
      }
      while(res >= 10){
         dl = 10;
         while(res/dl >= 10){
            dl *= 10;
         }
         resstr[k] = (int(res/dl)+'0');
         res -= int(res/dl)*dl;
         k++;
      }
      resstr[k] = int(res)+'0';
      res -= int(res);
      k++;
      if(res >= 0.0001){
         resstr[k] = ',';
         k++;
         for(int j = 0; j < 4 && res>=0.0001; j++){
            res *= 10;
            resstr[k] = (int(res)+'0');
            res = res - int(res);
            k++;
         }
      }
      for(i = 0; i < 100; i++){
         str[i] = resstr[i];
      }
   }
}

void percent(){ // обработка процента
   double num1 = 0, num2 = 0;
   char sign;
   
   num1 = readnum();
   int i = 0;
   if(str[0] == '-') i++;
   for(i; i < 100; i++){
      if(!(str[i] >= '0' && str[i] <= '9' || str[i] == ',')) break;
   }
   sign = str[i];
   i++;
   num2 = readnum(i);
   printf("%lf %c %lf\n", num1, sign, num2);
   
   if(sign == '+' || sign == '-'){
      num2 = num1/100*num2;
   }
   if(sign == '*' || sign == '/'){
      num2 /= 100;
   }
   
   if(num2 == 0){
      str[i] = '0';
      for(int k = i+1; k < 100; k++){
         str[k] = ' ';
      }
   }
   else{
      int dl = 0;
      if(num2 < 0){
         str[i] = '-';
         num2 *= -1;
         i++;
      }
      while(num2 >= 10){
         dl = 10;
         while(num2/dl >= 10){
            dl *= 10;
         }
         str[i] = (int(num2/dl)+'0');
         num2 = int(num2)%dl;
         i++;
      }
      str[i] = int(num2)+'0';
      num2 -= int(num2);
      i++;
      if(num2 >= 0.0001){
         str[i] = ',';
         i++;
         for(int j = 0; j < 4 && num2>=0.0001; j++){
            num2 *= 10;
            str[i] = (int(num2)+'0');
            num2 = num2 - int(num2);
            i++;
         }
      }
      //strcpy(str,' '); error: cannot convert 'int*' to 'char*'
      for(i; i < 100; i++){
         str[i] = ' ';
      }
   }
}

int main(){
   initwindow(MAX_WIDTH, MAX_HEIGHT, " алькул€тор", 500, 200);
   setbkcolor(COLOR(255, 220, 220));
   clearviewport();
   button bs[20] = {{"CE", 0, 0}, {"MS", 1, 0}, {"MR", 2, 0}, {"/ ", 3, 0}, {"7 ", 0, 1}, {"8 ", 1, 1}, {"9 ", 2, 1}, {"* ", 3, 1}, {"4 ", 0, 2}, {"5 ", 1, 2}, {"6 ", 2, 2}, {"- ", 3, 2}, {"1 ", 0, 3}, {"2 ", 1, 3}, {"3 ", 2, 3}, {"+ ", 3, 3}, {"% ", 0, 4}, {"0 ", 1, 4}, {", ", 2, 4}, {"= ", 3, 4}}; //массив кнопок
   setcolor(BLACK);
   
   int p = 0; // номер отображаемой страницы
   char mem[101]; //дополнительна€ пам€ть работающа€ по кнопкам MS MR
   
   //strcpy(str, ' '); error: cannot convert 'int*' to 'char*'
   //strcpy(mem, ' '); error: invalid conversion from 'char' to 'const char*' [-fpermissive]
   for(int i = 0; i < 100; i++)
   {
      mem[i] = ' ';
      str[i] = ' ';
   }
   str[100] = 0;
   mem[100] = 0;
   

   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   setusercharsize(2, 3, 3, 2);
   while (1) {
      p = 1-p;
      setactivepage(p);
      
      if(mousebuttons() == 1){
         if(mousex()%90>10 && (mousey()-130)%90>10){
            int but = mousex()/90 + (mousey()-130)/90*4;
            switch(but){
               case 0: {
                  //strcpy(str, ' '); error: cannot convert 'int*' to 'char*'
                  for(int i = 0; i < 100; i++){
                     str[i] = ' ';
                  }
                  break;
               }
               case 1: {
                  math();
                  for(int i = 0; i < 100; i++){
                     mem[i] = str[i];
                     str[i] = ' ';
                  }
                  break;
               }
               case 2: {
                  if(mem[0] == ' '){
                     break;
                  }
                  //strcat(str,mem); error: cannot convert 'int*' to 'char*'
                  for(int i = 0; i < 100; i++){
                     if((str[i]-'0' < 0 || str[i]-'0' > 9) && str[i] != ' '){
                        for(int k = 0; k <100-i-1; k++){
                           str[i+k+1] = mem[k];
                        }
                        break;
                     }
                  }
                  for(int i = 0; i <100; i++){
                     str[i] = mem[i];
                  }
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
               default:{
                  if(bs[but].x == 3 || bs[but].y == 0){
                     math();
                  }
                  // strcat(str, bs[but].name);  error: cannot convert 'int*' to 'char*'
                  for(int i = 0; i<2; i++){
                     for(int k = 0; k < 100; k++){
                        if(str[k] == ' '){
                           str[k] = bs[but].name[i];
                           break;
                        }
                     }
                  }
               }
            }
         }
         while(mousebuttons() == 1);
      }
      
      clearviewport();
      for(int i = 0; i<20; i++){
         rectangle(10*(bs[i].x+1)+80*bs[i].x, 140+90*bs[i].y, 90*(bs[i].x+1), 220+90*bs[i].y);
         settextjustify(CENTER_TEXT,TOP_TEXT);
         outtextxy(10*(bs[i].x+1)+80*bs[i].x+45, 140+90*bs[i].y+19, bs[i].name);
      }
      char test[100];
      for(int i = 0; i < 100; i++){
         test[i] = 0;
      }
      for(int i = 0; i < 100; i++){
         if(str[i] == ' '){
            break;
         }
         test[i] = str[i];
      }
      settextjustify(RIGHT_TEXT,TOP_TEXT);
      outtextxy(360, 90, test);
      
      setvisualpage(p);
   }
}