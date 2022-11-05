#include "Objects/Plot/plot.h"

#include "Error_messages/error_messages.h"

#include <string>

void Plot::make_animations() {
    if( system == "windows" ) {
        std::string cmd = "\"\"" + python + "\" \"" + code + "SkyrmDyn_Cpp\\Plotting\\make_animation.py\"\"";
        std::system( cmd.c_str() );
    }
    else if( system == "linux" || system == "macos" ) {
        std::string cmd = "python3 " + code + "SkyrmDyn_Cpp\\Plotting\\make_animation.py";
        std::system( cmd.c_str() );
    }
    else {
        throw DeclarationError( "system" );
    }

    std::string old_name = ".\\spin_dynamics.mp4";
    std::string new_name = ".\\Outputs\\Animations\\spin_dynamics.mp4";
    std::rename( old_name.c_str(), new_name.c_str() );

    old_name = ".\\magnetization_dynamics.mp4";
    new_name = ".\\Outputs\\Animations\\magnetization_dynamics.mp4";
    std::rename( old_name.c_str(), new_name.c_str() );

    old_name = ".\\magnetization_components_dynamics.mp4";
    new_name = ".\\Outputs\\Animations\\magnetization_components_dynamics.mp4";
    std::rename( old_name.c_str(), new_name.c_str() );

    old_name = ".\\energy_dynamics.mp4";
    new_name = ".\\Outputs\\Animations\\energy_dynamics.mp4";
    std::rename( old_name.c_str(), new_name.c_str() );
}
