#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#define NPOP 100

#include "mutate.hpp"
#include "crossbreeding.hpp"
#include "selection.hpp"
#include "configuration.hpp"

class GeneticAlgorithm {
    MutationPtr mutation;
    SelectionPtr selection;
    CrossbreedingPtr crossbreeding;
    ConfigPtr best_configuration = nullptr;
    int32_t best_eval = 0;
    std::vector<ConfigPtr> population;

public:
    GeneticAlgorithm(MutationPtr mutation, SelectionPtr selection, CrossbreedingPtr crossbreeding) {
        this->mutation = mutation;
        this->selection = selection;
        this->crossbreeding = crossbreeding;
        
        for (uint32_t i = 0; i < NPOP; i++) {
            ConfigPtr now_configuration = std::make_shared<Config>();
            fill_field(now_configuration);
            this->population.push_back(now_configuration);
        }
    }

    void main_cycle();
    void process_population();
    std::pair<ConfigPtr, int32_t> evaluate_population();
};

#endif
