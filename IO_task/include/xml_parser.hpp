#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include <iostream>
#include <fstream>


#include "problem.hpp"

void write_xml_file(std::vector<Problem *> &, 
        uint32_t &, uint32_t &, uint32_t &, uint32_t &, std::string &);
void read_xml_file(std::vector<Problem *> &,
        uint32_t &, uint32_t &, uint32_t &, uint32_t &, std::string &);

#endif //XML_PARSER_HPP
