    //=======================================================================================                                           
    if (keys['J'])                                                                                                                      
    {                                                                                                                                   
             head_POSITION[0]         -=  .01;                                                                                  
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             head_POSITION[0]         +=  .01;                                                                                  
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             head_POSITION[1]         +=  .01;                                                                                  
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             head_POSITION[1]         -=  .01;                                                                                  
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             head_POSITION[2]         +=  .01;                                                                                  
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             head_POSITION[2]         -=  .01;                                                                                  
    }                                                                                                                                   
    //=======================================================================================                                           
    //=======================================================================================                                           
    /* if (keys['J'])                                                                                                                   
    {                                                                                                                                   
             head_LIGHT_POSITION_01[0]         -=  .11;                                                                         
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             head_LIGHT_POSITION_01[0]         +=  .11;                                                                            
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             head_LIGHT_POSITION_01[1]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             head_LIGHT_POSITION_01[1]         -=  .11;                                                                            
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             head_LIGHT_POSITION_01[2]         +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             head_LIGHT_POSITION_01[2]         -=  .11;                                                                            
    } */                                                                                                                                
    //=======================================================================================                                           
    if (keys['M'])                                                                                                                      
    {	                                                                                                                                  
             head_ROTATE[3]                 +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['N'])                                                                                                                      
    {	                                                                                                                                  
             head_ROTATE[3]                 -=  .11;                                                                            
    }                                                                                                                                   
    if (keys['X'])                                                                                                                      
    {	                                                                                                                                  
             head_SHININESS                  +=  1.01;                                                                            
    }	                                                                                                                                  
    if (keys['Z'])                                                                                                                      
    {	                                                                                                                                  
             head_SHININESS                  -=  1.01;                                                                                       
    }                                                                                                                                            
    if (keys[VK_F8]) 			                                                                                                                   
	{                                                                                                                                              
        ofstream outKeys("_MODEL_FOLDERS_/horseParts/head/head_SHADER_SETTINGS.cpp");                                                                                     
        outKeys << "  GLfloat     head_LIGHT_POSITION_01[] = {" << head_LIGHT_POSITION_01[0] << ", "                               
                                                                       << head_LIGHT_POSITION_01[1] << ", "                               
                                                                       << head_LIGHT_POSITION_01 [2] << ", " << 1.0 << "};\n"; 
      
         outKeys << "  GLfloat     head_POSITION[] = {" << head_POSITION[0] << ", "                               
                                                                       << head_POSITION[1] << ", "                               
                                                                       << head_POSITION [2] << ", " << 1.0 << "};\n";                                                                       
                                                                                
        outKeys << "  GLfloat     head_ROTATE[3]        =  " << head_ROTATE[3]  << ";\n";                                    
        outKeys << "  GLfloat     head_SHININESS           =  " << head_SHININESS  << ";\n";                                       
    }                                                                                                                                            
