import os

def setup_povray_file():
    input_file = open( "./SkyrmDyn_Cpp/inputs_config", "r" )
    file = input_file.readlines()
    for line in file:
        if line.find( "lattice_size = " ) != -1:
            sub_line = line[ 16:len(line)-2 ]
            lattice_size = sub_line.split()
            lattice_size[0] = float( lattice_size[0][ :len( lattice_size[0] )-1 ] )
            lattice_size[1] = float( lattice_size[1][ :len( lattice_size[1] )-1 ] )
            lattice_size[2] = float( lattice_size[2] )
            break
    input_file.close()
            
    look_at = [ 0.5*( lattice_size[0] + 1 ), 0.5*( lattice_size[1] + 1 ), 0.5*( lattice_size[2] + 1 ) ]
    position = [ 0.5*( lattice_size[0] + 1 ), 0.5*( lattice_size[1] + 1 ), 30*lattice_size[2] ]
    light = [ -40*lattice_size[0], -60*lattice_size[1], 100*lattice_size[2] ]
    
    camera = "camera { location < " + str( position[0] ) + ", " + str( position[1] ) + ", " + str( position[2] ) + " > look_at < " + str( look_at[0] ) + ", " + str( look_at[1] ) + ", " + str( look_at[2] ) + " > }\n"
    light_source = "light_source { < " + str( light[0] ) + ", " + str( light[1] ) + ", " + str( light[2] ) + " > color White }\n"
    
    povray_reader = open( "./SkyrmDyn_Cpp/Plotting/plot_spins.pov", "r" )
    povray_file = povray_reader.readlines()
    povray_reader.close()
    
    i = 0
    cpt = 0
    for line in povray_file:
        if cpt >= 2:
            break
        else:
            if line.find( "camera {" ) != -1:
                povray_file[i] = camera
                cpt += 1
            elif line.find( "light_source {" ) != -1:
                povray_file[i] = light_source
                cpt += 1
        i += 1
    
    povray_writer = open( "./SkyrmDyn_Cpp/Plotting/plot_spins_copy.pov", "w" )
    povray_writer.writelines( povray_file )
    povray_writer.close()
    
    os.remove( "./SkyrmDyn_Cpp/Plotting/plot_spins.pov" )
    os.rename( "./SkyrmDyn_Cpp/Plotting/plot_spins_copy.pov", "./SkyrmDyn_Cpp/Plotting/plot_spins.pov" )

if __name__ == "__main__":
    setup_povray_file()
