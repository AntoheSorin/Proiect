#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Paranteze.h"
#include "Numar.h"
#include <vector>
#include <stack>

class Calculator {
private:
    std::vector<Numar> numere;
    std::vector<Paranteze> paranteze;
    std::stack<Numar> stiva_numere;
    std::stack<Paranteze> stiva_paranteze;

    static const Paranteze PARANTEZE_ROTUNDE;
    static const Paranteze PARANTEZE_PATRATICE;

    bool esteOperator(char c) const;
    void gestioneazaNumar(const std::string& expresie, int& i);
    void gestioneazaOperator(const std::string& expresie, int& i);
    void gestioneazaParanteza(const std::string& expresie, int& i);
    int getPrecedentaParanteza(char c) const;
    int getPrecedentaOperator(char c) const;
    std::string convertInfixToPostfix(const std::string& infix);

public:
    Calculator();
    Numar calculeazaExpresie(const std::string& expresie);
    void saveResultToFile(const std::string& filename);
    void loadEquationsFromFile(const std::string& filename);
    void printMenu();
};

#endif 
