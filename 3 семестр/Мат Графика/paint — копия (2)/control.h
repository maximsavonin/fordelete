#ifndef CONTROL_H
#define CONTROL_H

int pole(int, int, int, int, std::string, int, int&, int);
void lineColor(int, int, int[3][2], int, IMAGE*);
IMAGE *saveScr(int, int, int, int);
bool butSave(int, int);

#endif
