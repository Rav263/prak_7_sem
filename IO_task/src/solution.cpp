#include <iostream>

#include "solution.hpp"


void BigSolution::add_new_problem(Problem *problem) {
    if (this->num_procs < problem->get_proc_index()) {
        std::cerr << "ERROR BAD PROBLEM PROC INDEX" << std::endl;
    }
    work_flow.push_back(problem);
}

