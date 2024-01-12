#include "Calculator.h"
#include <string>

int main(int argc, char* argv[]) {
    Calculator calculator;
    int opt;
    std::string filename;

    do {
        calculator.printMenu();
        std::cin >> opt;

        switch (opt) {
        case 1: {
            std::string expresie;
            std::cout << "Introduceti expresia matematica: ";
            std::getline(std::cin, expresie);

            try {
                Numar rezultat = calculator.calculeazaExpresie(expresie);
                std::cout << "Rezultatul este: " << rezultat << std::endl;
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Eroare: " << e.what() << std::endl;
            }
            break;
        }
        case 2: {
            std::cout << "Introduceti numele fisierului: ";
            std::cin >> filename;
            calculator.saveResultToFile(filename);
            break;
        }
        case 3: {
            std::cout << "Introduceti numele fisierului: ";
            std::cin >> filename;
            calculator.loadEquationsFromFile(filename);
            break;
        }
        case 4:
            break;
        default:
            std::cout << "Optiune invalida. Reincercati." << std::endl;
        }
    } while (opt != 4);

    return 0;
}
