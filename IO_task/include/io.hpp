#ifndef IO_HPP
#define IO_HPP

class IO {
private:
    Solution *now_solution = nullptr;
    Solution *best_solution = nullptr;
    uint32_t best_metric;
public:
    IO(Solution *initial_solution) : now_solution(initial_solution){
    }

    void main_cycle();
    Solution *get_best_solution();  
    void evaluate_now_solution();
};

#endif //IO_HPP
