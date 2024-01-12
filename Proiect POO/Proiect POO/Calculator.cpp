#include "Calculator.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream> // Adăugat pentru std::ofstream și std::ifstream

const Paranteze Calculator::PARANTEZE_ROTUNDE = Paranteze('(', ')', 0);
const Paranteze Calculator::PARANTEZE_PATRATICE = Paranteze('[', ']', 0);

bool Calculator::esteOperator(char c) const {
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

void Calculator::gestioneazaNumar(const std::string& expresie, int& i) {
    int j = i;
    while (j < expresie.length() && (std::isdigit(expresie[j]) || expresie[j] == '.')) {
        j++;
    }
    if (j > i) {
        Numar number(std::stod(expresie.substr(i, j - i)));
        numere.push_back(number);
        i = j;
    }
}

void Calculator::gestioneazaOperator(const std::string& expresie, int& i) {
    if (i == 0 || expresie[i - 1] == ' ') {
        throw std::invalid_argument("Operator invalid");
    }

    char c = expresie[i];
    if (!esteOperator(c)) {
        throw std::invalid_argument("Operator invalid");
    }

    while (!stiva_paranteze.empty() && getPrecedentaParanteza(stiva_paranteze.top().getInchidereCaracter()) >= getPrecedentaOperator(c)) {
        stiva_numere.push(numere.back());
        numere.pop_back();
        stiva_paranteze.pop();
    }

    stiva_paranteze.push(Paranteze(' ', ' ', getPrecedentaOperator(c)));
    i++;
}

void Calculator::gestioneazaParanteza(const std::string& expresie, int& i) {
    char c = expresie[i];
    if (c == '(' || c == '[') {
        stiva_paranteze.push(Paranteze(c, ' ', getPrecedentaParanteza(c)));
    }
    else if (c == ')' || c == ']') {
        while (!stiva_paranteze.empty() && stiva_paranteze.top().getDeschidereCaracter() != '(' && stiva_paranteze.top().getDeschidereCaracter() != '[') {
            stiva_numere.push(numere.back());
            numere.pop_back();
            stiva_paranteze.pop();
        }

        if (stiva_paranteze.empty() || stiva_paranteze.top().getDeschidereCaracter() != (c == ')' ? '(' : '[')) {
            throw std::invalid_argument("Paranteze neasociate");
        }

        stiva_paranteze.pop();
    }

    i++;
}

int Calculator::getPrecedentaParanteza(char c) const {
    if (c == PARANTEZE_ROTUNDE.getDeschidereCaracter()) {
        return 1;
    }
    else if (c == PARANTEZE_PATRATICE.getDeschidereCaracter()) {
        return 2;
    }
    else {
        throw std::invalid_argument("Paranteza invalida");
    }
}

int Calculator::getPrecedentaOperator(char c) const {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    throw std::invalid_argument("Operator invalid");
}

std::string Calculator::convertInfixToPostfix(const std::string& infix) {
    std::string postfix;
    std::stack<Paranteze> stiva_paranteze;

    for (int i = 0; i < infix.length(); i++) {
        if (std::isdigit(infix[i]) || infix[i] == '.') {
            postfix += infix[i];
        }
        else if (esteOperator(infix[i])) {
            while (!stiva_paranteze.empty() && stiva_paranteze.top().getPrecedenta() >= getPrecedentaOperator(infix[i])) {
                postfix += stiva_paranteze.top().getInchidereCaracter();
                stiva_paranteze.pop();
            }

            stiva_paranteze.push(Paranteze(' ', ' ', getPrecedentaOperator(infix[i])));
        }
        else if (infix[i] == '(' || infix[i] == '[') {
            stiva_paranteze.push(Paranteze(infix[i], ' ', getPrecedentaParanteza(infix[i])));
        }
        else if (infix[i] == ')' || infix[i] == ']') {
            while (!stiva_paranteze.empty() && stiva_paranteze.top().getDeschidereCaracter() != (infix[i] == ')' ? '(' : '[')) {
                postfix += stiva_paranteze.top().getInchidereCaracter();
                stiva_paranteze.pop();
            }

            if (!stiva_paranteze.empty() && stiva_paranteze.top().getDeschidereCaracter() == (infix[i] == ')' ? '(' : '[')) {
                stiva_paranteze.pop();
            }
        }
        else if (infix[i] == ' ') {
            continue;
        }
        else {
            throw std::invalid_argument("Caracter invalid");
        }
    }

    while (!stiva_paranteze.empty()) {
        postfix += stiva_paranteze.top().getInchidereCaracter();
        stiva_paranteze.pop();
    }

    return postfix;
}

Calculator::Calculator() {}

Numar Calculator::calculeazaExpresie(const std::string& expresie) {
    std::string postfix = convertInfixToPostfix(expresie);

    for (int i = 0; i < postfix.length(); i++) {
        if (std::isdigit(postfix[i]) || postfix[i] == '.') {
            Numar number(std::stod(postfix.substr(i, 1)));
            stiva_numere.push(number);
            i++;
        }
        else if (esteOperator(postfix[i])) {
            Numar operand2 = stiva_numere.top();
            stiva_numere.pop();

            Numar operand1 = stiva_numere.top();
            stiva_numere.pop();

            switch (postfix[i]) {
            case '+':
                stiva_numere.push(operand1 + operand2);
                break;
            case '-':
                stiva_numere.push(operand1 - operand2);
                break;
            case '*':
                stiva_numere.push(operand1 * operand2);
                break;
            case '/':
                stiva_numere.push(operand1 / operand2);
                break;
            default:
                throw std::invalid_argument("Operator nevalid");
            }
        }
    }

    return stiva_numere.top();
}

void Calculator::saveResultToFile(const std::string& filename) {
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului " << filename << std::endl;
        return;
    }

    ofs << stiva_numere.top() << std::endl;
}

void Calculator::loadEquationsFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        Numar num;
        iss >> num;

        if (iss.fail()) {
            std::cerr << "Eroare la parsarea liniei " << line << std::endl;
            continue;
        }

        numere.push_back(num);
    }
}

void Calculator::printMenu() {
    std::cout << "Calculator Menu:\n";
    std::cout << "1. Introducere expresie\n";
    std::cout << "2. Salveaza rezultat curent\n";
    std::cout << "3. Citeste ecuații din fișier\n";
    std::cout << "4. Iesire\n";
    std::cout << "Introduceti optiunea dvs: ";
}
