                    if(frontRightLeg_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &frontRightLeg_NORMALMAP);                                                                  
                            frontRightLeg_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(frontRightLeg_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &frontRightLeg_TEXTUREMAP);                                                                 
                            frontRightLeg_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                              
                    if(frontRightUpperLeg_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &frontRightUpperLeg_VBO);                                                                         
                            frontRightUpperLeg_VBO  = 0;                                                                                         
                    }                                                                                                              
