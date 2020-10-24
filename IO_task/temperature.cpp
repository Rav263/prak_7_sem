#include <iostream>

#include "temperature.hpp"

void TempFirst::decrease_temp() {
    this->temp -= 1;
}

void TempSecond::decrease_temp() {
    this->temp -= 3;
}

void TempThird::decrease_temp() {
    this->temp /= 2;
}
