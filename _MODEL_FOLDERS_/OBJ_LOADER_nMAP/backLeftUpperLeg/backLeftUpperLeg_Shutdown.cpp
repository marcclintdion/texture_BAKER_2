                    if(backLeftUpperLeg_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &backLeftUpperLeg_NORMALMAP);                                                                  
                            backLeftUpperLeg_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(backLeftUpperLeg_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &backLeftUpperLeg_TEXTUREMAP);                                                                 
                            backLeftUpperLeg_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                              
                    if(backLeftUpperLeg_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &backLeftUpperLeg_VBO);                                                                         
                            backLeftUpperLeg_VBO  = 0;                                                                                         
                    }                                                                                                              
