#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <cstdint>
#include <vector>

class Problem {
private:
    double work_time;
    uint32_t proc_index;
    uint32_t index;
    std::vector<Problem *> *next_links = nullptr;
public:
    Problem(double work_time, uint32_t proc_index, uint32_t index) :
        work_time(work_time), proc_index(proc_index), index(index) {
        this->next_links = new std::vector<Problem *>();
    }

    void add_next_link(Problem *problem);
    void change_proc_index(uint32_t new_index);
    std::vector<Problem *>* get_next_links();
    uint32_t get_index();
    uint32_t get_proc_index();
};

#endif // PROBLEM_HPP
