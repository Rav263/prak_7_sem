#ifndef SELECTION_HPP
#define SELECTION_HPP

#include "configuration.hpp"
#include <memory>
#include <iostream>

class AbstractSelection {
public:
    virtual std::vector<ConfigPtr> select(std::vector<std::pair<ConfigPtr, int32_t>> &population) = 0;
};

class Selection : public AbstractSelection {
public:
    uint32_t tournament_size = 16;
    uint32_t num_of_tournaments = 50;
    Selection(uint32_t tournamet_size = 8, uint32_t num_of_tournaments = 50) {
        this->tournament_size = tournament_size;
        this->num_of_tournaments = num_of_tournaments;
        std::cerr << this->tournament_size << " " << this->num_of_tournaments << std::endl;
    }
    std::vector<ConfigPtr> select(std::vector<std::pair<ConfigPtr, int32_t>> &population);
};

using SelectionPtr = std::shared_ptr<AbstractSelection>;

#endif
