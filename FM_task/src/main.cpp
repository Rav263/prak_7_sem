#include <iostream>

// #include "math_lib.hpp"
#include "factory.hpp"
#include "operators.hpp"
#include "gradient_descent.hpp"

using TFunctionPtr = std::shared_ptr<TFunction>;

int main() {
    FunFactory fact;

    std::vector<TFunctionPtr> cont;
    auto f = fact.CreateFunction("exp", {2}); // PowerFunc x^2
    cont.push_back(f);

    auto g = fact.CreateFunction("polynomial", {0, 3}); // TPolynomial 7 + 3*x^2 + 15*x^3
    cont.push_back(g);
    for (const auto ptr : cont) {
        std::cout << ptr->ToString() << " for x = 10 is " << (*ptr)(10) << std::endl;
    }
    auto p = f  + g;

    std::cout << p->GetDeriv(1) << " " << f->GetDeriv(3) << std::endl;
    std::cout << (*p)(10) << std::endl;
    auto fun_2 = fact.CreateFunction("polynomial", {0, 1, -2.3});
}
