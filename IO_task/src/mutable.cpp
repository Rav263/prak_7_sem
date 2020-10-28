#include "mutable.hpp"

#include <ctime>
#include <cstdlib>


double MutableLawOp::mut_solution(Solution *solution, Temp *temp) {
    auto num_procs = solution->get_procs_num();
    auto num_problems = solution->get_problems_num();

    auto problem_index = std::rand() % num_problems;
    auto now_proc_index = solution->get_problem_proc_index(problem_index);
    auto proc_index = std::rand() % num_procs;
    
    while (now_proc_index == proc_index) {
        proc_index = std::rand() % num_procs;
    }

    solution->change_problem_proc_index(problem_index, proc_index);

    return solution->evaluate();
}
