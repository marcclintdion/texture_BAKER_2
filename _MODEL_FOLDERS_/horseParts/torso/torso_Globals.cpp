GLuint      torso_SHADER_VERTEX;                                                                                                      
GLuint      torso_SHADER_FRAGMENT;                                                                                                    
GLuint      torso_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_torso;                                                                                              
GLuint      UNIFORM_LIGHT_MATRIX_torso;                                                                                               
//--------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_torso;                                                                                          
GLuint      UNIFORM_SHININESS_torso;                                                                                                  
GLuint      UNIFORM_ATTENUATION_torso;                                                                                                  
GLuint      UNIFORM_TEXTURE_DOT3_torso;                                                                                               
GLuint      UNIFORM_TEXTURE_torso;                                                                                                    
//--------------------------------------                                                                                                  
GLfloat     torso_POSITION[]             = {0.00, 0, 0, 0};                                                                  
GLfloat     torso_ROTATE[]              =  {  0.0, 1.0,  0.0, 0.0};                                                                   
GLfloat     torso_SCALE[]               =  {  1.0, 1.0,  1.0, 1.0};                                                                   
//-----------------------------------------------------------------                                                                       
  GLfloat     torso_LIGHT_POSITION_01[] = {2, 15, 30, 1};
  GLfloat     torso_ATTENUATION         =  1;
  GLfloat     torso_SHININESS           =  534.502;                                                                                   
//-----------------------------------------------------------------                                                                       
GLuint      torso_VBO; 
GLuint      torso_INDEX_VBO;                                                                                                                
//-----------------------------------------------------------------                                                                       
GLuint      torso_NORMALMAP;                                                                                                          
GLuint      torso_TEXTUREMAP;                                                                                                         
