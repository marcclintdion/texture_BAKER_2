                    if(tail_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &tail_NORMALMAP);                                                                  
                            tail_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(tail_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &tail_TEXTUREMAP);                                                                 
                            tail_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                              
                    if(tail_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &tail_VBO);                                                                         
                            tail_VBO  = 0;                                                                                         
                    }                                                                                                              
