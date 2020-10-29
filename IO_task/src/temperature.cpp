#include <iostream>
#include <cmath>

#include "temperature.hpp"

void TempFirst::decrease_temp(uint32_t iteration) {
    this->temp = this->init_temp / (1.0 + iteration);
}

void TempSecond::decrease_temp(uint32_t iteration) {
    this->temp = this->init_temp / log(1.0 + iteration);

}

void TempThird::decrease_temp(uint32_t iteration) {
    this->temp = this->init_temp * log(1.0 + iteration) / (1.0 + iteration);
}
