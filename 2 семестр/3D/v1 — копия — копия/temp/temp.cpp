






typedef struct Button
{
   int x, y;
   char text[20] = {0};
}Button;

void save()
{
   int width, height;
   IMAGE *output;
   
   width  = getmaxx() + 1;
   height = getmaxy() + 1;
   output = createimage(width, height);
   
   getimage(0, 0, width - 1, height - 1, output);
   saveBMP("output.bmp", output);
   freeimage(output);
}

int main()
{
   initwindow(1920, 1080, "Win", 0, 40);
   Button btns[12] = {{500, 300, "1"}, {800, 300, "2"}, {1100, 300, "3"}, {1400, 300, "4"}, {500, 500, "5"}, {800, 500, "6"}, {1100, 500, "7"}, {1400, 500, "8"}, {0, 0, "Red"}, {0, 0, "Green"}, {0, 0, "Blue"}, {0, 0, "Save"}};
   int p = 0, num = -1;
   int h = 30, w = 70;
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, USER_CHAR_SIZE);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   setusercharsize(1, 1, 3, 2);
   while(1)
   {
      p = 1-p;
      setactivepage(p);
      clearviewport();
      
      for(int i = 0; i < 8; i++)
      {
         if(abs(mousex()-_abracadabra_cast(btns[i]);