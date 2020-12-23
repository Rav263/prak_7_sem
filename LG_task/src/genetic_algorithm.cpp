#include "genetic_algorithm.hpp"
#include "configuration.hpp"
#include <iostream>


void GeneticAlgorithm::main_cycle() {
    uint32_t iter = 0;

    while (iter < 20) {
        this->process_population();
        
        std::vector<std::pair<ConfigPtr, int32_t>> evaled_pop;
        auto best = evaluate_population(evaled_pop); 

        auto best_evaled = evaled_pop[best];

        if (best_evaled.second > this->best_eval) {
            this->best_eval = best_evaled.second;
            this->best_configuration = std::make_shared<Config>(*best_evaled.first);
            iter = 0;
            this->master += 1;
        } else {
            iter += 1;
            this->master += 1;
        }
        
        auto new_population = this->selection->select(evaled_pop);
        this->crossbreeding->crossbreed(new_population);
        this->mutation->mutate(new_population);
        this->population = new_population;
    }
}

void GeneticAlgorithm::process_population() {
    for (auto config : this->population) {
        create_generation(config);
    }
}

uint32_t GeneticAlgorithm::evaluate_population(std::vector<std::pair<ConfigPtr, int32_t>> &evaled_pop) {
    uint32_t best = 0;

    for (auto config : population) {
        auto eval = evaluate_configuration(config);
        evaled_pop.push_back({config, eval});

        if (eval >= evaled_pop[best].second) {
            best = evaled_pop.size() - 1;
        }
    }

    return best;
}
