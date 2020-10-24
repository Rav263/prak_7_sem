#include <iostream>
#include <vector>

#include "temperature.hpp"

int main() {
    std::vector<Temp *> temps= {new TempFirst(9), new TempSecond(9), new TempThird(9)};

    for (auto now : temps) {
        now->decrease_temp();
    }

    for (auto now : temps) {
        std::cout << now->temp << " ";
    }

    std::cout << std::endl;

    for (auto now : temps) {
        delete now;
    }
}
