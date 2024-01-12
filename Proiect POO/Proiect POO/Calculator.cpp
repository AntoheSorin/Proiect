#include <iostream>
#include <string>
#include <stdexcept>
#include "Calculator.h"
#include "Numar.h"
#include "Paranteze.h"
    
    const Paranteze Calculator::PARANTEZE_ROTUNDE = Paranteze('(', ')', 0);
    const Paranteze Calculator::PARANTEZE_PATRATICE = Paranteze('[', ']', 0);

    bool Calculator::esteOperator(char c) const {
        return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '#');
    }

    bool Calculator::esteDeschidereParanteza(char c) const {
        return (c == PARANTEZE_ROTUNDE.getDeschidereCaracter()) || (c == PARANTEZE_PATRATICE.getDeschidereCaracter());
    }

    bool Calculator::esteInchidereParanteza(char c) const {
        return (c == PARANTEZE_ROTUNDE.getInchidereCaracter()) || (c == PARANTEZE_PATRATICE.getInchidereCaracter());
    }

    int Calculator::getPrecedentaParanteza(char c) const {
        if (esteDeschidereParanteza(c)) {
            return 0;
        }
        else if (c == PARANTEZE_ROTUNDE.getInchidereCaracter()) {
            return 1;
        }
        else if (c == PARANTEZE_PATRATICE.getInchidereCaracter()) {
            return 2;
        }
        else {
            throw std::invalid_argument("Paranteza invalida");
        }
    }

    int Calculator::getPrecedentaOperator(char c) const {
        if (c == '+') return 1;
        if (c == '-') return 1;
        if (c == '*') return 2;
        if (c == '/') return 2;
        if (c == '^') return 3;
        if (c == '#') return 3;
        throw std::invalid_argument("Operator invalid");
    }

    void Calculator::gestioneazaNumar(const std::string & expresie, int& i) {
        int j = i;
        while (j < expresie.length() && std::isdigit(expresie[j])) {
            j++;
        }
        if (j > i) {
            Numar number(std::stod(expresie.substr(i, j - i)));
            numere.push_back(number);
            i = j;
        }
    }

    void Calculator::gestioneazaOperator(const std::string & expresie, int& i) {
        char c = expresie[i];
        if (!esteOperator(c)) {
            throw std::invalid_argument("Operator invalid");
        }

        while (!stiva_paranteze.empty() && getPrecedentaParanteza(stiva_paranteze.top().getInchidereCaracter()) > getPrecedentaOperator(c)) {
            stiva_numere.push(numere.back());
            numere.pop_back();
            stiva_paranteze.pop();
        }

        stiva_paranteze.push(Paranteze(' ', ' ', getPrecedentaOperator(c)));
        i++;
    }

    Numar Calculator::calculeazaExpresie(const std::string& expresie) {
        numere.clear();
        paranteze.clear();
        stiva_numere = std::stack<Numar>();
        stiva_paranteze = std::stack<Paranteze>();

        int i = 0;
        while (i < expresie.length()) {
            if (std::isspace(expresie[i])) {
                i++;
            }
            else if (std::isdigit(expresie[i])) {
                gestioneazaNumar(expresie, i);
            }
            else if (esteOperator(expresie[i])) {
                gestioneazaOperator(expresie, i);
            }
            else if (esteDeschidereParanteza(expresie[i])) {
                stiva_paranteze.push(Paranteze(expresie[i], ' ', getPrecedentaParanteza(expresie[i])));
                i++;
            }
            else if (esteInchidereParanteza(expresie[i])) {
                while (!stiva_paranteze.empty() && !esteDeschidereParanteza(stiva_paranteze.top().getDeschidereCaracter())) {
                    stiva_numere.push(numere.back());
                    numere.pop_back();
                    stiva_paranteze.pop();
                }

                if (stiva_paranteze.empty() || stiva_paranteze.top().getDeschidereCaracter() != expresie[i]) {
                    throw std::invalid_argument("Paranteze neasociate");
                }

                stiva_paranteze.pop();
                i++;
            }
            else {
                throw std::invalid_argument("Caracter nevalid in expresie");
            }
        }

        while (!stiva_paranteze.empty()) {
            if (esteDeschidereParanteza(stiva_paranteze.top().getDeschidereCaracter())) {
                throw std::invalid_argument("Paranteze neinchise");
            }

            stiva_numere.push(numere.back());
            numere.pop_back();
            stiva_paranteze.pop();
        }

        while (!stiva_numere.empty()) {
            numere.push_back(stiva_numere.top());
            stiva_numere.pop();
        }

        std::stack<Numar> rezultat;
        std::stack<char> operatori;

        for (const Numar& numar : numere) {
            if (numar.esteIntreg()) {
                rezultat.push(numar);
            }
            else {
                while (!operatori.empty() && getPrecedentaOperator(operatori.top()) >= numar.getValoare()) {
                    Numar operand2 = rezultat.top();
                    rezultat.pop();

                    Numar operand1 = rezultat.top();
                    rezultat.pop();

                    char op = operatori.top();
                    operatori.pop();

                    switch (op) {
                    case '+':
                        rezultat.push(operand1 + operand2);
                        break;
                    case '-':
                        rezultat.push(operand1 - operand2);
                        break;
                    case '*':
                        rezultat.push(operand1 * operand2);
                        break;
                    case '/':
                        rezultat.push(operand1 / operand2);
                        break;
                    default:
                        throw std::invalid_argument("Operator nevalid");
                    }
                }

                operatori.push((char)numar.getValoare());
            }
        }

        while (!operatori.empty()) {
            Numar operand2 = rezultat.top();
            rezultat.pop();

            Numar operand1 = rezultat.top();
            rezultat.pop();

            char op = operatori.top();
            operatori.pop();

            switch (op) {
            case '+':
                rezultat.push(operand1 + operand2);
                break;
            case '-':
                rezultat.push(operand1 - operand2);
                break;
            case '*':
                rezultat.push(operand1 * operand2);
                break;
            case '/':
                rezultat.push(operand1 / operand2);
                break;
            default:
                throw std::invalid_argument("Operator nevalid");
            }
        }

        return rezultat.top();
    }

