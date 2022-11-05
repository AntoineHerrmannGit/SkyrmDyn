#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#include <string>


class Plot
{
public:
    // Constructor
    //-----------------------------------
    Plot();

    // Getters
    //-----------------------------------
    std::string get_system();

    std::string get_python();
    std::string get_povray();

    std::string get_code();

    // Public library
    //-----------------------------------
    void setup_povray_file();

    void make_single_image( std::string spin_file );
    void make_all_images();

    void make_graphs();
    void make_animations();

    void plot_figures();

private:
    std::string system = "linux";

    std::string python = "C:\\Program Files\\Python39\\python.exe";
    std::string povray = "D:\\Povray\\bin\\pvengine.exe";

    std::string code = "D:\\Antoine\\SkyrmDyn\\C++\\SkyrmDyn_Cpp\\";

    void initialize();
};

#endif // SYSTEM_CONFIG_H
