#ifndef CROSSBREEDING_HPP
#define CROSSBREEDING_HPP

#include "configuration.hpp"
#include <memory>

class AbstractCrossbreeding {
};

class Crossbreeding : public AbstractCrossbreeding {
};


using CrossbreedingPtr = std::shared_ptr<AbstractCrossbreeding>;

#endif
