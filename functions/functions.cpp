#include "functions.h"

const double P = acos(-1.0);
const double inaccuracy = sin(P); //Выявление погрешности для дальнейшего использования
// (это число должно быть 0, но ввиду ограниченности компьютера оно чуть-чуть больше 0, собственно, это и есть наша погрешность)

struct Token { //Структура для хранения данных в стеке
    char type;  //Информация о типе: 0 - число, символы операций - сами операции
    double value; //Информация о значении: 0 - операция, число - само число
};

bool calculation(std::stack <Token>& Numbers, std::stack <Token>& Operations, Token& item) { //Функция подсчёта
    double a = Numbers.top().value; //Берём первый символ в стеке
    double b;
    Numbers.pop(); //И сразу удаляем его из стека

    switch (Operations.top().type) { //В зависимости от верхнего символа в стеке с операциями делаем следующее
        case '+':
            b = Numbers.top().value; //Берём следующее число из стека с числами и удаляем его сразу же
            Numbers.pop();
            item.type = '0';  //Используем нашу буферную переменную по назначению
            item.value = a + b; //Плюсуем
            Numbers.push(item); //Кидаем в стек полученный результат
            break;
        case '-':  //Делаем так для всех операций
            b = Numbers.top().value;
            Numbers.pop();
            item.type = '0';
            item.value = b - a; //Изменён порядок т.к. в стеке они хранятся в обратном порядке
            Numbers.push(item);
            break;
        case '*':
            b = Numbers.top().value;
            Numbers.pop();
            item.type = '0';
            item.value = a * b;
            Numbers.push(item);
            break;
        case '/':
            b = Numbers.top().value;
            Numbers.pop();
            if (a == 0) { //Проверка на деление на 0
                std::cerr << "\nError! Divided by zero!\n";
                return false; //Возвращаем "ложь" т.к. ошибка
            }
            item.type = '0';
            item.value = b / a; //Т.к. в стеке переменные хранятся в обратном от ввода порядке, что меняем местами
            Numbers.push(item);
            break;
        case '^':
            b = Numbers.top().value;
            Numbers.pop();
            item.type = '0';
            item.value = pow(b,a);
            Numbers.push(item);
            break;
        case 's':
            item.type = '0';
            if (sin(a) > -inaccuracy && sin(a) < inaccuracy) {
                item.value = 0;
            } else item.value = sin(a);
            Numbers.push(item);
            break;
        case 'c':
            item.type = '0';
            if (cos(a) > -inaccuracy && cos(a) < inaccuracy) {
                item.value = 0;
            } else item.value = cos(a);
            Numbers.push(item);
            break;
        case 't':
            if (cos(a) > -inaccuracy && cos(a) < inaccuracy) { //Проверка на деление на 0
                std::cerr << "\nError! Invalid tan argument!\n";
                return false; //Возвращаем "ложь" т.к. ошибка
            }
            item.type = '0';
            item.value = tan(a);
            Numbers.push(item);
            break;
        case 'g':
            if (sin(a) > -inaccuracy && sin(a) < inaccuracy) { //Проверка на деление на 0
                std::cerr << "\nError! Invalid ctg argument!\n";
                return false; //Возвращаем "ложь" т.к. ошибка
            }
            item.type = '0';
            item.value = 1 / tan(a);
            Numbers.push(item);
            break;
        case 'e':
            item.type = '0';
            item.value = exp(a);
            Numbers.push(item);
            break;
        case 'S':
            item.type = '0';
            item.value = asin(a);
            Numbers.push(item);
            break;
        case 'C':
            item.type = '0';
            item.value = acos(a);
            Numbers.push(item);
            break;
        case 'T':
            item.type = '0';
            item.value = atan(a);
            Numbers.push(item);
            break;
        case 'G':
            item.type = '0';
            item.value = (P/2) - atan(a);
            Numbers.push(item);
            break;
        default:  //Если операция не определена, то выводим ошибку
            std::cerr << "\nUnknown operation!\n";
            return false; //Возвращаем "ложь" т.к. ошибка
    }
    Operations.pop(); //Удаляем использованный символ операции из стека с операциями
    return true; //Всё прошло успешно, возвращаем "истина"
}

int getRank(char operation) { //Функция для получения ранга(приоритета) операции
    switch (operation) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case 's':
        case 'c':
        case 't':
        case 'g':
        case 'e':
        case 'S':
        case 'C':
        case 'T':
        case 'G':
            return 4;
        default:
            return 0;
    }
}

