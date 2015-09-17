      #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      backLeftLowerLeg_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_backLeftLowerLeg =                                                                                                        

      "    #define highp                                                                                     \n"                           

      "    uniform highp vec4   light_POSITION_01;                                                           \n"                           
      "    uniform         mat4   mvpMatrix;                                                                   \n"                           
      "    uniform         mat4   lightMatrix;                                                                 \n"                           

      "    attribute       vec4   position;                                                                    \n"                           
      "    attribute       vec2   texture;                                                                     \n"                           

      "    varying highp vec4   lightPosition_PASS;                                                          \n"                           
      "    varying highp vec2   varTexcoord;                                                                 \n"                           


      "    void main()                                                                                         \n"                           
      "    {                                                                                                   \n"                           
      "        lightPosition_PASS = normalize(lightMatrix * light_POSITION_01);                                \n"                           

      "        varTexcoord        = texture;                                                                   \n"                           

      "        gl_Position        = mvpMatrix * position;                                                      \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      backLeftLowerLeg_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(backLeftLowerLeg_SHADER_VERTEX, 1, &vertexSource_backLeftLowerLeg, NULL);                                                                        
      glCompileShader(backLeftLowerLeg_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_backLeftLowerLeg =                                                                                                            

      " #ifdef GL_ES                                                                                                     \n"                       
      " #else                                                                                                     \n"                       
      " #define highp                                                                                                  \n"                       
      " #endif                                                                                                           \n"                       

      "    uniform sampler2D       Texture1;                                                                             \n"                       
      "    uniform sampler2D       NormalMap;                                                                            \n"                       
      "    uniform highp float   shininess;                                                                            \n"                       
      "    uniform highp float   attenuation;                                                                          \n"                       

      "    varying highp vec4    lightPosition_PASS;                                                                   \n"                       
      "    varying highp vec2    varTexcoord;                                                                          \n"                       

      "     highp  float         NdotL1;                                                                               \n"                       
      "     highp  vec3          normal;                                                                               \n"                       
      "     highp vec3           NormalTex;                                                                            \n"                       

      "     void main()                                                                                                  \n"                       
      "     {                                                                                                            \n"                       
      "         NormalTex   =  texture2D(NormalMap,  varTexcoord).xyz;                                                   \n"                       
      "         NormalTex             = (NormalTex - 0.5);                                                               \n"                       
      "         normal                =  normalize(NormalTex);                                                           \n"                       

      "         NdotL1                =  dot(normal, lightPosition_PASS.xyz);                                            \n"                       

      "         gl_FragColor          =  texture2D(Texture1, varTexcoord.st, 0.0)  * .2                                  \n"                       

      "                               +  texture2D(Texture1, varTexcoord.st, 0.0) * NdotL1 * NdotL1* NdotL1*attenuation  \n"                       

      "                               +  texture2D(Texture1, varTexcoord.st, 0.0) * pow(NdotL1, shininess) * vec4(2.0, 1.0, .1, 1.0);              \n"                       

      "    }\n";                                                                                                                                   

      //---------------------------------------------------------------------                                                                         
      backLeftLowerLeg_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(backLeftLowerLeg_SHADER_FRAGMENT, 1, &fragmentSource_backLeftLowerLeg, NULL);                                                                          
      glCompileShader(backLeftLowerLeg_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(backLeftLowerLeg_SHADER, backLeftLowerLeg_SHADER_VERTEX);                                                                                              
      glAttachShader(backLeftLowerLeg_SHADER, backLeftLowerLeg_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(backLeftLowerLeg_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(backLeftLowerLeg_SHADER, 1, "texture");                                                                                             
      //glBindAttribLocation(backLeftLowerLeg _SHADER, 2, "normal");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(backLeftLowerLeg_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(backLeftLowerLeg_SHADER, backLeftLowerLeg_SHADER_VERTEX);                                                                                              
      glDetachShader(backLeftLowerLeg_SHADER, backLeftLowerLeg_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(backLeftLowerLeg_SHADER_VERTEX);                                                                                                            
      glDeleteShader(backLeftLowerLeg_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_backLeftLowerLeg                   = glGetUniformLocation(backLeftLowerLeg_SHADER,   "mvpMatrix");                                              
      UNIFORM_LIGHT_MATRIX_backLeftLowerLeg                    = glGetUniformLocation(backLeftLowerLeg_SHADER,   "lightMatrix");                                            
      UNIFORM_LIGHT_POSITION_01_backLeftLowerLeg               = glGetUniformLocation(backLeftLowerLeg_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_backLeftLowerLeg                       = glGetUniformLocation(backLeftLowerLeg_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_backLeftLowerLeg                     = glGetUniformLocation(backLeftLowerLeg_SHADER,   "attenuation");                                              
      UNIFORM_TEXTURE_DOT3_backLeftLowerLeg                    = glGetUniformLocation(backLeftLowerLeg_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_backLeftLowerLeg                         = glGetUniformLocation(backLeftLowerLeg_SHADER,   "Texture1");                                               
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
      //------------------------------------------------------------------------------------------                                              
   /*   #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"backLeftLowerLeg_DOT3" ofType:@"bmp"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &backLeftLowerLeg_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, backLeftLowerLeg_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"backLeftLowerLeg" ofType:@"png"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &backLeftLowerLeg_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, backLeftLowerLeg_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/backLeftLowerLeg/backLeftLowerLeg_DOT3.bmp",          backLeftLowerLeg_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/backLeftLowerLeg/backLeftLowerLeg.png",               backLeftLowerLeg_TEXTUREMAP);                                                        
      #endif    */                                                                                                                                
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "backLeftLowerLeg.cpp"                                                                                                                
      glGenBuffers(1,              &backLeftLowerLeg_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, backLeftLowerLeg_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(backLeftLowerLeg), backLeftLowerLeg, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //=================================================================================================================================       
