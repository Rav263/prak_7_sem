#include "xml_parser.hpp"
#include <tinyxml2.h>


void write_xml_file(std::vector<Problem *> &problems, 
        uint32_t &num_problems, uint32_t &num_procs, 
        uint32_t &start_time, uint32_t &end_time,
        std::string &file_name) {
    tinyxml2::XMLDocument document;

    auto task = document.NewElement("TASK");
    auto params = task->InsertNewChildElement("PARAMS");
    auto declaration = document.NewDeclaration();
    
    params->SetAttribute("PROBLEMS", num_problems);
    params->SetAttribute("PROCS", num_procs);
    params->SetAttribute("STARTTIME", start_time);
    params->SetAttribute("ENDTIME", end_time);
    
    auto problems_el = task->InsertNewChildElement("PROBLEMS");

    for (auto now_problem : problems) {
        std::string name = "PROBLEM_";
        name += std::to_string(now_problem->get_index());
        auto problem_params = problems_el->InsertNewChildElement(name.c_str());
        problem_params->SetAttribute("WORKTIME", now_problem->get_work_time());
    }

    document.InsertFirstChild(declaration);
    document.InsertEndChild(task);

    document.SaveFile(file_name.c_str());
}


void read_xml_file(std::vector<Problem *> &problems,
        uint32_t &num_problems, uint32_t &num_procs,
        uint32_t &start_time, uint32_t &end_time,
        std::string &file_name) {
    tinyxml2::XMLDocument document;
    document.LoadFile(file_name.c_str());

    auto task = document.FirstChildElement();
    auto params = task->FirstChildElement();
   
    auto probs = params->FindAttribute("PROBLEMS");
    auto procs = params->FindAttribute("PROCS");
    auto st_time = params->FindAttribute("STARTTIME");
    auto ed_time = params->FindAttribute("ENDTIME");

    probs->QueryUnsignedValue(&num_problems);
    procs->QueryUnsignedValue(&num_procs);
    st_time->QueryUnsignedValue(&start_time);
    ed_time->QueryUnsignedValue(&end_time); 

    auto problems_at = task->LastChildElement();

    for (int i = 0; i < num_problems; i++) {
        auto now_problem = problems_at->FirstChildElement();
        double work_time;
        auto work_time_at = now_problem->FindAttribute("WORKTIME");
        work_time_at->QueryDoubleValue(&work_time);

        auto gen_problem = new Problem(work_time, 0, i);
        problems_at->DeleteChild(now_problem);
        problems.push_back(gen_problem);
    }
}
