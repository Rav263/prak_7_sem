#ifndef IO_HPP
#define IO_HPP

#include "solution.hpp"
#include "mutable.hpp"

class IO {
private:
    Solution *now_solution = nullptr;
    Solution *best_solution = nullptr;
    MutableLaw *mut_law = nullptr;
    Temp *temp_law = nullptr;
    double best_metric;
public:
    IO(Solution *initial_solution, MutableLaw *mut, Temp *temp) :
        now_solution(initial_solution), mut_law(mut), temp_law(temp) {
        this->best_solution = initial_solution->copy_solution();
    }

    void main_cycle();
    Solution *get_best_solution();

    ~IO();
};

#endif //IO_HPP
