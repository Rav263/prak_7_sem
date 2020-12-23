#include "genetic_algorithm.hpp"
#include "configuration.hpp"

void GeneticAlgorithm::main_cycle() {
    uint32_t iter = 0;

    while (iter < 20) {
        this->process_population();
        auto best = evaluate_population(); 
        
        if (best.second > this->best_eval) {
            this->best_eval = best.second;
            this->best_configuration = best.first;
            iter = 0;
        } else {
            iter += 1;
        }

        this->selection->select(this->population);
        this->crossbreeding->crossbreed(this->population);
        this->mutation->mutate(this->population);
    }
}

void GeneticAlgorithm::process_population() {
    for (auto config : this->population) {
        create_generation(config);
    }
}

std::pair<ConfigPtr, int32_t> GeneticAlgorithm::evaluate_population() {
    int32_t best = 0;
    ConfigPtr best_conf = nullptr;

    for (auto config : population) {
        auto eval = evaluate_configuration(config);

        if (eval > best or best_conf == nullptr) {
            best = eval;
            best_conf = config;
        }
    }

    return {best_conf, best};
}
