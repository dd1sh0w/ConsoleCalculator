#include "functions/functions.h"


int main() {
    int error;

    system("cls");
    std::cout << "Hi, it's a calculator with priority! You can use next symbols:\nsin()\ncos()\ntan()\nctg()\nasin()\nacos()\natan()\nactg()\nP\nexp()\n\n";

    do {
        error = Calculator();
    } while (error == 0);

    return error;
}
