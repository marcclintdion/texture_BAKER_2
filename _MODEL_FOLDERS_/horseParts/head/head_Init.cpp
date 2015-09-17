      #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      head_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_head =                                                                                                        

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
      head_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(head_SHADER_VERTEX, 1, &vertexSource_head, NULL);                                                                        
      glCompileShader(head_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_head =                                                                                                            

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

      "         gl_FragColor          =  (texture2D(Texture1, varTexcoord.st, 0.0)  * .1                                  \n"                       

      "                               +  texture2D(Texture1, varTexcoord.st, 0.0) * NdotL1 * NdotL1  \n"                       

      "                               +  texture2D(Texture1, varTexcoord.st, 0.0) * pow(NdotL1, shininess) * vec4(1.0, .9, .7, 1.0))*attenuation;              \n"                       
      "                               +  texture2D(Texture1, varTexcoord.st, 0.0) * pow(NdotL1, shininess) * vec4(2.0, 1.0, .1, 1.0);              \n"                       

      "    }\n";                                                                                                                                   

      //---------------------------------------------------------------------                                                                         
      head_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(head_SHADER_FRAGMENT, 1, &fragmentSource_head, NULL);                                                                          
      glCompileShader(head_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(head_SHADER, head_SHADER_VERTEX);                                                                                              
      glAttachShader(head_SHADER, head_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(head_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(head_SHADER, 1, "texture");                                                                                             
      //glBindAttribLocation(head _SHADER, 2, "normal");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(head_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(head_SHADER, head_SHADER_VERTEX);                                                                                              
      glDetachShader(head_SHADER, head_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(head_SHADER_VERTEX);                                                                                                            
      glDeleteShader(head_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_head                   = glGetUniformLocation(head_SHADER,   "mvpMatrix");                                              
      UNIFORM_LIGHT_MATRIX_head                    = glGetUniformLocation(head_SHADER,   "lightMatrix");                                            
      UNIFORM_LIGHT_POSITION_01_head               = glGetUniformLocation(head_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_head                       = glGetUniformLocation(head_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_head                     = glGetUniformLocation(head_SHADER,   "attenuation");                                              
      UNIFORM_TEXTURE_DOT3_head                    = glGetUniformLocation(head_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_head                         = glGetUniformLocation(head_SHADER,   "Texture1");                                               
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
      //------------------------------------------------------------------------------------------                                              
      #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"head_DOT3" ofType:@"bmp"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &head_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, head_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"head" ofType:@"png"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &head_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, head_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/horseParts/head/head_DOT3.bmp",          head_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/horseParts/head/head.png",               head_TEXTUREMAP);                                                        
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "head.cpp"                                                                                                                
      glGenBuffers(1,              &head_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, head_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(head), head, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //=================================================================================================================================       
