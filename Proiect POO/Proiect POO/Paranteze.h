#pragma once

#include <iostream>

class Paranteze {
private:
    char deschidere_caracter;
    char inchidere_caracter;
    int precedenta;

public:
    Paranteze(char deschide, char inchide, int p);

    char getDeschidereCaracter() const;
    char getInchidereCaracter() const;
    int getPrecedenta() const;

    friend std::ostream& operator<<(std::ostream& os, const Paranteze& paranteze);
};
