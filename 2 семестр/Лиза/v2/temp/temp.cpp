







#define MAX_WIDTH 370
#define MAX_HEIGHT 590

struct button{
   char name[3] = {' ', ' ', 0};
   int status = 0;
   int x = 0;
   int y = 0;
};

void math(char str[100])
{
   int num1 = 0, num2 = 0, res = 0, dl = 0;
   char sign = ' ', resstr[100];
   
   for(int i = 0; i < 100; i++)
   {
      resstr[i] = ' ';
   }
   
   for(int i = 0; str[i-1] != ' '; i++)
   {
      if(str[i] >= '0' and str[i] <= '9')
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
   for(int i = 0; i < 100; i++){
      if(str[i] < '0' && str[i] > '9'){
         str[i] = ' ';
      }
   }
}

int main(){
   initwindow(MAX_WIDTH, MAX_HEIGHT, "Калькулятор", 500, 200);
   setbkcolor(COLOR(255, 220, 220));
   clearviewport();
   button bs[20]; //массив кнопок
   setcolor(BLACK);
   
   int p = 0;
   char str[101];
   
   for(int i = 0; i < 100; i++)
   {
      str[i] = ' ';
   }
   str[100] = 0;
   
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
               case 19: {
                  math(str);
                  break;
               }
               case 0: {
                  for(int i = 0; i < 100; i++){
                     str[i] = ' ';
                  }
                  break;
               }
               default:{
                  if(bs[but].x < 3 && _abracadabra_cast(bs[but]);