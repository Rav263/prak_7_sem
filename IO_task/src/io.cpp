#include "io.hpp"

void IO::main_cycle() {
    uint32_t best_count = 0;
    for(;;) {
        this->iterations += 1;
        auto new_evaluation = this->mut_law->mut_solution(this->now_solution, this->temp_law);
        
        if (new_evaluation < this->best_solution->evaluate()) {
            delete this->best_solution;
            this->best_solution = this->now_solution->copy_solution();
            best_count = 0;
        } else {
            best_count += 1;
        }

        if (best_count == 100) {
            break;
        }
    }
}

Solution* IO::get_best_solution() {
    return this->best_solution;
}

uint64_t IO::get_iterations() {
    return this->iterations;
}

IO::~IO() {
    delete best_solution;
}
