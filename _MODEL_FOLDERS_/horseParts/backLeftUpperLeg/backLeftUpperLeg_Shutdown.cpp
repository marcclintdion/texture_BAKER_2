                if(backLeftLeg_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &backLeftLeg_NORMALMAP);                                                                  
                            backLeftLeg_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(backLeftLeg_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &backLeftLeg_TEXTUREMAP);                                                                 
                            backLeftLeg_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                          
                    if(backLeftUpperLeg_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &backLeftUpperLeg_VBO);                                                                         
                            backLeftUpperLeg_VBO  = 0;                                                                                         
                    }                                                                                                              
