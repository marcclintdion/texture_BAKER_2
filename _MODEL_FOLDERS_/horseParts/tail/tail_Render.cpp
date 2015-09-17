                                                                                                                                            
    glBindBuffer(GL_ARRAY_BUFFER, tail_VBO);                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
    LoadIdentity(modelView);                                                                                                                                                  
    Translate(modelView, tail_POSITION[0], tail_POSITION[1], tail_POSITION[2]);                                                                                         
    Rotate(modelView, tail_ROTATE[0], tail_ROTATE[1], tail_ROTATE[2], tail_ROTATE[3]);//--MODEL                                                                       
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Translate(lightMatrix, 1.0, -10.0, 2.0);                                                                                                                                
    Rotate(lightMatrix,0.0, 1.0, 0.0,  look_LEFT_RIGHT);                                                                                                                         
    Rotate(lightMatrix,1.0, 0.0, 0.0,  -look_UP_DOWN);    
    //---------------------------------------------------------------------------------------------------------
    #include "../horse_BLENDER_Render.cpp"                                                                                                                               
    //======================================================================================================                                                                  
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, tail_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, tail_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawArrays(GL_TRIANGLES, 0, 438);                                                                                                     

