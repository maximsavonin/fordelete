#include "graphics.h"
#include "control.h"
#include "task.h"

int main()
{
   initwindow(900, 600);
   
   IMAGE * image ;
   image = loadBMP ("Fon.bmp" );
   putimage (0 , 0 , image , COPY_PUT );
   
   create_control(P_TOP, 0, 540, "p_top.bmp");                //+top
   create_control(M_TOP, 150, 540, "m_top.bmp");           //-top
   create_control(P_SIZE, 300, 540, "p_size.bmp");    //do more size
   create_control(M_SIZE, 450, 540, "m_size.bmp");   //do less size
   create_control(SAVE, 600, 540, "save.bmp");  
   create_control(EXIT, 750, 540, "exit.bmp");
    
   int x = 450, y = 300, radius = 100, n = 21;
   setcolor(COLOR(77, 255, 0));
   
   while (true)
   {
      while (mousebuttons() != 1);
      switch (select_control())
      {
         case NONE: break;
         case P_TOP: 
         {
            if(n<22)n++;
            putimage (0 , 0 , image , COPY_PUT );
            drawStar(x,y,radius,n);
            delay(200);
            break;
         }
         case M_TOP:
         {
            if(n>5)n--; 
            putimage (0 , 0 , image , COPY_PUT );
            drawStar(x,y,radius,n);
            delay(200);
            break;
         }
         case P_SIZE: 
         {
            if(radius<230) radius+=10;
            putimage (0 , 0 , image , COPY_PUT );
            drawStar(x,y,radius,n); 
            break;
         }
         case M_SIZE: 
         {
            if(radius>10) radius-=10;
            putimage (0 , 0 , image , COPY_PUT );
            drawStar(x,y,radius,n); 
            break;
         }
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
   }
   freeimage (image);
}