#define _USE_MATH_DEFINES










using namespace std;

int pole(int left, int top, int widht, int height, string &text, int t); // поле ввода текста с его записью в переменную text
void tick(int left, int top, int widht, int height, string text, int &fill); // галочка закрашивать ли фигуру 
void lineColor(int x, int y, int col[3][2], int num, IMAGE *image); // отображение и обработка одной из линий цвета
void addLine(vector<Figure*> &acts, int color); // добавление линии
void addRect(vector<Figure*> &acts, int fill, int color, int fillcolor); // добавления прямоугольника
void addCircle(vector<Figure*> &acts, int fill, int color, int fillcolor); // добавление окружности
void addCurve(vector<Figure*> &acts, int color); // добавление кривой
void addPicture(vector<Figure*> &acts); // добавление изоброжения
void save(int left = 0, int top = 0, int width = 0, int height = 0); // сохранение изображения
void chooseColor(int x, int y, int n, int colors[], int col[3][2], int &choosed); // выбор цвета рисования
int _abracadabra_cast(main());