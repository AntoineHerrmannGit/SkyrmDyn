#include "Objects/Plot/plot.h"

#include "Error_messages/error_messages.h"

#include <string>

void Plot::make_graphs() {
    if( system == "windows" ) {
        std::string graph_cmd = "\"\"" + python + "\" \"" + code + "SkyrmDyn_Cpp\\Plotting\\make_graphs.py\"\"";
        std::system( graph_cmd.c_str() );
    }
    else if( system == "linux" || system == "macos" ) {
        std::string graph_cmd = "python3 " + code + "SkyrmDyn_Cpp\\Plotting\\make_graphs.py";
        std::system( graph_cmd.c_str() );
    }
    else {
        throw DeclarationError( "system" );
    }

    std::string old_name = ".\\energy.png";
    std::string new_name = ".\\Outputs\\Graphs\\energy.png";
    std::rename( old_name.c_str(), new_name.c_str() );

    old_name = ".\\energy.pdf";
    new_name = ".\\Outputs\\Graphs\\energy.pdf";
    std::rename( old_name.c_str(), new_name.c_str() );

    old_name = ".\\magnetization.pdf";
    new_name = ".\\Outputs\\Graphs\\magnetization.pdf";
    std::rename( old_name.c_str(), new_name.c_str() );

    old_name = ".\\magnetization.png";
    new_name = ".\\Outputs\\Graphs\\magnetization.png";
    std::rename( old_name.c_str(), new_name.c_str() );

    old_name = ".\\magnetization_3D.pdf";
    new_name = ".\\Outputs\\Graphs\\magnetization_3D.pdf";
    std::rename( old_name.c_str(), new_name.c_str() );

    old_name = ".\\magnetization_3D.png";
    new_name = ".\\Outputs\\Graphs\\magnetization_3D.png";
    std::rename( old_name.c_str(), new_name.c_str() );
}



