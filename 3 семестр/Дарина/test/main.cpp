#include "graphics.h"
#include "control.h"
#include "task.h"


int main() {
   initwindow(900, 690);

   IMAGE * image ;
   image = loadBMP ("sims.bmp");
   putimage (0 ,0 , image , COPY_PUT );
   
   create_control (SAVE, 0, 0, 100, 50);//тут
   create_control (EXIT, 810, 0, "exit.bmp");//тут
   create_control (MOVE_X_PLUS, 0, 620, "movexplus.bmp");//и тут
   create_control (MOVE_X_MINUS, 130, 620, "movexminus.bmp");//и тут
   create_control (MOVE_Y_PLUS, 260, 620, "moveyplus.bmp");//тут
   create_control (MOVE_Y_MINUS, 390, 620, "moveyminus.bmp");//тут
   create_control (ROTATE_X, 520, 620, "rotatex.bmp");//тут
   create_control (ROTATE_Y, 650, 620, "rotatey.bmp");//и даже тут
   create_control (ROTATE_Z, 780, 620, "rotatez.bmp");//тут тоже
   
   Figure figure = Figure();
   figure.draw(0);

   while (true) {
      while (mousebuttons() != 1);
      switch (select_control()) 
      {
         case NONE: break;
         case MOVE_X_PLUS : 
            figure.move(0, 1);
            putimage (0 ,0 , image , COPY_PUT );
            create_control (SAVE, 0, 0, "save.bmp");//не знаю зачем это, но если это раньше рисовала кнопку то удалить
            create_control (EXIT, 810, 0, "exit.bmp");//и это
            figure.draw(0);
            break;
         case MOVE_X_MINUS : 
            figure.move(0, -1);
            putimage (0 ,0 , image , COPY_PUT );
            create_control (SAVE, 0, 0, "save.bmp");//аналогично
            create_control (EXIT, 810, 0, "exit.bmp");
            figure.draw(0);
            break;
         case MOVE_Y_PLUS : 
            figure.move(1, 1);
            putimage (0 ,0 , image , COPY_PUT );//аналогично
            create_control (SAVE, 0, 0, "save.bmp");
            create_control (EXIT, 810, 0, "exit.bmp");
            figure.draw(0);
            break;
         case MOVE_Y_MINUS : 
            figure.move(1, -1);
            putimage (0 ,0 , image , COPY_PUT );//аналогично
            create_control (SAVE, 0, 0, "save.bmp");
            create_control (EXIT, 810, 0, "exit.bmp");
            figure.draw(0);
            break;
         case ROTATE_X: 
            figure.rotate(0);
            putimage (0 ,0 , image , COPY_PUT );//аналогично
            create_control (SAVE, 0, 0, "save.bmp");
            create_control (EXIT, 810, 0, "exit.bmp");
            figure.draw(0); 
            break;
         case ROTATE_Y: 
            figure.rotate(1);
            putimage (0 ,0 , image , COPY_PUT );//аналогично
            create_control (SAVE, 0, 0, "save.bmp");
            create_control (EXIT, 810, 0, "exit.bmp");
            figure.draw(0);
            break;
         case ROTATE_Z: 
            figure.rotate(2);
            putimage (0 ,0 , image , COPY_PUT );//аналогично
            create_control (SAVE, 0, 0, "save.bmp");
            create_control (EXIT, 810, 0, "exit.bmp");
            figure.draw(0);
            break;
         case SAVE: save(); break;
         case EXIT: closegraph(); return 0;
      }
      
      delay(50);
   }
   freeimage (image);
}

