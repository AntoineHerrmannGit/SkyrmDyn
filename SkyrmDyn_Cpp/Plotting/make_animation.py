from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

import os

from moviepy.editor import VideoClip
from moviepy.video.io.bindings import mplfig_to_npimage

from moviepy.editor import ImageSequenceClip, VideoClip
  
def Animate_spins():
    print( "Animation of the spins lattice ----- start." )
    
    if os.path.exists( "spin_dynamics.mp4" ) :
        os.remove( "spin_dynamics.mp4" )
            
    # Put all images in the list
    list_of_images = os.listdir( "./Outputs/Images/" )
    
    i = 0
    for file in list_of_images :
        list_of_images[i] = "./Outputs/Images/" + file
        i += 1
    
    clip = ImageSequenceClip( list_of_images, fps = 20 )
    clip.write_videofile( "spin_dynamics.mp4" )
    
    print( "Animation of the spins lattice ----- done." )

def Animate_magnetization():
    print( "Animation of the Magnetization ----- start." )
    
    if os.path.exists( "magnetization_dynamics.mp4" ) :
        os.remove( "magnetization_dynamics.mp4" )
    
    file = open( os.path.join( ".\Outputs\Magnetization\magnetization.dat" ), "r" )
    nb_frames = sum( 1 for line in file )
    
    fps = 20
    duration = nb_frames / fps
    
    frame = [0]
    def make_frame( t ):
        # Gather datas
        file = open( os.path.join( ".\Outputs\Magnetization\magnetization.dat" ), "r" )
    
        time = []
        mx = []
        my = []
        mz = []
    
        for row in file :
            row = row.split( "   " )
            time.append( float( row[0] ) )
            mx.append( float( row[1] ) )
            my.append( float( row[2] ) )
            mz.append( float( row[3] ) )
    
        file.close()
        
    
        # matplot subplot
        fig = plt.figure()
        fig.set_size_inches(12, 12)
        ax = fig.add_subplot(111, projection='3d')
        
        def create_frame( fig, mx, my, mz, t, frame ):
            # Clear previous datas
            ax.clear()
            
            ax.plot3D(mx[:frame[0]], my[:frame[0]], mz[:frame[0]], 'red')
        
            ax.set_xlim( -1, 1 ) 
            ax.set_ylim( -1, 1 ) 
            ax.set_zlim( -1, 1 ) 
            
            ax.set_xlabel("Mx ( a.u. )")
            ax.set_ylabel("My ( a.u. )")
            ax.set_zlabel("Mz ( a.u. )")
            
            # returning numpy image
            return mplfig_to_npimage( fig )
        
        frame[0] += 1
        return create_frame( fig, mx, my, mz, t, frame )
    
    # creating animation
    clip = VideoClip( make_frame, duration=duration )
    clip.write_videofile( "magnetization_dynamics.mp4", fps=fps )
    
    print( "Animation of the Magnetization ----- done." )      

def Animate_magnetization_components():
    print( "Animation of the Magnetization components ----- start." )

    if os.path.exists( "magnetization_components_dynamics.mp4" ) :
        os.remove( "magnetization_component_dynamics.mp4" )

    file = open( os.path.join( ".\Outputs\Magnetization\magnetization.dat" ), "r" )
    nb_frames = sum( 1 for line in file )

    fps = 20
    duration = nb_frames / fps

    frame = [0]
    def make_frame( t ):
        # Gather datas
        file = open( os.path.join( ".\Outputs\Magnetization\magnetization.dat" ), "r" )

        time = []
        mx = []
        my = []
        mz = []

        for row in file :
            row = row.split( "   " )
            time.append( float( row[0] ) )
            mx.append( float( row[1] ) )
            my.append( float( row[2] ) )
            mz.append( float( row[3] ) )

        file.close()


        # matplot subplot
        fig, ax = plt.subplots(1,1)

        def create_frame( fig, mx, my, mz, time, t, frame ):
            # Clear previous datas
            ax.clear()

            ax.plot( time[:frame[0]], mx[:frame[0]], color='DarkGrey', linewidth= 2, label="Mx" )
            ax.plot( time[:frame[0]], my[:frame[0]], color='Grey', linewidth= 2, label="My" )
            ax.plot( time[:frame[0]], mz[:frame[0]], color='Black', linewidth= 2, label="Mz" )

            plt.xlim( min(time), max(time) )
            plt.ylim( -1.1, 1.1 )
            plt.legend(loc = 'lower right', fontsize = 'large')
            plt.xlabel( "Time (fs)" )
            plt.ylabel( "Magnetization components ( a.u. ) " )

            # returning numpy image
            return mplfig_to_npimage( fig )

        frame[0] += 1
        return create_frame( fig, mx, my, mz, time, t, frame )

    # creating animation
    clip = VideoClip( make_frame, duration=duration )
    clip.write_videofile( "magnetization_component_dynamics.mp4", fps=fps )

def Animate_energy():
    print( "Animation of the Energy ----- start." )
    
    if os.path.exists( "energy_dynamics.mp4" ) :
        os.remove( "energy_dynamics.mp4" )
    
    file = open( os.path.join( ".\Outputs\Energy\energy.dat" ), "r" )
    nb_frames = sum( 1 for line in file )
    
    fps = 20
    duration = nb_frames / fps
    
    frame = [0]
    def make_frame( t ):
        # Gather datas
        file = open( os.path.join( ".\Outputs\Energy\energy.dat" ), "r" )
    
        time = []
        energy = []
    
        for row in file :
            row = row.split( "   " )
            time.append( float( row[0] ) )
            energy.append( float( row[1] ) )
    
        file.close()
        
    
        # matplot subplot
        fig, ax = plt.subplots(1,1)
        
        def create_frame( fig, energy, time, t, frame ):
            # Clear previous datas
            ax.clear()
                
            ax.plot( time[:frame[0]], energy[:frame[0]], color='Black', linewidth= 2, label="Energy" )
    
            plt.xlim( min(time), max(time) )
            plt.ylim( 1.1*min( energy ), 1.1*max( energy ) )
            plt.legend(loc = 'lower right', fontsize = 'large')
            plt.xlabel( "Time (fs)" )
            plt.ylabel( "Energy (eV) " )                                                    
            
            # returning numpy image
            return mplfig_to_npimage( fig )
        
        frame[0] += 1
        return create_frame( fig, energy, time, t, frame )
    
    # creating animation
    clip = VideoClip( make_frame, duration=duration )
    clip.write_videofile( "energy_dynamics.mp4", fps=fps )
    
    print( "Animation of the Energy ----- done." )
    
if __name__ == "__main__":
    Animate_spins()
    Animate_magnetization()
    Animate_magnetization_components()
    Animate_energy()
