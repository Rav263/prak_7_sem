#include <iostream>

#include "solution.hpp"


uint32_t BigSolution::get_last_problem_index() {
    return this->work_flow.size() - 1;
}

void BigSolution::add_new_problem(Problem *problem) {
    if (this->num_procs < problem->get_proc_index()) {
        std::cerr << "ERROR:: BAD PROBLEM PROC INDEX" << std::endl;
        exit(1);
    }
    if (this->get_last_problem_index() != problem->get_index() - 1) {
        std::cerr << "ERROR:: BAD PROBLEM INDEX" << std::endl;
        exit(1);
    }
    this->work_flow.push_back(problem);
}

Problem *BigSolution::get_problem(uint32_t index) {
    return this->work_flow[index];
}

Solution *BigSolution::copy_solution() {
    BigSolution *new_solution = new BigSolution(this->num_procs, this->num_problems);

    for (auto old_problem : this->work_flow) {
        new_solution->add_new_problem(old_problem->copy_problem());
    }

    return new_solution;
}

void BigSolution::print_solution() {
    for (auto now_problem : this->work_flow) {
        std::cout << "Problem: " << now_problem->get_index() 
            << " proc index: " << now_problem->get_proc_index() << std::endl;

    }

    std::cout << "EVALUATION: " << this->evaluate() << std::endl;
}


// Maybe it's needed to add start and end time for each problem
// Becouse maybe i'll need calculate pauses in procs work.

double BigSolution::evaluate() {
    std::vector<double> times(this->num_procs);

    for (auto now_problem : this->work_flow) {
        uint32_t proc_index = now_problem->get_proc_index();
        times[proc_index] += now_problem->get_work_time();
    }

    double min_time = times[0];
    double max_time = times[0];

    for (auto now_time : times) {
        if (now_time < min_time) {
            min_time = now_time;
        }
        if (now_time > max_time) {
            max_time = now_time;
        }
    }

    return max_time - min_time;
}
