    //=======================================================================================                                           
    if (keys['J'])                                                                                                                      
    {                                                                                                                                   
             frontRightUpperLeg_POSITION[0]         -=  .005;                                                                                  
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_POSITION[0]         +=  .005;                                                                                  
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_POSITION[1]         +=  .005;                                                                                  
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_POSITION[1]         -=  .005;                                                                                  
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_POSITION[2]         +=  .005;                                                                                  
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_POSITION[2]         -=  .005;                                                                                  
    }                                                                                                                                   
    //=======================================================================================                                           
    //=======================================================================================                                           
 /*    if (keys['J'])                                                                                                                   
    {                                                                                                                                   
             frontRightUpperLeg_LIGHT_POSITION_01[0]         -=  .11;                                                                         
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_LIGHT_POSITION_01[0]         +=  .11;                                                                            
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_LIGHT_POSITION_01[1]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_LIGHT_POSITION_01[1]         -=  .11;                                                                            
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_LIGHT_POSITION_01[2]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_LIGHT_POSITION_01[2]         -=  .11;                                                                            
    } 
    
    */                                                                                                                                
    //=======================================================================================                                           
    if (keys['M'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_ATTENUATION                  +=  .005;                                                                            
    }	                                                                                                                                  
    if (keys['N'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_ATTENUATION                  -=  .005;                                                                            
    }                                                                                                                                   
    if (keys['X'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_SHININESS                  +=  1.005;                                                                            
    }	                                                                                                                                  
    if (keys['Z'])                                                                                                                      
    {	                                                                                                                                  
             frontRightUpperLeg_SHININESS                  -=  1.005;                                                                                       
    }                                                                                                                                            
    if (keys[VK_F8]) 			                                                                                                                   
	{                                                                                                                                              
        ofstream outKeys("_MODEL_FOLDERS_/horseParts/frontRightUpperLeg/frontRightUpperLeg_SHADER_SETTINGS.cpp");                                                                                     
        outKeys << "  GLfloat     frontRightUpperLeg_POSITION[] = {" << frontRightUpperLeg_POSITION[0] << ", "                               
                                                                       << frontRightUpperLeg_POSITION[1] << ", "                               
                                                                       << frontRightUpperLeg_POSITION [2] << ", " << 1.0 << "};\n";          
      
        outKeys << "  GLfloat     frontRightUpperLeg_ATTENUATION         =  " << frontRightUpperLeg_ATTENUATION   << ";\n";                                    
        outKeys << "  GLfloat     frontRightUpperLeg_SHININESS           =  " << frontRightUpperLeg_SHININESS  << ";\n";                                       
    }                                                                                                                                            
