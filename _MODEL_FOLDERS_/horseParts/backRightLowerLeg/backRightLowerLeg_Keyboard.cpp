    //=======================================================================================                                           
    if (keys['J'])                                                                                                                      
    {                                                                                                                                   
             backRightLowerLeg_POSITION[0]         -=  .01;                                                                                  
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_POSITION[0]         +=  .01;                                                                                  
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_POSITION[1]         +=  .01;                                                                                  
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_POSITION[1]         -=  .01;                                                                                  
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_POSITION[2]         +=  .01;                                                                                  
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_POSITION[2]         -=  .01;                                                                                  
    }                                                                                                                                  
    //=======================================================================================                                           
    //=======================================================================================                                           
     if (keys['J'])                                                                                                                   
    {                                                                                                                                   
             backRightLowerLeg_LIGHT_POSITION_01[0]         -=  .11;                                                                         
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_LIGHT_POSITION_01[0]         +=  .11;                                                                            
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_LIGHT_POSITION_01[1]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_LIGHT_POSITION_01[1]         -=  .11;                                                                            
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_LIGHT_POSITION_01[2]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_LIGHT_POSITION_01[2]         -=  .11;                                                                            
    }                                                                                                                                 
    //=======================================================================================                                           
    if (keys['M'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_ATTENUATION                  +=  .01;                                                                            
    }	                                                                                                                                  
    if (keys['N'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_ATTENUATION                  -=  .01;                                                                            
    }                                                                                                                                   
    if (keys['X'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_SHININESS                  +=  1.01;                                                                            
    }	                                                                                                                                  
    if (keys['Z'])                                                                                                                      
    {	                                                                                                                                  
             backRightLowerLeg_SHININESS                  -=  1.01;                                                                                       
    }                                                                                                                                            
    if (keys[VK_F8]) 			                                                                                                                   
	{                                                                                                                                              
        ofstream outKeys("_MODEL_FOLDERS_/horseParts/backRightLowerLeg/backRightLowerLeg_SHADER_SETTINGS.cpp");                                                                                     
        outKeys << "  GLfloat     backRightLowerLeg_POSITION[] = {" << backRightLowerLeg_POSITION[0] << ", "                               
                                                                       << backRightLowerLeg_POSITION[1] << ", "                               
                                                                       << backRightLowerLeg_POSITION[2] << ", " << 1.0 << "};\n";          
        outKeys << "  GLfloat     backRightLowerLeg_ATTENUATION         =  " << backRightLowerLeg_ATTENUATION   << ";\n";                                    
        outKeys << "  GLfloat     backRightLowerLeg_SHININESS           =  " << backRightLowerLeg_SHININESS  << ";\n";                                       
    }                                                                                                                                            
