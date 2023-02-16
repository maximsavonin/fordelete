#ifndef DRAW_H
#define DRAW_H

struct Point;
Point *addPoint(int, int, Point*);

class lineB
{
   private:
      int x1, y1, x2, y2;
      int color = WHITE, width = 1;
   
   public:
      lineB(){}
      lineB(int, int, int, int);
      lineB(int, int, int, int, int);
      lineB(int, int, int, int, int, int);
      void setColor(int);
      void setStart(int, int);
      void setEnd(int, int);
      void setWidth(int);
      void draw();
};

class star
{
   private:
      int x, y, r;
      int n = 5, colorLine = WHITE, colorFill = WHITE;
      float fi;
      lineB lines[50];
      void creatStar();
      void lineColor();

   public:
      star(){}
      star(int, int, int, int);
      star(int, int, int, int, float);
      star(int, int, int, int, float, int);
      star(int, int, int, int, float, int, int);
      star(const star &obj);
      ~star(){/*delete[] lines;*/}
      void setRadius(int);
      void setCenter(int, int);
      void setNumCorners(int);
      void setColorLine(int);
      void setColorFill(int);
      void setCorners(int);
      void draw();
      void fill();
};

class circl
{
   private:
      int x, y, r;
      int colorLine = WHITE, colorFill = WHITE;

   public:
      circl(){}
      circl(int, int, int);
      circl(int, int, int, int);
      circl(int, int, int, int, int);
      void setCenter(int, int);
      void setRadius(int);
      void setColorLine(int);
      void setColorFill(int);
      void draw();
      void fill();
};

class lineBez
{
   private:
      int n = 0, color = WHITE, width = 1;
      int data[100][2];
      double step = 0.02;
      void pefog(int[100], int, int);
   
   public:
      lineBez();
      lineBez(int);
      lineBez(int, int);
      void add(int, int);
      void setColor(int);
      void setWidth(int);
      void setStep(double);
      void draw();
};

class lineCha
{
   private:
      int color = WHITE, width = 1;
      Point *root;
      Point *chaikin(Point *);
      void drawL(Point *);
      void del(Point *);
   
   public:
      lineCha();
      lineCha(int);
      lineCha(int, int);
      ~lineCha();
      void delRoot();
      void add(int, int);
      void setColor(int);
      void setWidth(int);
      void draw();
};

struct Fill;
struct act;
void fillIn(int, int, int, int);
void drawAll(act[1000], int);
void addLine(act[1000], int&, int);
void addStar(act[1000], int&, int);
void addCircle(act[1000], int&, int);
void addLineBez(act[1000], int&, int);
void save(int, int, int, int);

#endif