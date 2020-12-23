#include "mutate.hpp"

void Mutation::mutate(std::vector<ConfigPtr> &population) {
    for (auto config : population) {
        for (int i = 0; i < FIELD_SIZE; i++){
            double prob = (std::rand() % 10000) / (10000.0);
            if (prob < this->p_mut) config->flip(i);
        }
    }
}
