#ifndef MUTATE_HPP
#define MUTATE_HPP

#include "configuration.hpp"
#include <memory>



class AbstractMutation {
};

class Mutation : public AbstractMutation {
};



using MutationPtr = std::shared_ptr<AbstractMutation>;
#endif
