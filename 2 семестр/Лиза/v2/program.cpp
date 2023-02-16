#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <math.h>

#include "graphics.h"

#define MAX_WIDTH 370
#define MAX_HEIGHT 590

int str[101];

struct button{
   char name[3] = {' ', ' ', 0};
   int status = 0;
   int x = 0;
   int y = 0;
};

void readnum(int s=0){
   double num;
   for(int i = s; i < 100; i++){
      
   }
}

void math()
{
   int num1 = 0, num2 = 0, res = 0, dl = 0;
   char sign = ' ', resstr[100];
   
   for(int i = 0; i < 100; i++)
   {
      resstr[i] = ' ';
   }
   
   for(int i = 0; str[i-1] != ' '; i++)
   {
      if(str[i] >= '0' && str[i] <= '9')
      {
         if(sign == ' ')
         {
            num1 = num1*10 + (str[i]-'0');
         }
         else
         {
            num2 = num2*10 + (str[i]-'0');
         }
      }
      else
      {
         printf("%d %c %d\n", num1, sign, num2);
         if(sign == ' ') sign = str[i];
         else
         {
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
            }
            printf("%d", res);
            if(res == 0){
               str[0] = '0';
               for(int k = 1; k < 100; k++){
                  str[k] = ' ';
               }
            }
            else
            {
               for(int k = 99; res != 0; k--)
               {
                  resstr[k] = (res%10+'0');
                  res /= 10;
                  dl++;
               }
               for(int k = 0; k < dl; k++)
               {
                  str[k] = resstr[100-dl+k];
               }
               for(int k = i; k < 100; k++)
               {
                  str[k-i+dl] = str[k];
               }
               math();
               return;
            }
         }
      }         
   }
   for(int i = 0; i < 100; i++){
      if(str[i] < '0' && str[i] > '9'){
         str[i] = ' ';
      }
   }
}

void percent(){
   int num1 = 0, num2 = 0;
   for(int i = 0; i < 100; i++){
      if(str[i] == '+' || str[i] == '-'){
         for(int k = i+1; str[k] != ' '; k++){
            num2 = num2*10+(str[k]-'0');
         }
         num2 = num1/100*num2;
         int n = 0, num = num2;
         while(num != 0){
            n++;
            num /= 10;
         }
         for(int k = 0; num2 != 0; k++){
            str[i+n-k] = num2 % 10 + '0';
            num2 = num2 / 10;
         }
         for(int k = i+n+1; k<100; k++){
            str[k] = ' ';
         }
         break;
      }
      
      if(str[i] == '*' || str[i] == '/'){
         for(int k = i+1; str[k] != ' '; k++){
            num2 = num2*10+(str[k]-'0');
         }
         num2 = num2/100;
         int n = 0, num = num2;
         while(num != 0){
            n++;
            num /= 10;
         }
         for(int k = 0; num2 != 0; k++){
            str[i+n-k] = num2 % 10 + '0';
            num2 = num2 / 10;
         }
         for(int k = i+n+1; k<100; k++){
            str[k] = ' ';
         }
         break;
      }
      num1 = num1*10+(str[i]-'0');
   }
}

