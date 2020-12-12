#include "gradient_descent.hpp"
#include "operators.hpp"
#include <iostream>

double GradientDescent(
        std::shared_ptr<TFunction> func, 
        uint64_t iterations, 
        double now_x, 
        double step_size) {
    
    auto sq_func = func * func;
    for (uint64_t iter = 0; iter < iterations; iter += 1) {
//        std::cout << "iter " << iter << ": " << now_x << " " << sq_func->GetDeriv(now_x) << std::endl;
        now_x = now_x - step_size * sq_func->GetDeriv(now_x);
    }

    return now_x;
}
