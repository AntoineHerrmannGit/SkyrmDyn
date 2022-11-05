#include "inputs_writer.h"

#include "Objects/Parameter/parameter.h"

#include "Error_messages/error_messages.h"

#include "Maths/Objects/Array/Array_int/array_int.h"
#include "Maths/Objects/Array/Array_float/array_float.h"
#include "Maths/Objects/Array/Array_double/array_double.h"

#include <string>
#include <iostream>
#include <fstream>

#include <math.h>

void change_input( std::string variable_name, std::string variable ) {
    std::string new_line = variable_name + " = " + variable + "\n";
    std::string filename = "../SkyrmDyn_Cpp/inputs_config";
    std::ifstream read( filename );
    std::ofstream write( filename );

    std::string line;
    std::string tmp;
    if( read && write ) {
        // Read the file line by line
        while( std::getline( read, line ) ) {
            // If the name of the line containing the parameter is found
            if( line.find( variable_name + " = " ) != std::string::npos ) {
                write << new_line;
                break;
            }
            tmp = line;
            write << line + "\n";
        }
    }
    else {
        throw( DeclarationError( "\"read\" and/or \"write\"" ) );
    }
}

std::string convert_array_double_to_string( Array_double var ) {
    std::string result = "{";
    for( int i=0; i<var.get_dimension(); i++ ) {
        double xi = var.get_component( i );
        result += std::to_string( xi ) + ", ";
    }
    result += result.substr( 0, result.size() - 2 ) + "}";
    return result;
}
std::string convert_array_float_to_string( Array_double var ) {
    std::string result = "{";
    for( int i=0; i<var.get_dimension(); i++ ) {
        float xi = var.get_component( i );
        result += std::to_string( xi ) + ", ";
    }
    result += result.substr( 0, result.size() - 2 ) + "}";
    return result;
}
std::string convert_array_int_to_string( Array_double var ) {
    std::string result = "{";
    for( int i=0; i<var.get_dimension(); i++ ) {
        int xi = var.get_component( i );
        result += std::to_string( xi ) + ", ";
    }
    result += result.substr( 0, result.size() - 2 ) + "}";
    return result;
}


