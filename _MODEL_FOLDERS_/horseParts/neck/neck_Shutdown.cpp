                    if(neck_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &neck_NORMALMAP);                                                                  
                            neck_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(neck_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &neck_TEXTUREMAP);                                                                 
                            neck_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                              
                    if(neck_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &neck_VBO);                                                                         
                            neck_VBO  = 0;                                                                                         
                    }                                                                                                              
