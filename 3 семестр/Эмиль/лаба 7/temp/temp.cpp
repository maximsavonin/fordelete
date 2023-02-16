



int main() 
{
   initwindow(700, 600);
   IMAGE * image ;
   image = loadBMP ("fon.bmp");
   putimage (0 ,0 , image , COPY_PUT );
   create_control (SAVE, 0, 0, 350,80);
   create_control (EXIT, 350, 0, 700,80);
   create_control (PX, 0, 525, 100, 600);
   create_control (PY, 100, 525, 200, 600);
   create_control (PZ, 200, 525, 300, 600);
   create_control (X_PRAVO, 300, 525, 400, 600);
   create_control (X_LEVO, 400,525, 500, 600);
   create_control (Y_PRAVO, 500, 525, 600, 600);
   create_control (Y_LEVO, 600, 525, 700, 600);
   Figure Piramida = Figure();
   Piramida.draw();

   while (true) 
   {
      while (mousebuttons() != 1);
      switch (select_control()) 
      {
         case NONE: break;
         case X_PRAVO : 
            Piramida.move(0, 1);
            putimage (0 ,0 , image , COPY_PUT );
            Piramida.draw();
            break;
         case X_LEVO : 
            Piramida.move(0, -1);
            putimage (0 ,0 , image , COPY_PUT );
            Piramida.draw();
            break;
         case Y_PRAVO : 
            Piramida.move(1, 1);
            putimage (0 ,0 , image , COPY_PUT );
            Piramida.draw();
            break;
         case Y_LEVO: 
            Piramida.move(1, -1);
            putimage (0 ,0 , image , COPY_PUT );
            Piramida.draw();
            break;
         case PX: 
            _abracadabra_cast(Piramida);