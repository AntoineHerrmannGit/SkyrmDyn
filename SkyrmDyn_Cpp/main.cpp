#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include <typeinfo>

#include <filesystem>

#include <ctime>
#include <random>
#include <chrono>

#include <cmath>

#include "File_management/file_management.h"

#include "Inputs/Readers/inputs_reader.h"

#include "Maths/Random/random.h"
#include "Maths/Objects/Matrix/Real_matrix/real_matrix.h"

#include "Maths/Functions/distribution_functions.h"
#include "Maths/Objects/Tensor/Vector_tensor/vector_tensors.h"

#include "Maths/Operators/vector_operators.h"

#include "Objects/Lattice/lattice.h"
#include "Objects/Parameter/parameter.h"
#include "Objects/Plot/plot.h"

#include "Plotting/setup_povray_file.h"


int main( /* int argc, char *argv[] */ )
{
    /*
    std::cout<<"Program start \n Clearing output directories \n";
    clear_output_directories();

    std::cout<<"Initializing lattice \n";
    Lattice lattice;

    std::cout<<"LLG evolution \n";
    int i=0;
    int nb_steps = lattice.get_parameter().get_llg_time() / lattice.get_parameter().get_llg_time_step();
    while( lattice.get_parameter().get_current_time() < lattice.get_parameter().get_llg_time() ) {
        lattice.euler_llg_evolution();
        std::cout<<"Step " + std::to_string( i ) + " / " + std::to_string( nb_steps ) + "\n";
    }
    */

    std::cout<<"Initializing plotter \n";
    Plot plot;

    std::cout<<"Plotting graphs and animations \n";
    plot.plot_figures();

    std::cout << "Well done \n";

    return 0;
}
