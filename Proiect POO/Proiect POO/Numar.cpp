#include "Numar.h"
#include <iostream>

Numar::Numar() : este_intreg(true), valoare(0) {}

Numar::Numar(int i) : este_intreg(true), valoare(i) {}

Numar::Numar(double d) : este_intreg(false), valoare(d) {}

bool Numar::esteIntreg() const {
    return este_intreg;
}

double Numar::getValoare() const {
    return valoare;
}

void Numar::seteazaValoare(double d) {
    valoare = d;
    este_intreg = (d - (int)d) == 0;
}

Numar Numar::operator+(const Numar& altul) const {
    return Numar(valoare + altul.valoare);
}

Numar Numar::operator-(const Numar& altul) const {
    return Numar(valoare - altul.valoare);
}

Numar Numar::operator*(const Numar& altul) const {
    return Numar(valoare * altul.valoare);
}

Numar Numar::operator/(const Numar& altul) const {
    if (altul.valoare == 0) {
        std::cerr << "Eroare: Impartire la zero" << std::endl;
        exit(1);
    }
    return Numar(valoare / altul.valoare);
}

std::ostream& operator<<(std::ostream& os, const Numar& numar) {
    if (numar.este_intreg) {
        os << (int)numar.valoare;
    }
    else {
        os << numar.valoare;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Numar& numar) {
    double d;
    is >> d;
    numar.seteazaValoare(d);
    return is;
}
