#ifndef GRADIENT_DESCENT_HPP
#define GRADIENT_DESCENT_HPP

#include "math_lib.hpp"

#define STEP_SIZE 0.001

double GradientDescent(std::shared_ptr<TFunction> func, uint64_t iterations, double now_x);

#endif // GRADIENT_DESCENT_HPP
