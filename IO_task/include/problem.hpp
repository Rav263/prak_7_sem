#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <cstdint>
#include <vector>

class Problem {
private:
    double work_time;
    uint32_t proc_index;
    uint32_t index;
public:
    Problem(double work_time, uint32_t proc_index, uint32_t index) :
        work_time(work_time), proc_index(proc_index), index(index) {
    }

    double get_work_time();
    void change_proc_index(uint32_t new_index);
    uint32_t get_index();
    uint32_t get_proc_index();
    Problem *copy_problem();
};

#endif // PROBLEM_HPP
