#ifndef NUMAR_H
#define NUMAR_H

#include <iostream>

class Numar {
private:
    bool este_intreg;
    double valoare;

public:
    Numar();
    Numar(int i);
    Numar(double d);

    bool esteIntreg() const;
    double getValoare() const;
    void seteazaValoare(double d);

    Numar operator+(const Numar& altul) const;
    Numar operator-(const Numar& altul) const;
    Numar operator*(const Numar& altul) const;
    Numar operator/(const Numar& altul) const;

    friend std::ostream& operator<<(std::ostream& os, const Numar& numar);
    friend std::istream& operator>>(std::istream& is, Numar& numar);
};

#endif 
