    //=======================================================================================                                           
    /*if (keys['J'])                                                                                                                      
    {                                                                                                                                   
             neck_POSITION[0]         -=  .01;                                                                                  
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[0]         +=  .01;                                                                                  
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[1]         +=  .01;                                                                                  
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[1]         -=  .01;                                                                                  
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[2]         +=  .01;                                                                                  
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[2]         -=  .01;                                                                                  
    }*/                                                                                                                                   
    //=======================================================================================                                           
    //=======================================================================================                                           
     if (keys['J'])                                                                                                                   
    {                                                                                                                                   
             neck_POSITION[0]         -=  .01;                                                                         
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[0]         +=  .01;                                                                            
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[1]         +=  .01;                                                                            
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[1]         -=  .01;                                                                            
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[2]         +=  .01;                                                                            
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             neck_POSITION[2]         -=  .01;                                                                            
    }                                                                                                                                 
    //=======================================================================================                                           
    if (keys['M'])                                                                                                                      
    {	                                                                                                                                  
             neck_ROTATE[3]                  +=  .11;                                                                            
    }	                                                                                                                                  
    if (keys['N'])                                                                                                                      
    {	                                                                                                                                  
             neck_ROTATE[3]                  -=  .11;                                                                            
    }                                                                                                                                   
    if (keys['X'])                                                                                                                      
    {	                                                                                                                                  
             neck_SHININESS                  +=  1.01;                                                                            
    }	                                                                                                                                  
    if (keys['Z'])                                                                                                                      
    {	                                                                                                                                  
             neck_SHININESS                  -=  1.01;                                                                                       
    }                                                                                                                                            
    if (keys[VK_F8]) 			                                                                                                                   
	{                                                                                                                                              
        ofstream outKeys("_MODEL_FOLDERS_/horseParts/neck/neck_SHADER_SETTINGS.cpp");                                                                                     
        outKeys << "  GLfloat     neck_POSITION[] = {" << neck_POSITION[0] << ", "                               
                                                                       << neck_POSITION[1] << ", "                               
                                                                       << neck_POSITION [2] << ", " << 1.0 << "};\n";          
        outKeys << "  GLfloat     neck_ROTATE[3]         =  " << neck_ROTATE[3]   << ";\n";                                    
        outKeys << "  GLfloat     neck_SHININESS           =  " << neck_SHININESS  << ";\n";                                       
    }                                                                                                                                            
