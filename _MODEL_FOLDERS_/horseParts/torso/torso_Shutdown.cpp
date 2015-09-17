                    if(torso_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &torso_NORMALMAP);                                                                  
                            torso_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(torso_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &torso_TEXTUREMAP);                                                                 
                            torso_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                              
                    if(torso_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &torso_VBO);                                                                         
                            torso_VBO  = 0;                                                                                         
                    }                                                                                                              
