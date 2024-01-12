#ifndef PARANTEZE_H
#define PARANTEZE_H

#include <iostream>

class Paranteze {
private:
    char deschidere_caracter;
    char inchidere_caracter;
    int precedenta;

public:
    Paranteze(char deschidere, char inchidere, int precedenta);
    char getDeschidereCaracter() const;
    char getInchidereCaracter() const;
    int getPrecedenta() const;

    friend std::ostream& operator<<(std::ostream& os, const Paranteze& paranteze);
};

#endif 
