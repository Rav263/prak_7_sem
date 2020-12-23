#ifndef SELECTION_HPP
#define SELECTION_HPP

#include "configuration.hpp"
#include <memory>

class AbstractSelection {
public:
    virtual void select() = 0;
};

class Selection : public AbstractSelection {
    void select();
}

using SelectionPtr = std::shared_ptr<AbstractSelection>;

#endif
