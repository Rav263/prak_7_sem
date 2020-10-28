#include <iostream>

#include "solution.hpp"


void BigSolution::add_new_problem(Problem *problem) {
    this->problems[problem->get_index()] = problem;
    this->procs[problem->get_index()] = problem->get_proc_index();
}


Solution *BigSolution::copy_solution() {
    BigSolution *new_solution = new BigSolution(this->num_procs, this->num_problems);

    new_solution->procs = this->procs;
    
    for (auto old_problem : this->problems) {
        new_solution->problems[old_problem->get_index()] = old_problem->copy_problem();
    }

    return new_solution;
}


void BigSolution::print_solution() {
    for (auto now_problem : this->problems) {
        std::cout << "Problem: " << now_problem->get_index() 
            << " proc index: " << now_problem->get_proc_index() << std::endl;
    }

    std::cout << "EVALUATION: " << this->evaluate() << std::endl;
}


void BigSolution::change_problem_proc_index(uint32_t problem_index, uint32_t proc_index) {
    if (problem_index >= this->num_problems) {
        std::cerr << "BAD PROBLEM INDEX: " << problem_index 
            << "/" << this->num_problems << std::endl;
    }

    if (proc_index >= this->num_procs) {
        std::cerr << "BAD PROBLEM INDEX: " << proc_index 
            << "/" << this->num_procs << std::endl; 
    }
    problems[problem_index]->change_proc_index(proc_index);
    procs[problem_index] = proc_index;
    this->evaluation = -1;
}


// Maybe it's needed to add start and end time for each problem
// Becouse maybe i'll need calculate pauses in procs work.

double BigSolution::evaluate() {
    if (this->evaluation != -1) {
        return this->evaluation;
    }
    std::vector<double> times(this->num_procs);

    for (auto now_problem : problems) {
        times[now_problem->get_proc_index()] += now_problem->get_work_time();
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

    this->evaluation = max_time - min_time;

    return evaluation;
}


uint32_t BigSolution::get_problems_num() {
    return this->num_problems;
}


uint32_t BigSolution::get_procs_num() {
    return this->num_procs;
}


uint32_t BigSolution::get_problem_proc_index(uint32_t problem_index) {
    return this->procs[problem_index];
}
