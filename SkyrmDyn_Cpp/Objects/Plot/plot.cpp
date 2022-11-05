#include "plot.h"

#include "Plotting/setup_povray_file.h"

#include "Inputs/Readers/system_reader.h"

// Constructor
//-----------------------------------
Plot::Plot()
{
    initialize();
}

// Getters
//-----------------------------------
std::string Plot::get_system() {
    return system;
}

std::string Plot::get_python() {
    return python;
}
std::string Plot::get_povray() {
    return povray;
}

std::string Plot::get_code() {
    return code;
}

void Plot::plot_figures() {
    //make_all_images();
    make_graphs();
    make_animations();
}

// Private library
//-----------------------------------
void Plot::initialize() {
    system = get_system_string( std::string( "system" ) );
    python = get_system_string( std::string( "python" ) );
    povray = get_system_string( std::string( "povray" ) );
    code = get_system_string( std::string( "code" ) );
    setup_povray_file();
}
