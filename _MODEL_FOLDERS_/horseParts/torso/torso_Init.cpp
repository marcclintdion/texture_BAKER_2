            
      //------------------------------------------------------------------------------------------                                              
      #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"torso_DOT3" ofType:@"BMP"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &torso_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, torso_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"torso" ofType:@"bmp"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &torso_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, torso_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/horseParts/torso/torso_DOT3.bmp",          torso_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/horseParts/torso/torso.png",               torso_TEXTUREMAP);                                                        
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "torso.cpp"                                                                                                                
      glGenBuffers(1,              &torso_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, torso_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(torso), torso, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //=================================================================================================================================       
      #include    "torso_INDICES.cpp"       
      glGenBuffers(1, &torso_INDEX_VBO);                       
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, torso_INDEX_VBO);                   
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(torso_INDEX), torso_INDEX, GL_STATIC_DRAW);
      //=================================================================================================================================   










