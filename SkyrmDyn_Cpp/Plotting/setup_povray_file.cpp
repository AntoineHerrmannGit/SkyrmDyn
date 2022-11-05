#include "Objects/Plot/plot.h"

#include "Plotting/setup_povray_file.h"

#include "Error_messages/error_messages.h"

#include "Inputs/Readers/inputs_reader.h"

#include "setup_povray_file.h"

#include "Maths/Objects/Array/Array_int/array_int.h"

#include "Inputs/Readers/inputs_reader.h"

#include "File_management/file_management.h"

#include <string>
#include <fstream>
#include <iostream>

#include <cmath>

void Plot::setup_povray_file() {
    std::string cmd = "\"\"" + python + "\" \"" + code + "SkyrmDyn_Cpp\\Plotting\\setup_povray_file.py\"\"";
    std::system( cmd.c_str() );
    /*
    set_camera();
    set_light_source();
    */
}

void move_pov_and_include_spin_file( std::string filename ) {
    move_file( "plot_spins.pov", "./SkyrmDyn_Cpp/Plotting/", "./Outputs/Povray_data_files/" );
    replace_line_in_file( "./Outputs/Povray_data_files/plot_spins.pov", "#include \"input_file.dat\"", "#include \"" + filename + "\"" );
}

void set_camera() {
    Array_int lattice_size = get_array_int( "lattice_size" );
    float x = lattice_size.get_x();
    float y = lattice_size.get_y();
    float z = lattice_size.get_z();

    float look_x = 0.5*x;
    float look_y = 0.5*y;
    float look_z = 0.5*z;

    x = -0.25*x;
    y = -0.4*y;
    z = 2*z;

    std::string old_line;
    std::ifstream read( "./SkyrmDyn_Cpp/Plotting/plot_spins.pov" );
    bool success = false;
    if( read ) {
        // Read the file line by line
        while( std::getline( read, old_line ) ) {
            // If the name of the line containing the parameter is found
            if( old_line.find( "camera {" ) != std::string::npos ) {
                success = true;
                break;
            }
        }
        if( !success ) {
            throw( OperationError( "finding", "old_line" ) );
        }
    }
    else {
        throw( DeclarationError( "\"read\"" ) );
    }

    std::string new_line = "camera { location < " + std::to_string(x) + ", "
                                                  + std::to_string(y) + ", "
                                                  + std::to_string(z) + " > look_at < "
                                                  + std::to_string(look_x) + ", "
                                                  + std::to_string(look_y) + ", "
                                                  + std::to_string(look_z) + " > }";

    replace_line_in_file( old_line, new_line, "./SkyrmDyn_Cpp/Plotting/plot_spins.pov" );
}

void set_light_source() {
    Array_int lattice_size = get_array_int( "lattice_size" );
    int l=0;
    for( int i=0; i<lattice_size.get_dimension(); i++ ) {
        l += lattice_size.get_component( i );
    }
    float x = -40*l;
    float y = -60*l;
    float z = 100*l;

    std::string old_line;
    std::ifstream read( "./SkyrmDyn_Cpp/Plotting/plot_spins.pov" );
    bool success = false;
    if( read ) {
        // Read the file line by line
        while( std::getline( read, old_line ) ) {
            // If the name of the line containing the parameter is found
            if( old_line.find( "light_source {" ) != std::string::npos ) {
                success = true;
                break;
            }
        }
        if( !success ) {
            throw( OperationError( "finding", "old_line" ) );
        }
    }
    else {
        throw( DeclarationError( "\"read\"" ) );
    }

    std::string new_line = "light_source { location < " + std::to_string(x) + ", "
                                                        + std::to_string(y) + ", "
                                                        + std::to_string(z) + " > color White }";

    replace_line_in_file( old_line, new_line, "./SkyrmDyn_Cpp/Plotting/plot_spins.pov" );
}

void write_nb_povray_files() {
    double llg_time = get_double( "llg_time" );
    double llg_time_step = get_double( "llg_time_step" );

    std::string filename = "./SkyrmDyn_Cpp/Plotting/plot_spins.pov";
    std::string new_line = "#declare nb_files = " + std::to_string( (int) round( llg_time / llg_time_step ) ) + ";";
    std::string line_to_find =  "#declare nb_files = ";
    std::ifstream read( filename );
    std::ofstream write( filename );

    std::string line;
    std::string tmp;
    if( read && write ) {
        // Read the file line by line
        while( std::getline( read, line ) ) {
            // If the name of the line containing the parameter is found
            if( line.find( line_to_find ) != std::string::npos ) {
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


