#include "Objects/Plot/plot.h"

#include "Error_messages/error_messages.h"

#include "File_management/file_management.h"

#include "Plotting/setup_povray_file.h"

#include <string>
#include <filesystem>

void Plot::make_single_image( std::string spin_file ) {
    std::string old_line = "#include \"spin_file_to_include\"";
    std::string new_line = "#include \"" + std::filesystem::absolute( std::filesystem::path( spin_file ) ).string() + "\"";
    replace_line_in_file( old_line, new_line, ".\\SkyrmDyn_Cpp\\Plotting\\plot_spins.pov" );

    if( system == "windows" ) {
        std::string make_povray_image = "\"" + povray + " /EXIT /RENDER \"" + std::filesystem::absolute( std::filesystem::path( ".\\SkyrmDyn_Cpp\\Plotting\\plot_spins.pov" ) ).string() + "\"";
        std::system( make_povray_image.c_str() );
    }
    else if( system == "linus" || system == "macos" ) {
        std::string make_povray_image = "\"" + povray + " /EXIT /RENDER \"" + std::filesystem::absolute( std::filesystem::path( ".\\SkyrmDyn_Cpp\\Plotting\\plot_spins.pov" ) ).string() + "\"";
        std::system( make_povray_image.c_str() );
    }
    else {
        throw DeclarationError( "system" );
    }

    replace_line_in_file( new_line, old_line, ".\\SkyrmDyn_Cpp\\Plotting\\plot_spins.pov" );
}

void Plot::make_all_images() {
    setup_povray_file();
    const std::filesystem::path directory{"./Outputs/Povray_data_files/"};
    int i=0;
    for (auto const& dir_entry : std::filesystem::directory_iterator{directory})
        {
            std::string spin_file = dir_entry.path().string();
            make_single_image( spin_file );
            std::string old_name = ".\\SkyrmDyn_Cpp\\Plotting\\plot_spins.png";
            std::string new_name = ".\\Outputs\\Images\\img_" + std::string( "000000000000" ).substr( std::to_string( i ).size() ) + std::to_string( i ) + std::string( ".png" );
            std::rename( old_name.c_str(), new_name.c_str() );
            i++;
        }
}



