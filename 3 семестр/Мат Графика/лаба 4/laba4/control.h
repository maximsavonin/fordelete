#ifndef CONTROL_H
#define CONTROL_H

struct Button;

int pole(int, int, int, int, std::string, int, int&, int);
void lineColor(int, int[3][2], int, IMAGE*);
bool button(Button);

#endif