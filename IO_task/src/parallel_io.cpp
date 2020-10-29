#include <algorithm>
#include <cmath>

#include "parallel_io.hpp"

void ParallelIO::create_problems(uint32_t num_problems, uint32_t num_procs, 
        uint32_t start_time, uint32_t end_time) {
    if (this->problems != nullptr) {
        return;
    }
    this->problems = new std::vector<Problem *>();
    for (uint32_t i = 0; i < num_problems; i++) {
        
        int32_t rasn = end_time - start_time - 1;

        double work_time = std::rand() % rasn + start_time;
        work_time += ((double) (std::rand() % 1000 + 1)) / 1000.0 ;
        this->problems->push_back(new Problem(work_time, 0, i));
    }
}


Solution *ParallelIO::create_init_solution(uint32_t num_of_problems, uint32_t num_of_procs) {
    BigSolution *init_solution = new BigSolution(num_of_procs, num_of_problems);
   
    double full_time = 0;
    std::vector<Problem *> problems = *this->problems;
    
    for (uint32_t i = 0; i < num_of_problems; i++) {
        full_time += problems[i]->get_work_time();
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
    
        if (index >= num_of_problems) {
            break;
        }
    }

    for (; index < num_of_problems; index++) {
        problems[index]->change_proc_index(num_of_procs - 1);
        
        init_solution->add_new_problem(problems[index]);
    }

    
    /*for (auto now_problem : problems) {
        init_solution->add_new_problem(now_problem);
    }*/
    return init_solution;
}

void ParallelIO::main_cycle() {
    uint32_t best_count = 0;
    for (;;) {
        std::vector<std::thread> threads(this->io_tasks.size());
        for (uint32_t i = 0; i < threads.size(); i++) {
            threads[i] = std::thread(&IO::main_cycle, this->io_tasks[i]);
        }
        
        for (auto &now_thread : threads) {
            now_thread.join();
        }

        auto best_evaluation = this->best_solution->evaluate();

        for (auto now_io : this->io_tasks) {
            auto now_solution = now_io->get_best_solution();
            if (now_solution->evaluate() < best_evaluation) {
                delete this->best_solution;
                this->best_solution = now_solution->copy_solution();
                best_count = -1;
            }
        }
        best_count += 1;

        for (auto now_io : this->io_tasks) {
            now_io->update_best_solution(this->best_solution->copy_solution());
        }

        if (best_count == 10) {
            break;
        }
    }
}

Solution *ParallelIO::get_best_solution() {
    return this->best_solution;
}
