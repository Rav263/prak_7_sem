#ifndef MUTABLE_HPP
#define MUTABLE_HPP

#include <iostream>
#include "solution.hpp"
#include "temperature.hpp"

class MutableLaw {
public:
    MutableLaw() {
    }

    virtual double mut_solution(Solution *solution, Temp * temp){return 0.0;}
};

class MutableLawOp : public MutableLaw {
public:
    MutableLawOp() {
    }

    virtual double mut_solution(Solution *solution, Temp *temp);
};

#endif //MUTABLE_HPP
