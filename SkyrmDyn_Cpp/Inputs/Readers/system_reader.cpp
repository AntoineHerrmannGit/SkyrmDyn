#include "system_reader.h"

#include "Error_messages/error_messages.h"

#include <string>
#include <fstream>
#include <iostream>

std::string get_system_as_string( std::string& parameter_to_find ) {
    std::string filename = "./SkyrmDyn_Cpp/inputs_system";
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
        throw( UnfoudVariableError( "\"systems_config\"") );//throw ( generate_assignation_error_message( std::string("file \"input_config\" not found") + __FILE__ + std::string("   ") + __FUNCTION__) );
    }
    return parameter;
}

std::string get_system_string( std::string name ) {
    name = get_system_as_string( name );
    name = name.substr( 1, (int) name.size() - 2 );
    return name;
}
