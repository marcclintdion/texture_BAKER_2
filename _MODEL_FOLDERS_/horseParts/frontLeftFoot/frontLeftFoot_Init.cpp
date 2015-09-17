      #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      frontLeftFoot_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_frontLeftFoot =                                                                                                        

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
      frontLeftFoot_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(frontLeftFoot_SHADER_VERTEX, 1, &vertexSource_frontLeftFoot, NULL);                                                                        
      glCompileShader(frontLeftFoot_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_frontLeftFoot =                                                                                                            

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
      frontLeftFoot_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(frontLeftFoot_SHADER_FRAGMENT, 1, &fragmentSource_frontLeftFoot, NULL);                                                                          
      glCompileShader(frontLeftFoot_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(frontLeftFoot_SHADER, frontLeftFoot_SHADER_VERTEX);                                                                                              
      glAttachShader(frontLeftFoot_SHADER, frontLeftFoot_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(frontLeftFoot_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(frontLeftFoot_SHADER, 1, "texture");                                                                                             
      //glBindAttribLocation(frontLeftFoot _SHADER, 2, "normal");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(frontLeftFoot_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(frontLeftFoot_SHADER, frontLeftFoot_SHADER_VERTEX);                                                                                              
      glDetachShader(frontLeftFoot_SHADER, frontLeftFoot_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(frontLeftFoot_SHADER_VERTEX);                                                                                                            
      glDeleteShader(frontLeftFoot_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_frontLeftFoot                   = glGetUniformLocation(frontLeftFoot_SHADER,   "mvpMatrix");                                              
      UNIFORM_LIGHT_MATRIX_frontLeftFoot                    = glGetUniformLocation(frontLeftFoot_SHADER,   "lightMatrix");                                            
      UNIFORM_LIGHT_POSITION_01_frontLeftFoot               = glGetUniformLocation(frontLeftFoot_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_frontLeftFoot                       = glGetUniformLocation(frontLeftFoot_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_frontLeftFoot                     = glGetUniformLocation(frontLeftFoot_SHADER,   "attenuation");                                              
      UNIFORM_TEXTURE_DOT3_frontLeftFoot                    = glGetUniformLocation(frontLeftFoot_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_frontLeftFoot                         = glGetUniformLocation(frontLeftFoot_SHADER,   "Texture1");                                               
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
      //------------------------------------------------------------------------------------------                                              
   /*   #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"frontLeftFoot_DOT3" ofType:@"bmp"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &frontLeftFoot_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, frontLeftFoot_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"frontLeftFoot" ofType:@"png"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &frontLeftFoot_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, frontLeftFoot_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/frontLeftFoot/frontLeftFoot_DOT3.bmp",          frontLeftFoot_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/frontLeftFoot/frontLeftFoot.png",               frontLeftFoot_TEXTUREMAP);                                                        
      #endif    */                                                                                                                                
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "frontLeftFoot.cpp"                                                                                                                
      glGenBuffers(1,              &frontLeftFoot_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, frontLeftFoot_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(frontLeftFoot), frontLeftFoot, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //=================================================================================================================================       
