#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <map>
#include <string>
#include <cmath>
#include "configuration.hpp"

std::string process_args(int argc, char *argv[], std::map<std::string, double> &args) {
    std::string file_name = "";

    args["seed"] = std::time(nullptr);
    args["pmut"] = 0.0004;
    args["help"] = 0;

    for (uint32_t i = 1; i < argc; i++) {
        std::string now_arg(argv[i]);
        if (i + 1 < argc) {
            std::string value(argv[i + 1]);
            if (now_arg == "--seed") {
                args["seed"] = std::stod(value);
            } else if (now_arg == "--series") {
                args["pmut"] = args["pmut"] * std::pow(1.5, std::stod(value));
            } else if (now_arg == "--file") {
                file_name = value;
            }
        } else {
            if (now_arg == "--help") {
                args["help"] = 1;
            }
        }
    }

    return file_name;
}


int main(int argc, char *argv[]) {
    std::map<std::string, double> args;
    std::string file_name = process_args(argc, argv, args);
    std::srand(int(args["seed"]));

    ConfigPtr field = std::make_shared<Config>();
    fill_field(field);
    print_scroll_field(field);

    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    int iter = 0;

    system("clear");
    for (;;) {
        Config tmp_field = *field;
        progress_field(field);
        print_not_scroll_field(field);
        iter += 1;

        tmp_field ^= (*field);
        if (not tmp_field.count()) break;

        sleep_for(milliseconds(100));
    }

    std::cout << field->count() << " " << iter << std::endl;
}
