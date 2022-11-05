#include "inputs_reader.h"

#include "Maths/Objects/Array/Array_int/array_int.h"
#include "Maths/Objects/Array/Array_double/array_double.h"

#include "Error_messages/error_messages.h"

#include <string>
#include <fstream>
#include <iostream>

std::string get_parameter_as_string( std::string& parameter_to_find ) {
    std::string filename = "./SkyrmDyn_Cpp/inputs_config";
    std::ifstream read( filename );
    std::string line;
    std::string parameter;
    parameter_to_find += " = ";
    if( read.is_open() ) {
        // Read the file line by line
        while( std::getline( read, line ) ) {
            // If the name of the parameter is found
            if( line.find( parameter_to_find ) != std::string::npos ) {
                int parameter_length = parameter_to_find.size();
                int line_length = line.size();
                int length_of_value = line_length - parameter_length;
                // Extract the value of the parameter as a sub_string
                parameter = line.substr( parameter_length, length_of_value );
                break;
            }
        }
        read.close();
    }
    else{
        throw( UnfoudVariableError( "\"input_config\"") );//throw ( generate_assignation_error_message( std::string("file \"input_config\" not found") + __FILE__ + std::string("   ") + __FUNCTION__) );
    }
    return parameter;
}

std::string get_string( std::string name ) {
    name = get_parameter_as_string( name );
    name = name.substr( 1, (int) name.size() - 2 );
    return name;
}

int get_int( std::string name ) {
    name = get_parameter_as_string( name );
    int result = std::stoi( name );
    return result;
}

double get_double( std::string name ) {
    name = get_parameter_as_string( name );
    double result = std::stod( name );
    return result;
}

Array_int get_array_int( std::string name ) {
    name = get_parameter_as_string( name );
    int first_coma = name.find(',', 0);
    int second_coma = name.find(',', first_coma + 1);

    int x = stoi( name.substr( 1, first_coma - 1 ) );
    int y = stoi( name.substr( first_coma + 2, second_coma - 1 ) );
    int z = stoi( name.substr( second_coma + 2, (int) name.size() - 1) );

    Array_int result;
    result.set_component( 0, x );
    result.set_component( 1, y );
    result.set_component( 2, z );

    return result;
}

Array_double get_array_double( std::string name ) {
    name = get_parameter_as_string( name );
    int first_coma = name.find(',', 0);
    int second_coma = name.find(',', first_coma + 1);

    double x = stoi( name.substr( 1, first_coma - 1 ) );
    double y = stoi( name.substr( first_coma + 2, second_coma - 1 ) );
    double z = stoi( name.substr( second_coma + 2, (int) name.size() - 1) );

    Array_double result;
    result.set_component( 0, x );
    result.set_component( 1, y );
    result.set_component( 2, z );

    return result;
}

int find_nb_strings_in_string( std::string reference_string, std::string input_string ) {
    int nb_appear = 0;
    if( reference_string.find( input_string ) != std::string::npos ) {
        nb_appear += 1;
        int found = reference_string.find( input_string );
        while( reference_string.find( input_string, found+1 ) != std::string::npos ) {
            nb_appear += 1;
            found = reference_string.find( input_string );
        }
        return nb_appear;
    }
    else {
        return nb_appear;
    }
}
