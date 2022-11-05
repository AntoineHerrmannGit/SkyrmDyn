#ifndef INPUTS_WRITER_H
#define INPUTS_WRITER_H

#include "Maths/Objects/Array/Array_double/array_double.h"

#include <string>

void change_input( std::string variable_name, std::string variable );

std::string convert_array_double_to_string( Array_double var );
std::string convert_array_float_to_string( Array_double var );
std::string convert_array_int_to_string( Array_double var );

#endif // INPUTS_WRITER_H
