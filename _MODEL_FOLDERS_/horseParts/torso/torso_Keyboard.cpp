    //=======================================================================================                                           
  /*  if (keys['J'])                                                                                                                      
    {                                                                                                                                   
             torso_POSITION[0]         -=  .001;                                                                                  
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[0]         +=  .001;                                                                                  
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[1]         +=  .001;                                                                                  
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[1]         -=  .001;                                                                                  
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[2]         +=  .001;                                                                                  
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[2]         -=  .001;                                                                                  
    }    */                                                                                                                               
    //=======================================================================================                                           
    //=======================================================================================                                           
     if (keys['J'])                                                                                                                   
    {                                                                                                                                   
             torso_LIGHT_POSITION_01[0]         -=  .11;                                                                         
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             torso_LIGHT_POSITION_01[0]         +=  .11;                                                                            
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             torso_LIGHT_POSITION_01[1]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             torso_LIGHT_POSITION_01[1]         -=  .11;                                                                            
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             torso_LIGHT_POSITION_01[2]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             torso_LIGHT_POSITION_01[2]         -=  .11;                                                                            
    }                                                                                                                                 
    //=======================================================================================                                           
    if (keys['M'])                                                                                                                      
    {	                                                                                                                                  
             torso_ATTENUATION                  +=  .01;                                                                            
    }	                                                                                                                                  
    if (keys['N'])                                                                                                                      
    {	                                                                                                                                  
             torso_ATTENUATION                  -=  .01;                                                                            
    }                                                                                                                                   
    if (keys['X'])                                                                                                                      
    {	                                                                                                                                  
             torso_SHININESS                  +=  1.01;                                                                            
    }	                                                                                                                                  
    if (keys['Z'])                                                                                                                      
    {	                                                                                                                                  
             torso_SHININESS                  -=  1.01;                                                                                       
    }                                                                                                                                            
    if (keys[VK_F8]) 			                                                                                                                   
	{                                                                                                                                              
        ofstream outKeys("_MODEL_FOLDERS_/horseParts/torso/torso_SHADER_SETTINGS.cpp");                                                                                     
        outKeys << "  GLfloat     torso_LIGHT_POSITION_01[] = {" << torso_LIGHT_POSITION_01[0] << ", "                               
                                                                       << torso_LIGHT_POSITION_01[1] << ", "                               
                                                                       << torso_LIGHT_POSITION_01 [2] << ", " << 1.0 << "};\n";          
        outKeys << "  GLfloat     torso_ATTENUATION         =  " << torso_ATTENUATION   << ";\n";                                    
        outKeys << "  GLfloat     torso_SHININESS           =  " << torso_SHININESS  << ";\n";                                       
    }                                                                                                                                            
