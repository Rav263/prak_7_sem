#ifndef PARALLEL_IO_HPP
#define PARALLEL_IO_HPP

#include <thread>
#include <mutex>
#include <vector>

#include "io.hpp"
#include "solution.hpp"
#include "mutable.hpp"
#include "temperature.hpp"
#include "problem.hpp"


class ParallelIO {
    std::vector<IO*> io_tasks;
    std::vector<Problem *> *problems;
    std::mutex mut;
    
    MutableLaw *mut_law;
    Solution *best_solution;
    
    uint32_t num_procs;
    double init_temp;

public:
    ParallelIO(uint32_t num_procs = 1, double init_temp = 1000.0, 
            std::vector<Problem *> *problems = nullptr) 
        : num_procs(num_procs), init_temp(init_temp), problems(problems) {
        this->mut_law = new MutableLawOp();
    }


    template<class TempLaw>
    void create_io_tasks(uint32_t num_problems, uint32_t num_procs, 
            uint32_t start_time, uint32_t end_time) {
        this->create_problems(num_problems, num_procs, start_time, end_time);
        Solution *init_solution = this->create_init_solution(num_problems, num_procs);
        std::cout << "Init evaluation: " << init_solution->evaluate() << std::endl;
        for (uint32_t i = 0; i < this->num_procs; i++) {
            this->io_tasks.push_back(
                new IO(init_solution->copy_solution(), this->mut_law, new TempLaw(this->init_temp)));
        }

        this->best_solution = init_solution;
    }

    Solution *create_init_solution(uint32_t num_problems, uint32_t num_procs);
    void create_problems(uint32_t num_problems, uint32_t num_procs, 
            uint32_t start_time, uint32_t end_time);
    void main_cycle();
    
    std::vector<Problem *> *get_problems() {
        return this->problems;
    }

    Solution *get_best_solution();

    ~ParallelIO() {
        for (auto now_io : this->io_tasks) {
            delete now_io;
        }
        delete this->mut_law;
    }
};

#endif // PARALLEL_IO_HPP
