#ifndef SOLUTION_HPP
#define SOLUTION_HPP


#include <vector>
#include "problem.hpp"


class Solution {
private:
public:
    Solution() {
    }
};


class BigSolution : public Solution {
private:
    std::vector<Problem *> work_flow;
    uint32_t num_procs;
    uint32_t num_problems;
public:
    BigSolution(uint32_t num_procs = 1, uint32_t num_problems = 0) :
        num_procs(num_procs), num_problems(num_problems) {

    }
    
    void add_new_problem(Problem *problem);
};
#endif // SOLUTION_HPP
