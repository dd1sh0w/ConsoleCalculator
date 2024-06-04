#ifndef CONSOLECALCULATOR_FUNCTIONS_H
#define CONSOLECALCULATOR_FUNCTIONS_H

#include <iostream>
#include <stack>
#include <cmath>

struct Leksema;

bool calculation(std::stack <Leksema>& Numbers, std::stack <Leksema>& Operations, Leksema& item);

int getRank(char operation);

int Calculator ();

#endif //CONSOLECALCULATOR_FUNCTIONS_H
