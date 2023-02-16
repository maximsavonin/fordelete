#define _USE_MATH_DEFINES





using namespace std;

struct Point
{
   int x, y;
};

void init_controls(){
   init_control(UP,0,0,"up.bmp");
   init_control(DOWN,100,0,"down.bmp");
   init_control(RIGHT,200,0,"right.bmp");
   init_control(LEFT,300,0,"left.bmp");
   init_control(L_SPIN,400,0,"lspin.bmp");
   init_control(R_SPIN,500,0,"rspin.bmp");
   init_control(U_SCALE,600,0,"uscale.bmp");
   init_control(D_SCALE,700,0,"dscale.bmp");
   init_control(SAVE,700,700,"save.bmp");
   init_control(EXIT,600,700,"exit.bmp");
}

void draw_interface(){
   for(int i=0;i<N_CONTROLS;i++){
      draw_image(i);
   }
}

int main()
{
   initwindow(800, 800);
   
   Point *figure;
   figure = new Point[4];
   _abracadabra_cast(figure[0]);