int Calculator () {
    bool isMinus = true; //Для случая, если первое число отрицательное
    char Symbol; //Символ чтения
    Token item; //Буферная переменная для закидывания в стек

    std::stack <Token> Numbers;    // Стек для чисел
    std::stack <Token> Operations; // Стек для операций


    std::cout << "Enter the expression: ";
    std::cin.get();

    while(true) {

        Symbol = std::cin.peek();    // Смотрим следующий в очереди символ
        if (Symbol == '\n') break;
        if (Symbol == ' ') {
            std::cin.ignore();
            continue;
        }
        if (Symbol == 's' || Symbol == 'c' || Symbol == 't' || Symbol == 'e') {
            char foo[3];
            for (int i = 0; i < 3; i++) {
                Symbol = std::cin.peek();
                foo[i] = Symbol;
                std::cin.ignore();
            }

            if (foo[0] == 's' && foo[1] == 'i' && foo[2] == 'n') {
                item.type = 's';
                item.value = 0;
                Operations.push(item);
                continue;
            }
            if (foo[0] == 'c' && foo[1] == 'o' && foo[2] == 's') {
                item.type = 'c';
                item.value = 0;
                Operations.push(item);
                continue;
            }
            if (foo[0] == 't' && foo[1] == 'a' && foo[2] == 'n') {
                item.type = 't';
                item.value = 0;
                Operations.push(item);
                continue;
            }
            if (foo[0] == 'c' && foo[1] == 't' && foo[2] == 'g') {
                item.type = 'g';
                item.value = 0;
                Operations.push(item);
                continue;
            }
            if (foo[0] == 'e' && foo[1] == 'x' && foo[2] == 'p') {
                item.type = 'e';
                item.value = 0;
                Operations.push(item);
                continue;
            }
        }

        if (Symbol == 'a') {
            char foo[4];
            for (int i = 0; i < 4; i++) {
                Symbol = std::cin.peek();
                foo[i] = Symbol;
                std::cin.ignore();
            }
            if (foo[0] == 'a' && foo[1] == 's' && foo[2] == 'i' && foo[3] == 'n') {
                item.type = 'S';
                item.value = 0;
                Operations.push(item);
                continue;
            }
            if (foo[0] == 'a' && foo[1] == 'c' && foo[2] == 'o' && foo[3] == 's') {
                item.type = 'C';
                item.value = 0;
                Operations.push(item);
                continue;
            }
            if (foo[0] == 'a' && foo[1] == 't' && foo[2] == 'a' && foo[3] == 'n') {
                item.type = 'T';
                item.value = 0;
                Operations.push(item);
                continue;
            }
            if (foo[0] == 'a' && foo[1] == 'c' && foo[2] == 't' && foo[3] == 'g') {
                item.type = 'G';
                item.value = 0;
                Operations.push(item);
                continue;
            }
        }

        if (Symbol >= '0' && Symbol <= '9' || Symbol == '-' && isMinus) { //Если число, то кидаем в стек с числами
            std::cin >> item.value;  //Читаем число полностью
            item.type = 0;
            Numbers.push(item);
            isMinus = 0;
            continue;
        } else if (Symbol == '+' || Symbol == '-' && !isMinus || Symbol == '*' || Symbol == '/' || Symbol == '^') { // Если операция кидаем в стек с операциями
            if (Operations.empty() ) { //Если в стеке нет операций, то кидаем наверх
                item.type = Symbol;
                item.value = 0;
                Operations.push(item);
                std::cin.ignore(); //Пропускаем этот символ, т.к. уже использовали его
                continue;
            } else if (!Operations.empty() && getRank(Symbol) > getRank(Operations.top().type)) { //Если есть операции, но ранг нынешнего символа больше, то кидаем наверх
                item.type = Symbol;
                item.value = 0;
                Operations.push(item);
                std::cin.ignore();
                continue;
            } else if (!Operations.empty() && getRank(Symbol) <= getRank(Operations.top().type)) { //Если есть операции, но ранг нынешнего символа меньше или равен рангу символа в стеке
                if (!calculation(Numbers, Operations, item)) { // То вызываем функцию для подсчёта
                    system("pause>0");
                    return 1;
                }
                continue;
            }
        } else if (Symbol == '(') {
            item.type = Symbol;
            item.value = 0;
            Operations.push(item);
            std::cin.ignore();
            continue;
        } else if (Symbol == ')') {
            while(Operations.top().type != '(') {
                if (!calculation(Numbers, Operations, item)) {
                    system("pause>0");
                    return 1;
                }
            }
            Operations.pop();
            std::cin.ignore();
            continue;
        }

        if (Symbol == 'P') { //Если PI, то кидаем в стек с числами
            item.type = 0;
            item.value = P;
            Numbers.push(item);
            isMinus = false;
            std::cin.ignore();
            continue;
        }

        // Если символ не число и не операция, то выводим ошибку
        std::cerr << "\nUnknown symbol!\n";
        system("pause>0");
        return 2;

    }

    while (Numbers.size() != 1 || !Operations.empty()) { //Производим вычисления в стеках, пока в стеке с числами не останется только ответ
        if (!calculation(Numbers, Operations, item)) {
            system("pause>0");
            return 1;
        }
    }

    std::cout << "\nAnswer: " << Numbers.top().value << "\n\n";
    system("pause>0");
    return 0;
};