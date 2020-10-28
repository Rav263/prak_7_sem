#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>


#include "temperature.hpp"
#include "solution.hpp"
#include "mutable.hpp"
#include "io.hpp"



Solution *create_init_solution(uint32_t num_of_problems, uint32_t num_of_procs) {
    BigSolution *init_solution = new BigSolution(num_of_procs, num_of_problems);
    std::vector<Problem *> problems;
   
    double full_time = 0;

    for (uint32_t i = 0; i < num_of_problems; i++) {
        problems.push_back(new Problem(2.0, 1, i));
        full_time += problems[problems.size() - 1]->get_work_time();
    }

    std::sort(problems.begin(), problems.end(), [](Problem* first, Problem *second){
        return first->get_work_time() > second->get_work_time();
    });

    double for_proc_work_time = full_time / num_of_procs;

    uint32_t an_time = std::floor(for_proc_work_time);
    uint32_t index = 0;

    for (uint32_t i = 0; i < num_of_procs; i++) {
        double now_added_time = 0;
        
        while (now_added_time < an_time and index < num_of_problems) {
            problems[index]->change_proc_index(i);
            init_solution->add_new_problem(problems[index]);
            now_added_time += problems[index]->get_work_time();
            index++;
        }
        std::cout << now_added_time << " " << an_time << std::endl;
    
        if (index >= num_of_problems) {
            break;
        }
    }

    for (; index < num_of_problems; index++) {
        problems[index]->change_proc_index(num_of_procs - 1);
        
        init_solution->add_new_problem(problems[index]);
    }

    return init_solution;
}


int main() {
    uint32_t num_of_procs = 1, num_of_problems = 0;

    std::cout << "Enter num of procs: ";
    std::cin >> num_of_procs;

    std::cout << "Enter num of problems: ";
    std::cin >> num_of_problems;


    Solution *solution = create_init_solution(num_of_problems, num_of_procs);
    MutableLaw *mut = new MutableLawOp();

    std::cout << "INIT SOLUTION: " << std::endl;
    solution->print_solution();
    
    IO *io = new IO(solution, mut, nullptr);

    io->main_cycle();
    auto best_solution = io->get_best_solution();

    best_solution->print_solution();

    delete solution;
    delete mut;
    delete io;
}
