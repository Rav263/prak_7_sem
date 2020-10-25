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

    for (uint32_t index; index < this->work_flow.size(); index++) {
        auto next_links = this->work_flow[index]->get_next_links();
        auto now_problem = new_solution->get_problem(index);
        
        for (auto next_link : *next_links) {
            now_problem->add_next_link(new_solution->get_problem(next_link->get_index()));
        }
    }

    return new_solution;
}

void BigSolution::print_solution() {
    for (auto now_problem : this->work_flow) {
        std::cout << "Problem: " << now_problem->get_index() 
            << " proc index: " << now_problem->get_proc_index() << std::endl;

        auto next_links = now_problem->get_next_links();

        for (auto next_link : *next_links) {
            std::cout << next_link->get_index() << " ";
        }
        std::cout << std::endl;
    }
}
