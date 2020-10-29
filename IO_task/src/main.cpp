#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>

#include "temperature.hpp"
#include "parallel_io.hpp"
#include "problem.hpp"
#include "xml_parser.hpp"

void help() {
    std::cout << "---------- this is help message ----------" << std::endl;
    std::cout << "--file [file_name]                        arg for set path to file with problem *.xml" << std::endl;
    std::cout << "--self [num_of_procs] [num_of_problems]   this arg for self problem generation (instead of --file)" << std::endl;
    std::cout << "--time [start_time] [end_time]            generate problems with work time in (start_time, end_time] (default (1, 5])" << std::endl;
    std::cout << "--procs [NProc]                           Solve program on NProc threads (default 1)" << std::endl;
    std::cout << "--help                                    print this message" << std::endl;
}


std::string process_args(int argc, char** argv, std::map<std::string, uint32_t> &args) {
    std::string file_name = "";
    args["procs"] = 1;
    args["start_time"] = 1;
    args["end_time"] = 2;
    args["generate"] = 0;

    for (uint32_t i = 1; i < argc; i++) {
        std::string now_arg(argv[i]);
         
        if (now_arg == "--procs") {
            if (i + 1 == argc) {
                help();
                exit(0);
            }
            std::string value(argv[i + 1]);
            args["procs"] = std::stoi(value);
        } else if (now_arg == "--self") {
            std::string procs = argv[i + 1];
            if (i + 1 == argc) {
                help();
                exit(0);
            }
            std::string problems(argv[i + 2]);
            args["num_of_problems"] = std::stoi(problems);
            args["num_of_procs"] = std::stoi(procs);
        } else if (now_arg == "--file") {
            if (i + 1 == argc) {
                help();
                exit(0);
            }

            file_name = std::string(argv[i + 1]);
        } else if (now_arg == "--help") {
            help();
            exit(0);
        } else if (now_arg == "--time" ) {
            if (i + 1 == argc) {
                help();
                exit(0);
            }
            args["start_time"] = std::stoi(std::string(argv[i + 1]));
            args["end_time"] = std::stoi(std::string(argv[i + 2]));
        } else if (now_arg == "--generate") {
            args["generate"] = 1;
        }
    }

    return file_name;
}


int main(int argc, char **argv) {
    std::map<std::string, uint32_t> args;
    std::string file_name = process_args(argc, argv, args);
    
    ParallelIO *parallel_io; 
    
    if (file_name.size() == 0 and args.count("num_of_problems") != 0) {
        parallel_io = new ParallelIO(args["procs"]);
    
    } else if (file_name.size() != 0) {
         if (args["generate"] and args.count("num_of_problems") != 0) {
            parallel_io = new ParallelIO(args["procs"]);
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
            // Task from file
         }
   
    } else {
        std::cerr << "BAD ARGS -- NO TASK" << std::endl;
        help();
        return 0;
    }

    parallel_io->create_io_tasks<TempFirst>(args["num_of_problems"], args["num_of_procs"], args["start_time"], args["end_time"]);
    parallel_io->main_cycle();

    auto best_solution = parallel_io->get_best_solution();
    std::cout << "End evaluation: " << best_solution->evaluate() << std::endl;

    delete parallel_io;
    delete best_solution;
}
