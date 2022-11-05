QT -= gui

CONFIG += c++20 console
CONFIG -= app_bundle

QMAKE_LFLAGS += -fopenmp
QMAKE_CXXLFLAGS += -fopenmp

LIBS += -fopenmp

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        File_management/file_management.cpp \
        Hamiltonian/Fields/Temperature/temperature_field.cpp \
        Hamiltonian/Interactions/anisotropy.cpp \
        Hamiltonian/Interactions/biquadratic.cpp \
        Hamiltonian/Interactions/dipole.cpp \
        Hamiltonian/Interactions/dmi.cpp \
        Hamiltonian/Interactions/four_spins.cpp \
        Hamiltonian/Interactions/heisenberg.cpp \
        Hamiltonian/Interactions/zeeman.cpp \
        Hamiltonian/Fields/Effective_fields/effective_magnetic_field.cpp \
        Inputs/Readers/inputs_reader.cpp \
        Inputs/Readers/system_reader.cpp \
        Inputs/Writers/inputs_writer.cpp \
        LLG/ILLG/illg.cpp \
        LLG/LL/ll.cpp \
        LLG/LL/ll_rk4.cpp \
        LLG/LLG/llg.cpp \
        LLG/LLG/llg_rk4.cpp \
        LLG/llg_evolution.cpp \
        Maths/Functions/distribution_functions.cpp \
        Maths/Functions/bessel.cpp \
        Maths/Functions/special.cpp \
        Maths/Objects/Array/Array_double/array_double.cpp \
        Maths/Objects/Array/Array_float/array_float.cpp \
        Maths/Objects/Array/Array_int/array_int.cpp \
        Maths/Objects/Matrix/Complex_matrix/complex_matrix.cpp \
        Maths/Objects/Matrix/Real_matrix/inverse.cpp \
        Maths/Objects/Matrix/Real_matrix/real_matrix.cpp \
        Maths/Objects/Tensor/Tensor_3D/tensor_3d.cpp \
        Maths/Objects/Tensor/Vector_tensor/vector_tensors.cpp \
        Maths/Operators/vector_operators.cpp \
        Maths/Random/random.cpp \
        Objects/Atom/Outputs/outputs.cpp \
        Objects/Atom/Relative/relative.cpp \
        Objects/Atom/atom.cpp \
        Objects/Cell/Create_cell/create_cell.cpp \
        Objects/Cell/Create_cell/locate_cell.cpp \
        Objects/Cell/cell.cpp \
        Objects/Lattice/Boundary_conditions/boundary_conditions.cpp \
        Objects/Lattice/Energy/energy.cpp \
        Objects/Lattice/Neighbors/neighbors.cpp \
        Objects/Lattice/Observables/total_energy.cpp \
        Objects/Lattice/Observables/total_magnetization.cpp \
        Objects/Lattice/Outputs/output.cpp \
        Objects/Lattice/Setup/setup_atomic_memory.cpp \
        Objects/Lattice/Setup/setup_lattice_configuration.cpp \
        Objects/Lattice/Setup/setup_spin_configuration.cpp \
        Objects/Lattice/Setup/setup_spin_skyrmion_configuration.cpp \
        Objects/Lattice/lattice.cpp \
        Objects/Parameter/parameter.cpp \
        Objects/Plot/plot.cpp \
        Plotting/make_animation.cpp \
        Plotting/make_graphs.cpp \
        Plotting/make_images.cpp \
        Plotting/setup_povray_file.cpp \
        Symmetries/Local_symmetries/local_symmetries.cpp \
        Topology/topological_cell.cpp \
        Topology/topology.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Constants/constants.h \
    Error_messages/error_messages.h \
    File_management/file_management.h \
    Hamiltonian/Fields/Temperature/temperature_field.h \
    Hamiltonian/Interactions/anisotropy.h \
    Hamiltonian/Interactions/biquadratic.h \
    Hamiltonian/Interactions/dipole.h \
    Hamiltonian/Interactions/dmi.h \
    Hamiltonian/Interactions/four_spins.h \
    Hamiltonian/Interactions/heisenberg.h \
    Hamiltonian/Interactions/zeeman.h \
    Hamiltonian/Fields/Effective_fields/effective_magnetic_field.h \
    Inputs/Readers/inputs_reader.h \
    Inputs/Readers/system_reader.h \
    Inputs/Writers/inputs_writer.h \
    LLG/ILLG/illg.h \
    LLG/LL/ll.h \
    LLG/LLG/llg.h \
    Maths/Functions/distribution_functions.h \
    Maths/Functions/bessel.h \
    Maths/Functions/special.h \
    Maths/Objects/Array/Array_double/array_double.h \
    Maths/Objects/Array/Array_float/array_float.h \
    Maths/Objects/Array/Array_int/array_int.h \
    Maths/Objects/Matrix/Complex_matrix/complex_matrix.h \
    Maths/Objects/Matrix/Real_matrix/real_matrix.h \
    Maths/Objects/Tensor/Tensor_3D/tensor_3d.h \
    Maths/Objects/Tensor/Vector_tensor/vector_tensors.h \
    Maths/Operators/vector_operators.h \
    Maths/Random/random.h \
    Objects/Atom/atom.h \
    Objects/Cell/cell.h \
    Objects/Lattice/Boundary_conditions/boundary_conditions.h \
    Objects/Lattice/lattice.h \
    Objects/Parameter/parameter.h \
    Objects/Plot/plot.h \
    Plotting/setup_povray_file.h \
    Symmetries/Local_symmetries/local_symmetries.h \
    Topology/topological_cell.h

DISTFILES += \
    Plotting/setup_povray_file.py \
    Plotting/make_graphs.py \
    Plotting/make_animation.py \
    Plotting/plot_spins.pov \
    inputs_config \
    inputs_system

