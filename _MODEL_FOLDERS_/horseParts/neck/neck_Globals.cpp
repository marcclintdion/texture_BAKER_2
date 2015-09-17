GLuint      neck_SHADER_VERTEX;                                                                                                      
GLuint      neck_SHADER_FRAGMENT;                                                                                                    
GLuint      neck_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_neck;                                                                                              
GLuint      UNIFORM_LIGHT_MATRIX_neck;                                                                                               
//--------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_neck;                                                                                          
GLuint      UNIFORM_SHININESS_neck;                                                                                                  
GLuint      UNIFORM_ATTENUATION_neck;                                                                                                  
GLuint      UNIFORM_TEXTURE_DOT3_neck;                                                                                               
GLuint      UNIFORM_TEXTURE_neck;                                                                                                    
//--------------------------------------                                                                                                  
GLfloat     neck_POSITION[]            = {0, 0.69, 4.59, 1};                                                                 
GLfloat     neck_ROTATE[]              =  {  1.0, 0.0,  0.0, -50.0};                                                                   
GLfloat     neck_SCALE[]               =  {  1.0, 1.0,  1.0, 1.0};                                                                   
//-----------------------------------------------------------------                                                                       
GLfloat     neck_LIGHT_POSITION_01[]   =  {  2.0, 15.0, 30.0, 1.0};                                                                  
GLfloat     neck_SHININESS             =    534.0;                                                                                    
GLfloat     neck_ATTENUATION           =     1.0;                                                                                    
//-----------------------------------------------------------------                                                                       
GLuint      neck_VBO;                                                                                                                
//-----------------------------------------------------------------                                                                       
GLuint      neck_NORMALMAP;                                                                                                          
GLuint      neck_TEXTUREMAP;                                                                                                         
