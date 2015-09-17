                    if(backRightLeg_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &backRightLeg_NORMALMAP);                                                                  
                            backRightLeg_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(backRightLeg_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &backRightLeg_TEXTUREMAP);                                                                 
                            backRightLeg_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                              
                    if(backRightUpperLeg_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &backRightUpperLeg_VBO);                                                                         
                            backRightUpperLeg_VBO  = 0;                                                                                         
                    }                                                                                                              
