#include "crossbreeding.hpp"
#include <iostream>

void Crossbreeding::crossbreed(std::vector<ConfigPtr> &population) {
    auto init_size = population.size();
    while (population.size() < this->npop) {
        double prob = (std::rand() % 100) / (100.0);
        if (prob > p_cross) continue;

        uint32_t first_index = std::rand() % init_size;
        uint32_t second_index;
        do {
            second_index = std::rand() % init_size;
        } while (first_index == second_index);


        uint32_t pos = rand() % FIELD_SIZE;
        uint32_t un_pos = FIELD_SIZE - pos;

        Config tmp = (((*population[first_index]) >> un_pos) << un_pos);
        tmp |= (((*population[second_index]) << pos) >> pos);


        population.push_back(std::make_shared<Config>(tmp));
    }
}
