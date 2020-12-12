#ifndef GRADIENT_DESCENT_HPP
#define GRADIENT_DESCENT_HPP

#include "math_lib.hpp"

double GradientDescent(
        std::shared_ptr<TFunction> func,
        uint64_t iterations,
        double now_x,
        double step_size);

#endif // GRADIENT_DESCENT_HPP
