import matplotlib.pyplot as plt
import os

def Remove_figures() :
    list_of_figures = [ "energy.png",
                        "energy.pdf",
                        "magnetization.png",
                        "magnetization.pdf",
                        "temperature.png",
                        "temperature.pdf",
                        "topological_charge.png",
                        "topological_charge.pdf" ]
    
    for file in list_of_figures :
        if os.path.exists( file ) :
            os.remove( file )


def Plot_energy() :
    file = open( os.path.join( "Outputs\Energy\energy.dat"), "r" )
    
    time = []
    energy = []
    
    for row in file :
        row = row.split( "   " )
        time.append( float( row[0] ) )
        energy.append( float( row[1] ) )
    
    file.close()
    
    fig, ax = plt.subplots(1,1)
    ax.plot( time, energy, color='Black', linewidth= 2 )
    # ax1.axes.get_yaxis().set_visible(False)
    # ax.axes.yaxis.set_ticklabels([])
    plt.xlim( min(time), max(time) )
    plt.ylim( 1.1*min(energy), 1.1*max(energy) )
    # plt.legend(loc = 'lower right', fontsize = 'large')
    plt.xlabel( "Time (fs)" )
    plt.ylabel( "Energy (eV) " )
    # plt.title( "Energy with respect to time" )
    # plt.show()
    fig.savefig("energy.pdf", bbox_inches='tight')
    fig.savefig("energy.png", bbox_inches='tight')
    

def Plot_magnetization_components() :
    file = open( os.path.join( "Outputs\Magnetization\magnetization.dat" ), "r" )
    
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
    
    fig, ax = plt.subplots(1,1)
    ax.plot( time, mx, color='DarkGrey', linewidth= 2, label="Mx" )
    ax.plot( time, my, color='Grey', linewidth= 2, label="My" )
    ax.plot( time, mz, color='Black', linewidth= 2, label="Mz" )
    # ax1.axes.get_yaxis().set_visible(False)
    # ax.axes.yaxis.set_ticklabels([])
    plt.xlim( min(time), max(time) )
    plt.ylim( -1.1, 1.1 )
    plt.legend(loc = 'lower right', fontsize = 'large')
    plt.xlabel( "Time (fs)" )
    plt.ylabel( "Magnetization components ( a.u. ) " )
    # plt.title( "Magnetization components with respect to time" )
    # plt.show()
    fig.savefig("magnetization.pdf", bbox_inches='tight')
    fig.savefig("magnetization.png", bbox_inches='tight')
    

def Plot_3D_magnetization() :
    file = open( os.path.join( "Outputs\Magnetization\magnetization.dat" ), "r" )
    
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
    
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    ax.plot3D(mx, my, mz, 'red')
    
    ax.set_xlim( -1, 1 ) 
    ax.set_ylim( -1, 1 ) 
    ax.set_zlim( -1, 1 ) 
    
    ax.set_xlabel("Mx ( a.u. )")
    ax.set_ylabel("My ( a.u. )")
    ax.set_zlabel("Mz ( a.u. )")
    
    # plt.title( "Magnetization under LLG equation with respect to time" )
    
    fig.savefig("magnetization_3D.pdf", bbox_inches='tight')
    fig.savefig("magnetization_3D.png", bbox_inches='tight')


def Plot_temperature() :
    file = open( os.path.join( "Outputs\Temperature\temperature.dat" ), "r" )
    
    time = []
    temperature = []
    
    for row in file :
        row = row.split( "   " )
        time.append( float( row[0] ) )
        temperature.append( float( row[1] ) )
    
    file.close()
    
    fig, ax = plt.subplots(1,1)
    ax.plot( time, temperature, color='Black', linewidth= 2 )
    # ax1.axes.get_yaxis().set_visible(False)
    # ax.axes.yaxis.set_ticklabels([])
    plt.xlim( min(time), max(time) )
    plt.ylim( 0, 1.1*max(temperature) )
    # plt.legend(loc = 'lower right', fontsize = 'large')
    plt.xlabel( "Time (fs)" )
    plt.ylabel( "Temperature (K) " )
    # plt.title( "Temperature with respect to time" )
    # plt.show()
    fig.savefig("temperature.pdf", bbox_inches='tight')
    fig.savefig("temperature.png", bbox_inches='tight')


def Plot_topological_charge() :
    file = open( os.path.join( "Outputs\Topological_charge\topological_charge.dat" ), "r" )
    
    time = []
    topological_charge = []
    
    for row in file :
        row = row.split( "   " )
        time.append( float( row[0] ) )
        topological_charge.append( float( row[1] ) )
    
    file.close()
    
    fig, ax = plt.subplots(1,1)
    ax.plot( time, topological_charge, color='Black', linewidth= 2 )
    # ax1.axes.get_yaxis().set_visible(False)
    # ax.axes.yaxis.set_ticklabels([])
    plt.xlim( min(time), max(time) )
    plt.ylim( min( -1, min(topological_charge) - 1 ), max( 1, max(topological_charge) + 1 ) )
    # plt.legend(loc = 'lower right', fontsize = 'large')
    plt.xlabel( "Time (fs)" )
    plt.ylabel( "Topological charge (a.u.) " )
    # plt.title( "Topological charge with respect to time" )
    # plt.show()
    fig.savefig("topological_charge.pdf", bbox_inches='tight')
    fig.savefig("topological_charge.png", bbox_inches='tight')

if __name__ == "__main__":
    Remove_figures()
    Plot_energy()
    Plot_magnetization_components()
    Plot_3D_magnetization()
    # Plot_temperature()
    # Plot_topological_charge()





