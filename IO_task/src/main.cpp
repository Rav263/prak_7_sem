#include <iostream>
#include <vector>

#include "temperature.hpp"
#include "solution.hpp"

int main() {
    uint32_t num_of_procs = 1, num_of_problems = 0;

    std::cout << "Enter num of procs: ";
    std::cin >> num_of_procs;

    std::cout << "Enter num of problems: ";
    std::cin >> num_of_problems;

    BigSolution *init_solution = new BigSolution(num_of_procs, num_of_problems);

    for (uint32_t i = 0; i < num_of_problems; i++) {
        Problem *now = new Problem(2.0, 1, i);

        init_solution->add_new_problem(now);
    }

    Solution *solution = init_solution;
    solution->get_problem(0)->add_next_link(solution->get_problem(1));
    
    std::cout << "INIT SOLUTION: " << std::endl;
    solution->print_solution();
    
    Solution *new_solution = solution->copy_solution();
    new_solution->get_problem(1)->change_proc_index(2);
    
    std::cout << std::endl << "AFTER CHANGE INIT SOLUTION" << std::endl;
    solution->print_solution();
    
    std::cout << std::endl << "NEW SOLUTION" << std::endl;
    new_solution->print_solution();

    delete solution;
    std::cout << std::endl << "NEW SOLUTION AFTER DELETE" << std::endl;
    new_solution->print_solution();
    delete new_solution; 
}
