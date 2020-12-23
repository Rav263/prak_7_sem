#include "selection.hpp"
#include <set>
#include <iostream>


std::vector<ConfigPtr> Selection::select(std::vector<std::pair<ConfigPtr, int32_t>> &population) {
    std::vector<ConfigPtr> result;
    std::set<ConfigPtr> used;

    for (uint32_t tour = 0; tour < this->num_of_tournaments; tour++) {
        std::set<std::pair<ConfigPtr, int32_t>> players;
        while (players.size() < this->tournament_size) {
            uint32_t index;
            do {
                index = std::rand() % population.size();
            } while (used.count(population[index].first));

            players.insert(population[index]);
        }

        std::pair<ConfigPtr, int32_t> best = {nullptr, 0};
        for (auto player : players) {
            if (player.second > best.second or best.first == nullptr) {
                best = player;
            }
        }

        used.emplace(best.first);
        result.push_back(best.first);
    }


    return result;
}
