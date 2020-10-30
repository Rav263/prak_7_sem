#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <chrono>


#include "temperature.hpp"
#include "parallel_io.hpp"
#include "problem.hpp"
#include "xml_parser.hpp"

void help() {
    std::cout << "---------- this is help message ----------" << std::endl;
    std::cout << "--file [file_name]                        Arg for set path to file with problem *.xml" << std::endl;
    std::cout << "--self [num_of_procs] [num_of_problems]   This arg for self problem generation (instead of --file)" << std::endl;
    std::cout << "--time [start_time] [end_time]            Generate problems with work time in (start_time, end_time] (default (1, 5])" << std::endl;
    std::cout << "--procs [NProc]                           Solve program on NProc threads (default 1)" << std::endl;
    std::cout << "--print                                   Print best solution" << std::endl;
    std::cout << "--generate                                Writes generated task into file" << std::endl;
    std::cout << "--temp [temp_law]                         Used temp decrease low from 1 to 3 (default 1)" << std::endl;
    std::cout << "--seed [seed]                             Use seed for random (default time(0))" << std::endl;
    std::cout << "--help                                    Print this message" << std::endl;
}


std::string process_args(int argc, char** argv, std::map<std::string, uint32_t> &args) {
    std::string file_name = "";
    args["procs"] = 1;
    args["start_time"] = 1;
    args["end_time"] = 5;
    args["generate"] = 0;
    args["print"] = 0;
    args["temp"] = 0;
    args["seed"] = 0;

    for (uint32_t i = 1; i < argc; i++) {
        std::string now_arg(argv[i]);
        if (i + 1 < argc) {
            if (now_arg == "--procs") {
                std::string value(argv[i + 1]);
                args["procs"] = std::stoi(value);
            } else if (now_arg == "--file") {
                file_name = std::string(argv[i + 1]);
            } else if (now_arg == "--temp") {
                args["temp"] = std::stoi(std::string(argv[i + 1]));
            } else if (now_arg == "--seed") {
                args["seed"] = std::stoi(std::string(argv[i + 1]));
            }
            if (i + 2 < argc) {
                if (now_arg == "--time" ) {
                    args["start_time"] = std::stoi(std::string(argv[i + 1]));
                    args["end_time"] = std::stoi(std::string(argv[i + 2]));
                } else if (now_arg == "--self") {
                    std::string procs = argv[i + 1];
                    std::string problems(argv[i + 2]);
                    args["num_of_problems"] = std::stoi(problems);
                    args["num_of_procs"] = std::stoi(procs);
                }  
            }
        }
        if (now_arg == "--generate") {
            args["generate"] = 1;
        } else if (now_arg == "--print") {
            args["print"] = 1;
        } else if (now_arg == "--help") {
            help();
            exit(0);
        }
    }

    return file_name;
}


int main(int argc, char **argv) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::map<std::string, uint32_t> args;
    std::string file_name = process_args(argc, argv, args);
    
    uint64_t seed;
    if (args["seed"] == 0) {
        seed = time(0);
    } else {
        seed = args["seed"];
    }
    std::cerr << "SEEED: " << seed << std::endl;
    std::srand(seed);
    
    ParallelIO *parallel_io; 
    double init_temp = 10000.0;

    if (file_name.size() == 0 and args.count("num_of_problems") != 0) {
        parallel_io = new ParallelIO(args["procs"]);
    
    } else if (file_name.size() != 0) {
        if (args["generate"] and args.count("num_of_problems") != 0) {
            parallel_io = new ParallelIO(args["procs"], init_temp);
            parallel_io->create_problems(args["num_of_problems"], args["num_of_procs"], 
                    args["start_time"], args["end_time"]);

            auto problems = parallel_io->get_problems();
            write_xml_file(*problems, args["num_of_problems"], args["num_of_procs"], args["start_time"], args["end_time"], file_name);
            delete parallel_io;
            return 0;
            // Test generation

        } else if (args["generate"]) {
            std::cerr << "BAD ARGS -- NO TASK" << std::endl;
            help();
            return 0;
         
        } else {
            std::vector<Problem *> *problems = new std::vector<Problem *>();
            uint32_t num_problems = 0;
            uint32_t num_procs = 0;
            uint32_t start_time = 0;
            uint32_t end_time =0;

            read_xml_file(*problems, num_problems, num_procs, start_time, end_time, file_name);
            args["num_of_problems"] = num_problems;
            args["num_of_procs"] = num_procs;
            args["start_time"] = start_time;
            args["end_time"] = end_time;
            
            parallel_io = new ParallelIO(args["procs"], init_temp, problems);
         } 
    } else {
        std::cerr << "BAD ARGS -- NO TASK" << std::endl;
        help();
        return 0;
    }

    if (args["temp"] == 2) {
        parallel_io->create_io_tasks<TempSecond>(args["num_of_problems"], args["num_of_procs"], args["start_time"], args["end_time"]);
    } else if (args["temp"] == 3) {
        parallel_io->create_io_tasks<TempThird>(args["num_of_problems"], args["num_of_procs"], args["start_time"], args["end_time"]);
    } else {
        parallel_io->create_io_tasks<TempFirst>(args["num_of_problems"], args["num_of_procs"], args["start_time"], args["end_time"]);
    }
    parallel_io->main_cycle();

    auto best_solution = parallel_io->get_best_solution();
    std::cout << "End evaluation: " << best_solution->evaluate() << std::endl;
    
    if (args["print"])
        best_solution->print_solution();
    
    auto end_time = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> time_span = end_time - start_time;

    std::cout << "Spended time: " << time_span.count() << std::endl;
    delete parallel_io;
    delete best_solution;
}
