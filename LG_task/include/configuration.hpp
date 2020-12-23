#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <bitset>
#include <vector>
#include <memory>


#define FIELD_SIDE 50
#define FIELD_SIZE FIELD_SIDE*FIELD_SIDE

using Config = std::bitset<FIELD_SIZE>;
using ConfigPtr = std::shared_ptr<Config>;

void print_scroll_field(ConfigPtr config);
void print_to_file(ConfigPtr config, std::string file_name);
void print_not_scroll_field(ConfigPtr config);
void fill_field(ConfigPtr config);
int get_index(int x, int y);
void invert_bit(int x, int y, ConfigPtr config);  
void progress_field(ConfigPtr config);
bool check_border(ConfigPtr config);
void create_generation(ConfigPtr config);
int evaluate_configuration(ConfigPtr config);

#endif
