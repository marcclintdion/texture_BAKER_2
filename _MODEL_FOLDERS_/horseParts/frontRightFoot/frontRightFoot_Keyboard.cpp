    //=======================================================================================                                           
    if (keys['J'])                                                                                                                      
    {                                                                                                                                   
             frontRightFoot_POSITION[0]         -=  .005;                                                                                  
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_POSITION[0]         +=  .005;                                                                                  
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_POSITION[1]         +=  .005;                                                                                  
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_POSITION[1]         -=  .005;                                                                                  
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_POSITION[2]         +=  .005;                                                                                  
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_POSITION[2]         -=  .005;                                                                                  
    }                                                                                                                                   
    //=======================================================================================                                           
    //=======================================================================================                                           
   /*  if (keys['J'])                                                                                                                   
    {                                                                                                                                   
             frontRightFoot_LIGHT_POSITION_01[0]         -=  .11;                                                                         
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_LIGHT_POSITION_01[0]         +=  .11;                                                                            
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_LIGHT_POSITION_01[1]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_LIGHT_POSITION_01[1]         -=  .11;                                                                            
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_LIGHT_POSITION_01[2]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_LIGHT_POSITION_01[2]         -=  .11;                                                                            
    } */                                                                                                                                
    //=======================================================================================                                           
    if (keys['M'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_ATTENUATION                  +=  .005;                                                                            
    }	                                                                                                                                  
    if (keys['N'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_ATTENUATION                  -=  .005;                                                                            
    }                                                                                                                                   
    if (keys['X'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_SHININESS                  +=  1.005;                                                                            
    }	                                                                                                                                  
    if (keys['Z'])                                                                                                                      
    {	                                                                                                                                  
             frontRightFoot_SHININESS                  -=  1.005;                                                                                       
    }                                                                                                                                            
    if (keys[VK_F8]) 			                                                                                                                   
	{                                                                                                                                              
        ofstream outKeys("_MODEL_FOLDERS_/horseParts/frontRightFoot/frontRightFoot_SHADER_SETTINGS.cpp");                                                                                     
        outKeys << "  GLfloat     frontRightFoot_POSITION[] = {" << frontRightFoot_POSITION[0] << ", "                               
                                                                       << frontRightFoot_POSITION[1] << ", "                               
                                                                       << frontRightFoot_POSITION [2] << ", " << 1.0 << "};\n";          
        outKeys << "  GLfloat     frontRightFoot_ATTENUATION         =  " << frontRightFoot_ATTENUATION   << ";\n";                                    
        outKeys << "  GLfloat     frontRightFoot_SHININESS           =  " << frontRightFoot_SHININESS  << ";\n";                                       
    }                                                                                                                                            
