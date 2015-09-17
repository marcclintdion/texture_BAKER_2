              /*      if(frontRightFoot_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &frontRightFoot_NORMALMAP);                                                                  
                            frontRightFoot_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(frontRightFoot_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &frontRightFoot_TEXTUREMAP);                                                                 
                            frontRightFoot_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                              
               */    
                    if(frontRightFoot_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &frontRightFoot_VBO);                                                                         
                            frontRightFoot_VBO  = 0;                                                                                         
                    }                                                                                                              
