                    if(head_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &head_NORMALMAP);                                                                  
                            head_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(head_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &head_TEXTUREMAP);                                                                 
                            head_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                              
                    if(head_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &head_VBO);                                                                         
                            head_VBO  = 0;                                                                                         
                    }                                                                                                              
