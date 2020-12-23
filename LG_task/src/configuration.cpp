#include "configuration.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

int get_index(int x, int y) {
    return x + y * FIELD_SIDE;
}

bool get_tile(int x, int y, ConfigPtr config) {
    if (x < 0 or x >= FIELD_SIDE) return false;
    if (y < 0 or y >= FIELD_SIZE) return false;

    return (*config)[get_index(x, y)];
}

void fill_field(ConfigPtr config) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        bool now = std::rand() % 2 == 1;
        config->set(i, now);
    }
}

void print_scroll_field(ConfigPtr config) {
    for (int y = 0; y < FIELD_SIDE; y++) {
        for (int x = 0; x < FIELD_SIDE; x++) {
            if ((*config)[get_index(x, y)]) std::cout << "X ";
            else std::cout << "- ";
        }
        std::cout << std::endl;
    }
}
void print_to_file(ConfigPtr config, std::string file_name) {
    std::ofstream out(file_name);
    for (int y = 0; y < FIELD_SIDE; y++) {
        for (int x = 0; x < FIELD_SIDE; x++) {
            if ((*config)[get_index(x, y)]) out << "X ";
            else out << "- ";
        }
        out << std::endl;
    }
}

void print_not_scroll_field(ConfigPtr config) {
    std::stringstream strs;
    for (int y = 0; y < FIELD_SIDE; y++) {
        for (int x = 0; x < FIELD_SIDE; x++) {
            if ((*config)[get_index(x, y)]) strs << "X ";
            else strs << "- ";
        }
        strs << std::endl;
    }
    printf("\033[;H%s", strs.str().c_str());
    fflush(stdout);
}

void invert_bit(int x, int y, ConfigPtr config) {
    config->set(get_index(x, y), not (*config)[get_index(x, y)]);
}

int evaluate_configuration(ConfigPtr config) {
    ConfigPtr tmp_config = std::make_shared<Config>(*config);

    progress_field(tmp_config);

    Config test = (*tmp_config) ^ (*config);
    
    return test.count() ? tmp_config->count() : tmp_config->count() - FIELD_SIZE;
}

bool progress_tile(int x, int y, ConfigPtr config) {
    std::vector<int> x_mods{-1, 0, 1};
    std::vector<int> y_mods{-1, 0, 1};

    int counter = 0;

    for (auto x_mod : x_mods) {
        for (auto y_mod : y_mods) {
            if (x_mod == 0 and y_mod == 0) continue;
            if (get_tile(x + x_mod, y + y_mod, config)) counter++;
        }
    }
    if (get_tile(x, y, config)) {
        if (counter < 2 or counter > 3) return true;
        return false;
    }
    if (counter == 3) return true;
    return false;
}

void progress_field(ConfigPtr config) {
    Config prog_field;
    for (int y = 0; y < FIELD_SIDE; y++) {
        for (int x = 0; x < FIELD_SIDE; x++) {
            prog_field.set(get_index(x, y), progress_tile(x, y, config));
        }
    }
    (*config) ^= prog_field;
}

bool check_border(ConfigPtr config) {
    ConfigPtr tmp_config = std::make_shared<Config>(*config);

    progress_field(tmp_config);

    Config test = (*tmp_config) ^ (*config);
    
    return test.count();
}

void create_generation(ConfigPtr config) {
    for (int i = 0; i < 100; i++) {
        progress_field(config);
    }
}
