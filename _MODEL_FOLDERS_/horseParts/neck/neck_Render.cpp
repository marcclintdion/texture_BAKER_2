                                                                                                                                             
    glBindBuffer(GL_ARRAY_BUFFER, neck_VBO);                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
    LoadIdentity(modelView);                                                                                                                                                  
    Translate(modelView, neck_POSITION[0], neck_POSITION[1], neck_POSITION[2]);                                                                                         
    Rotate(modelView, neck_ROTATE[0], neck_ROTATE[1], neck_ROTATE[2], neck_ROTATE[3]);//--MODEL                                                                       
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
 #include "../horse_BLENDER_Render.cpp"     
    //======================================================================================================                                                                  
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, neck_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, neck_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawArrays(GL_TRIANGLES, 0, 852);                                                                                                     

