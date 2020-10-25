#include "problem.hpp"


void Problem::add_next_link(Problem *problem) {
    this->next_links->push_back(problem);
}

void Problem::change_proc_index(uint32_t new_index) {
    this->proc_index = new_index;
}

std::vector<Problem *>* Problem::get_next_links() {
    return this->next_links;
}

uint32_t Problem::get_index() {
    return this->index;
}

uint32_t Problem::get_proc_index() {
    return this->proc_index;
}

Problem *Problem::copy_problem() {
    Problem *new_problem = new Problem(this->work_time, this->proc_index, this->index);
    
    return new_problem;
}

Problem::~Problem() {
    delete this->next_links;
}
