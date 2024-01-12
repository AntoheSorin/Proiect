#pragma once

#include "Numar.h"
#include "Paranteze.h"
#include <vector>
#include <stack>
#include <cctype>
#include <stdexcept>


class Calculator {
private:
    std::vector<Numar> numere;
    std::vector<Paranteze> paranteze;
    std::stack<Numar> stiva_numere;
    std::stack<Paranteze> stiva_paranteze;

    static const Paranteze PARANTEZE_ROTUNDE;
    static const Paranteze PARANTEZE_PATRATICE;

    bool esteOperator(char c) const;
    bool esteDeschidereParanteza(char c) const;
    bool esteInchidereParanteza(char c) const;

    int getPrecedentaParanteza(char c) const;

    int getPrecedentaOperator(char c) const;

    void gestioneazaNumar(const std::string& expresie, int& i);

    void gestioneazaOperator(const std::string& expresie, int& i);

public:
    Calculator();

    Numar calculeazaExpresie(const std::string& expresie);
};
