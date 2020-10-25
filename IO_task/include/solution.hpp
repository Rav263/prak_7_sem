#ifndef SOLUTION_HPP
#define SOLUTION_HPP


#include <vector>
#include "problem.hpp"


class Solution {
public:
    std::vector<Problem *> work_flow;
    Solution() {
    }

    virtual Solution* copy_solution(){
        return nullptr;
    }
    
    virtual void print_solution(){}

    virtual Problem *get_problem(uint32_t index){
        return nullptr;
    }

    ~Solution() {
        for (auto now : this->work_flow) {
            delete now;
        }
    }
};


class BigSolution : public Solution {
private:
    uint32_t num_procs;
    uint32_t num_problems;
public:
    BigSolution(uint32_t num_procs = 1, uint32_t num_problems = 0) :
        num_procs(num_procs), num_problems(num_problems) {

    }
    
    void add_new_problem(Problem *problem);
    uint32_t get_last_problem_index();
    virtual Problem *get_problem(uint32_t index);
    virtual Solution* copy_solution();
    virtual void print_solution();
};
#endif // SOLUTION_HPP
