#include <iostream>

// #include "math_lib.hpp"
#include "factory.hpp"
#include "operators.hpp"

using TFunctionPtr = std::shared_ptr<TFunction>;

int main() {
    FunFactory fact;

    std::vector<TFunctionPtr> cont;
    auto f = fact.CreateFunction("power", {2}); // PowerFunc x^2
    cont.push_back(f);

    auto g = fact.CreateFunction("polynomial", {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3
    cont.push_back(g);
    for (const auto ptr : cont) {
        std::cout << ptr->ToString() << " for x = 10 is " << (*ptr)(10) << std::endl;
    }
    auto p = g + f;
    std::cout << p->GetDeriv(1) << " " << f->GetDeriv(3) << std::endl;
    //auto fuck_you = "wedw" + f;
    std::cout << (*p)(10) << std::endl;
}
