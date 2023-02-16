//
//  main.cpp
//  polynom
//
//  Created by Елизавета Ныркова on 31.12.2022.
//

#include "polynome.h"

#include <sstream>
#include <algorithm>

using namespace std;

Monome::Monome(string str) {
    size_t n;
    coef = stod(str, &n);
    if (n == 0) coef = 1;
   
    for (int i = n; i < str.size(); i++) {
        if (isalpha(str[i])) {
            if (str[i + 1] == '^') {
                size_t k;
                int number = stod(str.substr(i+2), &k);
                pows[str[i]] += number;
                i += k+1;
            }
            else
                pows[str[i]] = 1;
        }
    }
}

Monome Monome::operator*(const Monome &obj) const {
   Monome result = *this;

   result.coef = result.coef * obj.coef;

    for (auto it : obj.pows) {
        if (result.pows.contains(it.first)) {
            result.pows[it.first] += it.second;
        }
        else {
            result.pows[it.first] = it.second;
        }
    }
    return result;
}

Monome Monome::operator*(double number) const {
   Monome result = *this;
   result.coef = result.coef * number;
   return result;
}

Monome Monome::operator/(double number) const {
   if (number == 0) throw std::runtime_error("Ошибка деления мономов");
   Monome result = *this;
   result.coef = result.coef / number;
   return result;
}

void Monome::differentiate(char c)
{
    auto el = pows.find(c);
    if(el != pows.end())
    {
        coef *= el->second;
        el->second -= 1;
    }
    else
    {
        coef = 0;
        pows.clear();
    }
}

bool operator==(const Monome &obj1, const Monome &obj2) {
   return obj1.coef == obj2.coef && obj1.pows == obj2.pows;
}

ostream &operator <<(ostream &out, const Monome &obj) {

    if(obj.coef > 0) out << "+";
   
    out << obj.coef;
    if (obj.pows.size() == 0) return out;

    out << "*";
    int counter = 0;

    for (auto it = obj.pows.begin(); it != obj.pows.end(); ++it)
    {
        if (it->second == 1)
            out << it->first;
        else
            out << it->first << "^" << it->second;
        counter++;

        if (counter != obj.pows.size())
            out << "*";
    }

    return out;
}

istream &operator >>(istream &in, Monome &obj) {

   string str;
   in >> str;

   Monome tmp(str);
   obj = tmp;

   return in;
}

istream &operator >>(istream &in, Polynome &obj) {

   string str;
   in >> str;

   Polynome tmp(str);
   obj = tmp;

   return in;
}

Polynome::Polynome(string str) {

   for (int i = 0; i < str.size(); ++i) {
      if (isdigit(str[i]) || str[i]=='-') {
         string buf = "";
         int k = i;
         while (k < str.size() && str[k] != '+')
            buf += str[k++];

         Monome m(buf);
         terms.push_back(m);
         i = k;
      }
   }
}

Polynome::Polynome(double num) {
   terms.push_back(num);
}

Polynome::Polynome(Monome obj) {
   terms.push_back(obj);
}

Polynome Polynome::operator/(double number) const {
   if (number == 0) throw std::runtime_error("Ошибка деления многочленов");
   Polynome res = *this;
   for (auto &term : res.terms)
      term.coef /= number;

   return res;
}

Polynome Polynome::operator +(const Polynome &obj) const {
   Polynome res = *this;
   bool flg;
   for (auto term : obj.terms) {
      flg=false;
      for (auto &term2 : res.terms) {
         if (term.similar(term2)) { // Если нашелся общий то flg=1 не добавляется в конец
               term2.coef += term.coef;
               flg=true;
               break;
         }
      }
      if(!flg) res.terms.push_back(term);
   }
   // Все мономы нулевых коэффициентов попали внутрь, нужно очистить их

    remove_if(res.terms.begin(), res.terms.end(), [](const Monome& m)
    {
        return fabs(m.coef) < 0.00001;
    });

   return res;
}

Polynome Polynome::operator -(const Polynome &obj) const {
   Polynome res = *this;
   return res + obj*(-1.);
}

Polynome Polynome::operator*(const Polynome &obj) const {
   Polynome result;

   for (auto it1 : this->terms) {
      for (auto it2 : obj.terms) {
         result = result + (it1 * it2);
      }
   }
   return result;
}

ostream &operator<<(std::ostream &out, const Polynome &obj) {
    for (auto term : obj.terms)
        out << term;
    return out;
}

std::vector<char> Polynome::print_variables(){
   std::vector<char> v = {' '};
   for (auto term: terms){
      for (auto it : term.pows) {
         if (*std::find(v.begin(), v.end(), it.first) != it.first){
            v.push_back(it.first);
         }
      }
   }
   return v;
}

Polynome Polynome::derivative(char c)
{
    Polynome p = *this;
    for(auto &it : p.terms)
    {
        it.differentiate(c);
    }

    remove_if(terms.begin(), terms.end(), [](const Monome& m)
    {
        return fabs(m.coef) < 0.00001;
    });

    return p;
}

double Polynome::count_for(std::map<char, double> &mp){
    double allsum = 0;
    for (auto term: terms)
    {
        double msum = term.coef;
        for (auto it : term.pows) {
            msum *= std::pow(mp[it.first], it.second);
        }

        allsum += msum;
    }
    return allsum;
}
