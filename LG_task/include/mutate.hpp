#ifndef MUTATE_HPP
#define MUTATE_HPP

#include "configuration.hpp"
#include <memory>



class AbstractMutation {
public:
    virtual void mutate(std::vector<ConfigPtr> &population) = 0;
};

class Mutation : public AbstractMutation {
    double p_mut = 0.0004;
public:
    Mutation(double p_mut) {
        this->p_mut = p_mut;
    }

    void mutate(std::vector<ConfigPtr> &population);
};



using MutationPtr = std::shared_ptr<AbstractMutation>;
#endif
