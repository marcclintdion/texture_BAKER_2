    glUseProgram(torso_SHADER);                                                                                                                                              
    glBindBuffer(GL_ARRAY_BUFFER, torso_VBO);                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
    LoadIdentity(modelView);                                                                                                                                                  
    Translate(modelView, torso_POSITION[0], torso_POSITION[1], torso_POSITION[2]);                                                                                         
    Rotate(modelView, torso_ROTATE[0], torso_ROTATE[1], torso_ROTATE[2], torso_ROTATE[3]);//--MODEL                                                                       
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Translate(lightMatrix, 1.0, -10.0, 2.0);                                                                                                                                
    Rotate(lightMatrix,0.0, 1.0, 0.0,  look_LEFT_RIGHT);                                                                                                                         
    Rotate(lightMatrix,1.0, 0.0, 0.0,  -look_UP_DOWN);                                                                                                                      
    //======================================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   2, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);                                                                                                                                             
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__UNIFORMS          
    glUniform4f(UNIFORM_LIGHT_POSITION_01_torso, torso_LIGHT_POSITION_01[0], torso_LIGHT_POSITION_01[1], torso_LIGHT_POSITION_01[2], torso_LIGHT_POSITION_01[3]);        
    glUniform1f(UNIFORM_SHININESS_torso, torso_SHININESS);                                                                                                                  
    glUniform1f(UNIFORM_ATTENUATION_torso, torso_ATTENUATION);                                                                                                                  
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_torso,   1,0,  mvpMatrix);                                                                                                      
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_torso,    1,0,  lightMatrix);                                                                                                    
    glUniform1i (UNIFORM_TEXTURE_DOT3_torso, 1);                                                                                                                             
    glUniform1i (UNIFORM_TEXTURE_torso, 0 );                                                                                                                                 
    //======================================================================================================                                                                  
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, torso_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, torso_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawArrays(GL_TRIANGLES, 0, 27792);                                                                                                     

