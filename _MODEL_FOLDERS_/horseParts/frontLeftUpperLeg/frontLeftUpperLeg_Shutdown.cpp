                   if(frontLeftLeg_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &frontLeftLeg_NORMALMAP);                                                                  
                            frontLeftLeg_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(frontLeftLeg_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &frontLeftLeg_TEXTUREMAP);                                                                 
                            frontLeftLeg_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                            
                    if(frontLeftUpperLeg_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &frontLeftUpperLeg_VBO);                                                                         
                            frontLeftUpperLeg_VBO  = 0;                                                                                         
                    }                                                                                                              
