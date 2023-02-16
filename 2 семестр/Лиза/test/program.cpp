#include "stdio.h"
#include "stdlib.h"
#include "random"
#include "ctime"

void math(char str[100])
{
   int num1 = 0, num2 = 0, res = 0, dl = 0;
   char sign = ' ', resstr[100];
   
   for(int i = 0; i < 100; i++)
   {
      resstr[i] = ' ';
   }
   
   for(int i = 0; str[i] != ' '; i++)
   {
      if(str[i] >= '0' and str[i] <= '9' and str[i+1] != ' ')
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
            if(res == 0) resstr[0] = '0';
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
               math(str);
               return;
            }
         }
      }         
   }
}

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
}