#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <map>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include "configuration.hpp"
#include "genetic_algorithm.hpp"


std::string process_args(int argc, char *argv[], std::map<std::string, double> &args) {
    std::string file_name = "";

    args["seed"] = std::time(nullptr);
    args["pmut"] = 0.0004;
    args["series"] = 1;
    args["help"] = 0;
    args["exp"] = 1;

    for (uint32_t i = 1; i < argc; i++) {
        std::string now_arg(argv[i]);
        if (i + 1 < argc) {
            std::string value(argv[i + 1]);
            if (now_arg == "--seed") {
                args["seed"] = std::stod(value);
            } else if (now_arg == "--series") {
                args["pmut"] = args["pmut"] * std::pow(1.5, std::stod(value));
                args["series"] = std::stoi(value);
            } else if (now_arg == "--file") {
                file_name = value;
            } else if (now_arg == "--exp") {
                args["exp"] = stoi(value);
            }
        } else {
            if (now_arg == "--help") {
                args["help"] = 1;
            }
        }
    }

    return file_name;
}

ConfigPtr read_configuration(std::string file_name) {
    std::ifstream in_file(file_name);
    Config now;

    for (uint32_t i = 0; i < FIELD_SIZE; i++) {
        std::string now_char;
        in_file >> now_char;

        if (now_char == "X") {
            now.set(i);
        }
    }
    return std::make_shared<Config>(now);
}


int main(int argc, char *argv[]) {
    std::map<std::string, double> args;
    std::string file_name = process_args(argc, argv, args);
    std::srand(int(args["seed"]));
    std::cerr << "SEEED: " << int(args["seed"]) << std::endl;

    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    
    if (file_name != "") {
        auto config = read_configuration(file_name);
        system("clear");
        for (int i = 0; i < 101; i++) {
            print_not_scroll_field(config);
            progress_field(config);
            sleep_for(milliseconds(100));
        }

        return 0;
    }

    
    auto mutation = std::make_shared<Mutation>(args["pmut"]);
    auto selection = std::make_shared<Selection>(4, 50);
    auto crossbreeding = std::make_shared<Crossbreeding>();

    GeneticAlgorithm genetic(mutation, selection, crossbreeding);
        
    auto start_time = high_resolution_clock::now();
    genetic.main_cycle();
    auto end_time = high_resolution_clock::now();
    duration<double, std::milli> time_span = end_time - start_time;
    
    std::cout << time_span.count() << " " << evaluate_configuration(genetic.best_configuration) << std::endl;
    std::cerr << genetic.master << std::endl;
    std::stringstream strs;
    strs << "series_" << int(args["series"]) << "_run_" << int(args["exp"]) << ".txt";
    print_to_file(genetic.best_configuration, strs.str());

    for (int i = 0; i < 100; i++) {
        progress_field(genetic.best_configuration);
    }
    std::stringstream strs_after;
    strs_after << "series_" << int(args["series"]) << "_run_" << int(args["exp"]) << "_sol_after100.txt";
    print_to_file(genetic.best_configuration, strs_after.str());
}
