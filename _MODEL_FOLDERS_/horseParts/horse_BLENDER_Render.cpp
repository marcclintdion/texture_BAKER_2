   glUseProgram(horse_BLENDER_SHADER); 
   
                                                                                                                    
    //======================================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   2, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);                                                                                                                                             
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__UNIFORMS          
    glUniform4f(UNIFORM_LIGHT_POSITION_01_horse_BLENDER, horse_BLENDER_LIGHT_POSITION_01[0], horse_BLENDER_LIGHT_POSITION_01[1], horse_BLENDER_LIGHT_POSITION_01[2], horse_BLENDER_LIGHT_POSITION_01[3]);        
    glUniform1f(UNIFORM_SHININESS_horse_BLENDER, horse_BLENDER_SHININESS);                                                                                                                  
    glUniform1f(UNIFORM_ATTENUATION_horse_BLENDER, horse_BLENDER_ATTENUATION);                                                                                                                  
    glUniform1f(UNIFORM_scale_UV_MAP_horse_BLENDER, horse_BLENDER_scale_UV_MAP);     
    glUniform1f(UNIFORM_UV_WINDOW, UV_WINDOW);      
    glUniform1f(UNIFORM_scalePerlin, scalePerlin);       
    glUniform1f(UNIFORM_scaleNoise, scaleNoise);     
    
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_horse_BLENDER,   1,0,  mvpMatrix);                                                                                                      
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_horse_BLENDER,    1,0,  lightMatrix);                                                                                                    
    glUniform1i (UNIFORM_TEXTURE_DOT3_horse_BLENDER, 1);   
    glUniform1i (UNIFORM_TEXTURE_horse_BLENDER, 0 ); 