int main(){
   initwindow(MAX_WIDTH, MAX_HEIGHT, "Калькулятор", 500, 200);
   setbkcolor(COLOR(255, 220, 220));
   clearviewport();
   button bs[20]; //массив кнопок
   setcolor(BLACK);
   
   int p = 0;
   char mem[101];
   
   for(int i = 0; i < 100; i++)
   {
      mem[i] = ' ';
      str[i] = ' ';
   }
   str[100] = 0;
   mem[100] = 0;
   
   bs[0].name[0] = 'C';
   bs[0].name[1] = 'E';
   bs[0].x = 0;
   bs[0].y = 0;

   bs[1].name[0] = 'M';
   bs[1].name[1] = 'S';
   bs[1].x = 1;
   bs[1].y = 0;

   bs[2].name[0] = 'M';
   bs[2].name[1] = 'R';
   bs[2].x = 2;
   bs[2].y = 0;

   bs[3].name[0] = '/';
   bs[3].name[1] = ' ';
   bs[3].x = 3;
   bs[3].y = 0;

   bs[4].name[0] = '7';
   bs[4].name[1] = ' ';
   bs[4].x = 0;
   bs[4].y = 1;

   bs[5].name[0] = '8';
   bs[5].name[1] = ' ';
   bs[5].x = 1;
   bs[5].y = 1;

   bs[6].name[0] = '9';
   bs[6].name[1] = ' ';
   bs[6].x = 2;
   bs[6].y = 1;

   bs[7].name[0] = '*';
   bs[7].name[1] = ' ';
   bs[7].x = 3;
   bs[7].y = 1;

   bs[8].name[0] = '4';
   bs[8].name[1] = ' ';
   bs[8].x = 0;
   bs[8].y = 2;

   bs[9].name[0] = '5';
   bs[9].name[1] = ' ';
   bs[9].x = 1;
   bs[9].y = 2;

   bs[10].name[0] = '6';
   bs[10].name[1] = ' ';
   bs[10].x = 2;
   bs[10].y = 2;

   bs[11].name[0] = '-';
   bs[11].name[1] = ' ';
   bs[11].x = 3;
   bs[11].y = 2;

   bs[12].name[0] = '1';
   bs[12].name[1] = ' ';
   bs[12].x = 0;
   bs[12].y = 3;

   bs[13].name[0] = '2';
   bs[13].name[1] = ' ';
   bs[13].x = 1;
   bs[13].y = 3;

   bs[14].name[0] = '3';
   bs[14].name[1] = ' ';
   bs[14].x = 2;
   bs[14].y = 3;

   bs[15].name[0] = '+';
   bs[15].name[1] = ' ';
   bs[15].x = 3;
   bs[15].y = 3;

   bs[16].name[0] = '%';
   bs[16].name[1] = ' ';
   bs[16].x = 0;
   bs[16].y = 4;

   bs[17].name[0] = '0';
   bs[17].name[1] = ' ';
   bs[17].x = 1;
   bs[17].y = 4;
   
   bs[18].name[0] = ',';
   bs[18].name[1] = ' ';
   bs[18].x = 2;
   bs[18].y = 4;
   
   bs[19].name[0] = '=';
   bs[19].name[1] = ' ';
   bs[19].x = 3;
   bs[19].y = 4;
   
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
      /*setfillstyle(SOLID_FILL, COLOR(255, 220, 220));
      bar(0, 0, 370, 590);*/
      for(int i = 0; i<20; i++){
         rectangle(10*(bs[i].x+1)+80*bs[i].x, 140+90*bs[i].y, 90*(bs[i].x+1), 220+90*bs[i].y);
         /*setfillstyle(SOLID_FILL, COLOR(120, 120, 255));
         bar(10*(bs[i].x+1)+80*bs[i].x+1, 141+90*bs[i].y, 90*(bs[i].x+1)-1, 219+90*bs[i].y);*/
         if(bs[i].name[1] == ' '){
            outtextxy(10*(bs[i].x+1)+80*bs[i].x+30, 140+90*bs[i].y+19, bs[i].name);
         }
         else{
            outtextxy(10*(bs[i].x+1)+80*bs[i].x+15, 140+90*bs[i].y+19, bs[i].name);
         }
      }
      char test[100];
      for(int i = 0; i < 100; i++){
         test[i] = NULL;
      }
      for(int i = 0; i < 100; i++){
         if(str[i] == ' '){
            break;
         }
         test[i] = str[i];
      }
      outtextxy(360-textwidth(test), 90, test);
      
      setvisualpage(p);
   }
}
/*
int main()
{
   char str[100];
   
   for(int i = 0; i < 100; i++)
   {
      str[i] = ' ';
   }
   
   while(1)
   {
      scanf("%s", &str);
      math(str);
      str[99] = '\0';
      puts(str);
   }
}*/