






Point points[N_POINT];

void genPoint(int left, int top, int width, int height)
{
   IMAGE *image;
   image = loadBMP("back.bmp");
   putimage(left, top, image, COPY_PUT);
   freeimage(image);
   
   for(int i = 0; i < N_POINT; i++)
   {
      points[i].x = rand() % (width-4)+2;
      points[i].y = rand() % (height-4)+2;
      
      IMAGE *image;
      image = loadBMP("slime.bmp");
      putimage(points[i].x-10, _abracadabra_cast(points[i]);