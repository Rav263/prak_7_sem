#ifndef CROSSBREEDING_HPP
#define CROSSBREEDING_HPP

#include "configuration.hpp"
#include <memory>

class AbstractCrossbreeding {
public:
    virtual void crossbreed(std::vector<ConfigPtr> &population) = 0;
};

class Crossbreeding : public AbstractCrossbreeding {
double p_cross = 0.8;
uint32_t npop = 100;
public:
    void crossbreed(std::vector<ConfigPtr> &population);
};


using CrossbreedingPtr = std::shared_ptr<AbstractCrossbreeding>;

#endif
