#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include <string>
#include <vector>

std::vector<std::string> get_directories(const std::string& directory);

void clear_output_directories();

void clear_directory( std::string directory );

void delete_file( std::string directory, std::string filename );

void replace_line_in_file( std::string old_line, std::string new_line, std::string filename );

void move_file( std::string filename, std::string initial_directory, std::string target_directory );

void make_archive();

#endif // FILE_MANAGEMENT_H
