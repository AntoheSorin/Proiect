#include <iostream>
#include <sstream>
#include "Calculator.h"

int main() {
    Calculator calculator;
    std::string expresie;

    
    while (true) {
       
        std::cout << "Introduceti ecuatia sau tastati 'exit' pentru a iesi: ";
        std::getline(std::cin, expresie);

        
        if (expresie == "exit") {
            std::cout << "La revedere!\n";
            break;  
        }

       
        try {
            Numar rezultat = calculator.calculeazaExpresie(expresie);
            std::cout << "Rezultatul expresiei este: " << rezultat << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
        }
    }

    return 0;
}
