#include "io.hpp"


void IO::update_best_solution(Solution *new_best_solution) {
    delete this->now_solution;
    delete this->best_solution;

    this->now_solution = new_best_solution->copy_solution();
    this->best_solution = new_best_solution;
}

void IO::main_cycle() {
    uint32_t best_count = 0;
    for(;;) {
        this->temp_law->decrease_temp(this->iterations);
        if (this->temp_law->temp <= 0.00000001) {
            std::cout << "TEMP BREAK" << std::endl;
            break;
        }
        for (uint32_t i = 0; i < 10; i++) {
            auto new_evaluation = this->mut_law->mut_solution(this->now_solution, this->temp_law);
        
            if (new_evaluation < this->best_solution->evaluate()) {
                delete this->best_solution;
                this->best_solution = this->now_solution->copy_solution();
                best_count = 0;
            } else {
                best_count += 1;
            }

            if (best_count >= 100) {
                break;
            }
        }
        if (best_count >= 100) {
            break;
        }
        this->iterations += 1;
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
    delete temp_law;
    delete now_solution;
}
