//
//  main.cpp
//  polynom
//
//  Created by Елизавета Ныркова on 31.12.2022.
//

#ifndef _POLYNOME_H_
#define _POLYNOME_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

class Monome
{ // Класс мономов из которых состоит полином
private:
   double coef = 1; // Коэфициент монома
   std::map<char, int> pows;  // Переменные и их степени

public:
   // Конструктор
   Monome() = default;
   Monome(std::string); // конструктор преобразователь из string в Monome
   Monome(double num):coef(num) {} // Конструктор-преобразоватенль из double в Monome

   // Определение операции
   Monome operator *(const Monome &obj) const ;

   Monome operator *(double number) const;
   Monome operator /(double number) const;

   friend bool operator==(const Monome &obj1, const Monome &obj2);
   // Ввод и вывод
   friend std::ostream &operator <<(std::ostream &out, const Monome &obj);
   friend std::istream &operator >>(std::istream &in, Monome &obj);

   // Метод сравнивания для нахождения общих мономов для операции
   bool similar(const Monome &obj) const {return pows == obj.pows;}

    void differentiate(char c);
   friend class Polynome;
};
// Определим операцию
inline bool operator!=(const Monome &obj1, const Monome &obj2) {
   return !(obj1 == obj2);
}

class Polynome {
private:
   //Вектор, содержащий мономы на которые раскладывается полином
   std::vector<Monome> terms;

public:
   // Конструктор
   Polynome() {}
   Polynome(std::string); // Конструктор-преобразователь из string в Polynome
   Polynome(double num);// Конструктор-преобразователь из double в Polynome
   Polynome(Monome num);// Конструктор-преобразователь из Monome в Polynome

   // Определение операции для работы с полиномом
   Polynome operator +(const Polynome &obj) const;
   Polynome operator -(const Polynome &obj) const;
   Polynome operator *(const Polynome &obj) const;

   // Определение операции для работы с числом
   Polynome operator /(double number) const;

   // Ввод и вывод
   friend std::ostream &operator<<(std::ostream &out, const Polynome &obj);
   friend std::istream &operator>>(std::istream &in, Polynome &obj);

   //Получение переменных
   std::vector<char> print_variables();
   double count_for(std::map<char, double> &mp);

   Polynome derivative(char c);
};


#endif
