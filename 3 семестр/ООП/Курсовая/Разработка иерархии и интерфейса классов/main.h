#define _USE_MATH_DEFINES

#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
#include <vector>

#include "graphics.h"
#include "draw.h"

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
int main() // основная функция
{
   int col[3][2] = {{255, 0}, {255, 0}, {255, 0}}; // цвет выбранный на полосках RGB и флаг держим ли мы ползунок мышкой
   int colors[10] = {WHITE, WHITE, RED, GREEN, BLUE, WHITE, WHITE, WHITE, WHITE, WHITE}; // массив цветов рисования и сохранённых цветов
   int p = 0, t = 0; // отоброжаемая страница и таймер для отоброжения | при вводе названия файла
   int mode = 0, fill = 0, choosed = -1; // режим рисования, закрашиваем ли мы фигуру, выбранный квадратик цветов
   vector<Figure*> acts; // все отоброжаемые фигуры
   
   const int numButton = 4; // количество кнопок для выбора режима рисования
   Figure *button[numButton][2]; // массив иконок кнопок
   
   Line butsave[18] = { Line(1150, 20, 1177, 20, BLACK, 1), // иконка кнопка сохранения
                                  Line(1177, 20, 1180, 23, BLACK, 1),
                                  Line(1180, 23, 1180, 50, BLACK, 1),
                                  Line(1180, 50, 1150, 50, BLACK, 1),
                                  Line(1150, 50, 1150, 20, BLACK, 1),
                                  Line(1155, 20, 1155, 28, BLACK, 1),
                                  Line(1155, 28, 1175, 28, BLACK, 1),
                                  Line(1175, 28, 1175, 20, BLACK, 1),
                                  Line(1170, 22, 1173, 22, BLACK, 1),
                                  Line(1173, 22, 1173, 26, BLACK, 1),
                                  Line(1173, 26, 1170, 26, BLACK, 1),
                                  Line(1170, 26, 1170, 22, BLACK, 1),
                                  Line(1155, 50, 1155, 31, BLACK, 1),
                                  Line(1155, 31, 1175, 31, BLACK, 1),
                                  Line(1175, 31, 1175, 50, BLACK, 1),
                                  Line(1157, 35, 1173, 35, BLACK, 1),
                                  Line(1157, 40, 1173, 40, BLACK, 1),
                                  Line(1157, 45, 1173, 45, BLACK, 1) };

   Line butclear[13] = { Line(1130, 20, 1115, 35, BLACK, 5), // иконка кнопки отчистки
                                 Line(1116, 36, 1099, 49, BLACK, 1),
                                 Line(1114, 34, 1101, 51, BLACK, 1),
                                 Line(1116, 36, 1098, 48, BLACK, 1),
                                 Line(1114, 34, 1102, 52, BLACK, 1),
                                 Line(1117, 37, 1097, 47, BLACK, 1),
                                 Line(1113, 33, 1103, 53, BLACK, 1),
                                 Line(1117, 37, 1096, 46, BLACK, 1),
                                 Line(1113, 33, 1104, 54, BLACK, 1),
                                 Line(1118, 38, 1095, 45, BLACK, 1),
                                 Line(1112, 32, 1105, 55, BLACK, 1),
                                 Line(1118, 38, 1094, 44, BLACK, 1),
                                 Line(1112, 32, 1106, 56, BLACK, 1) };

   Line butback[3] = { Line(1080, 35, 1050, 35, BLACK, 3), // иконки кнопки отмены действия
                                 Line(1050, 35, 1065, 20, BLACK, 3),
                                 Line(1050, 35, 1065, 50, BLACK, 3) };

   Figure *butload[4] = { new Rect(1005, 35, 1025, 55, BLACK, 2), // иконка кнопки загрузки изоброжения
                                    new Line(1015, 45, 1015, 15, BLACK, 2),
                                    new Line(1015, 15, 1006, 24, BLACK, 2),
                                    new Line(1015, 15, 1024, 24, BLACK, 2)};
   return 0;
}