#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>
#include <map>

#include "problem.hpp"


using Procs = std::vector<uint32_t>;
using Problems = std::vector<Problem *>;


class Solution {
public:
    Procs procs;
    Problems problems;
    
    Solution() {}

    virtual Solution* copy_solution() {
        return nullptr;
    }
    
    virtual void print_solution() {}

    virtual void change_problem_proc_index(uint32_t problem_index, uint32_t proc_index){}; 

    virtual double evaluate() {
        return 0.0;
    }

    ~Solution() {
        for (auto now_problem : this->problems) {
            delete now_problem;
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
        problems = Problems(num_problems);
        procs = Procs(num_procs);
    }
    
    void add_new_problem(Problem *problem);
    virtual void change_problem_proc_index(uint32_t problem_index, uint32_t proc_index); 
    virtual Solution* copy_solution();
    virtual void print_solution();
    virtual double evaluate();
};
#endif // SOLUTION_HPP
