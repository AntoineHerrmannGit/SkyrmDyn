#include "colors.inc" 
#include "functions.inc"    
#include "math.inc"
                                  
//*****************************************************************************
// The coordinate axis follows the left hand rule with the z-axis pointing away
//*****************************************************************************

background { Gray25 }             // Colour of the background
                                       
//*****************************************************************************   
// Set the camera and the light source  
//*****************************************************************************
   
camera { location < 25.5, 25.5, 30.0 > look_at < 25.5, 25.5, 1.0 > }
light_source { < -2000.0, -3000.0, 100.0 > color White }

// Creates an arrow representing a spin    
#macro Spin( rx, ry, rz, sx, sy, sz ) 
object { 
    #local spin_x = sx / sqrt( sx*sx + sy*sy + sz*sz );  
    #local spin_y = sy / sqrt( sx*sx + sy*sy + sz*sz );
    #local spin_z = sz / sqrt( sx*sx + sy*sy + sz*sz );
     
    #local cyl_radius = 0.21;
    #local cyl_length = 0.075;
    
    #local cone_base_radius = 0.4; 
    #local cone_cap_radius = 0.2*cone_base_radius;
    #local cone_length = 0.4;  
                                     
    #local virtual_cone_hat_length = (cone_cap_radius*cone_length)/(cone_base_radius-cone_cap_radius);
    #local cone_angle = atan(cone_cap_radius/virtual_cone_hat_length);
    #local sphere_hat_radius = abs(cone_cap_radius/cos(cone_angle));
    #local sphere_hat_center = cone_length - sphere_hat_radius*sin(cone_angle);
    
    #local theta = acos( spin_z ); 
    #if (spin_x!=0)
        #local phi = atan2( spin_y, spin_x );     
    #else
        #local phi = pi/2;
    #end
    
    #if (spin_z >=0)
        #local color_rgb = <1, 1-spin_z, 1-spin_z>;
    #else
        #local color_rgb = <1+spin_z, 1+spin_z, 1>;
    #end  
    
    merge{  
        sphere {
            <0, 0, -cyl_length>, 
            cyl_radius  
            pigment {
                color color_rgb
            }
        }
        cylinder {
            <0, 0, -cyl_length>,      // base point
            <0, 0, 0>,                // cap point
            cyl_radius                // radius     
            pigment {               
                color color_rgb
            }
        }
        cone {
            <0, 0, 0>,                // base point
            cone_base_radius,         // base radius
            <0, 0, cone_length>,      // cap point
            cone_cap_radius           // cap radius      
            pigment {    
                color color_rgb
            }  
        }
        sphere {
            <0, 0, sphere_hat_center>, 
            sphere_hat_radius  
            pigment {  
                color color_rgb
            }
        }
    } 
    rotate <0, theta*180/pi, phi*180/pi>
    translate <rx, ry, rz>
}  
#end   

//*****************************************************************************
// Include all files from the /Povray_data_files/ directory and renders image  
//
// /!\ May produce only one superposed image -> use external script to 
//     generate each picture
//*****************************************************************************
                                                                                                 
#include "D:\Antoine\SkyrmDyn\C++\SkyrmDyn_Cpp\Outputs\Povray_data_files\spin_000000000002.dat"
