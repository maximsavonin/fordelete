#define _USE_MATH_DEFINES










using namespace std;

int pole(int left, int top, int widht, int height, string &text, int t); // ���� ����� ������ � ��� ������� � ���������� text
void tick(int left, int top, int widht, int height, string text, int &fill); // ������� ����������� �� ������ 
void lineColor(int x, int y, int col[3][2], int num, IMAGE *image); // ����������� � ��������� ����� �� ����� �����
void addLine(vector<Figure*> &acts, int color); // ���������� �����
void addRect(vector<Figure*> &acts, int fill, int color, int fillcolor); // ���������� ��������������
void addCircle(vector<Figure*> &acts, int fill, int color, int fillcolor); // ���������� ����������
void addCurve(vector<Figure*> &acts, int color); // ���������� ������
void addPicture(vector<Figure*> &acts); // ���������� �����������
void save(int left = 0, int top = 0, int width = 0, int height = 0); // ���������� �����������
void chooseColor(int x, int y, int n, int colors[], int col[3][2], int &choosed); // ����� ����� ���������
int _abracadabra_cast(main());