#ifndef INPUTS_READER_H
#define INPUTS_READER_H

#include "Maths/Objects/Array/Array_double/array_double.h"
#include "Maths/Objects/Array/Array_int/array_int.h"

#include <string>

std::string get_parameter_as_string( std::string& parameter_to_find );

std::string get_string( std::string name );
int get_int( std::string name );
double get_double( std::string name );
Array_int get_array_int( std::string name );
Array_double get_array_double( std::string name );

int find_nb_strings_in_string( std::string reference_string, std::string input_string );

#endif // INPUTS_READER_H
