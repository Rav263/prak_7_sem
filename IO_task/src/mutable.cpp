#include "mutable.hpp"

#include <ctime>
#include <cstdlib>
#include <cmath>


double MutableLawOp::mut_solution(Solution *solution, Temp *temp) {
    auto num_procs = solution->get_procs_num();
    auto num_problems = solution->get_problems_num();
    auto old_evaluation = solution->evaluate();

    auto problem_index = std::rand() % num_problems;
    auto now_proc_index = solution->get_problem_proc_index(problem_index);
    auto proc_index = std::rand() % num_procs;
    
    while (now_proc_index == proc_index) {
        proc_index = std::rand() % num_procs;
    }

    solution->change_problem_proc_index(problem_index, proc_index);

    auto new_evaluation = solution->evaluate();

    if (new_evaluation < old_evaluation) {
        return new_evaluation;
    } else {
        double prob = std::exp(-(new_evaluation - old_evaluation) / temp->temp);
        double an_prob =  (double) (std::rand() % 1000) / 1000.0;
        std::cout << prob << " " << an_prob << std::endl;

        if (an_prob > prob) {
            solution->change_problem_proc_index(problem_index, now_proc_index);
        }

        return solution->evaluate();
    }
}
