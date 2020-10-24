#ifndef MUTABLE_HPP
#define MUTABLE_HPP

#include <iostream>
#include "solution.hpp"


class MutOperation {
public:
    Solution *solution;
    MutOperation(Solution *solution) : solution(solution) {
    }
};

class MyMutOperation : public MutOperation {
public:
    MyMutOperation(Solution *solution) : MutOperation(solution) {
    }
}

#endif //MUTABLE_HPP
