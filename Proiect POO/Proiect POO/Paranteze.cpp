#include "Paranteze.h"

Paranteze::Paranteze(char deschidere, char inchidere, int precedenta)
    : deschidere_caracter(deschidere), inchidere_caracter(inchidere), precedenta(precedenta) {}

char Paranteze::getDeschidereCaracter() const {
    return deschidere_caracter;
}

char Paranteze::getInchidereCaracter() const {
    return inchidere_caracter;
}

int Paranteze::getPrecedenta() const {
    return precedenta;
}

std::ostream& operator<<(std::ostream& os, const Paranteze& paranteze) {
    os << paranteze.deschidere_caracter << paranteze.inchidere_caracter;
    return os;
}
