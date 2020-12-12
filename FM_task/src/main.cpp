#include <iostream>

// #include "math_lib.hpp"
#include "factory.hpp"
#include "operators.hpp"
#include "gradient_descent.hpp"

#include <cmath>

using TFunctionPtr = std::shared_ptr<TFunction>;

int main() {
    FunFactory fact;
    auto fun_1 = fact.CreateFunction("polynomial", {std::exp(1)*std::exp(1)});
    auto fun_2 = fact.CreateFunction("exp", {std::exp(1)});
    auto fun_3 = fact.CreateFunction("polynomial", {0, 2, 1});
/*
    auto mul = fun_2 - fun_1;
    auto mul_2 = mul * mul;

    std::cout << mul_2->GetDeriv(1.5) << std::endl;
    std::cout << mul->ToString() << std::endl;*/ 
    std::cout << fun_3->GetDeriv(3) << " " << (*fun_3)(3) << std::endl;
}
