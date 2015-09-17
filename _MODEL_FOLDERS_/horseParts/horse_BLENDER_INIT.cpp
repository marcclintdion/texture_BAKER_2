      #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      horse_BLENDER_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_horse_BLENDER =                                                                                                        

      "    #define highp                                                                                                 \n"                           

      "    uniform highp vec4   light_POSITION_01;                                                                       \n"                           
      "    uniform highp float   scale;                                                                                  \n"        
      
      "    uniform         mat4   mvpMatrix;                                                                             \n"                           
      "    uniform         mat4   lightMatrix;                                                                           \n"                           
     
      "    uniform highp  float   scale_UV_MAP;                                                                          \n"   
      "    uniform highp  float   UV_WINDOW;                                                                             \n"        
      
      "    attribute       vec4   position;                                                                              \n" 
      "    attribute       vec2   texture;                                                                               \n"                           

      "    varying highp vec4   lightPosition_PASS;                                                                      \n"                           
      "    varying highp vec3   mcPosition;                                                                              \n"           
      "    varying highp vec2   varTexcoord;                                                                             \n"                           

      "    highp vec4   tempPos;                                                                                         \n"
     
     
      "    void main()                                                                                                   \n"                           
      "    {                                                                                                             \n"                           
      "        lightPosition_PASS  = normalize(lightMatrix * light_POSITION_01);                                         \n"                           

      "         tempPos            =  position;                                                                          \n"  
      "         mcPosition         = tempPos.xyz * scale;                                                                \n"        
      "         //-----------------------------------------                                                              \n"         
      
      "         if(UV_WINDOW == 1.0)                                                                                     \n"   
      "         {                                                                                                        \n"   
      "             tempPos.xy    = (texture.xy - 0.5) * 2.0;                                                            \n" 
      "             tempPos.z     = 0.0;                                                                                 \n"  
      "             //tempPos.xy *= vec2(scale_UV_MAP,scale_UV_MAP) ;                                                    \n"        
      "         }                                                                                                        \n"      
      
      "         //-----------------------------------------                                                              \n"      
      "         varTexcoord       = texture;                                                                             \n"                           
     
      
      "         gl_Position       = mvpMatrix * tempPos;                                                                 \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      horse_BLENDER_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(horse_BLENDER_SHADER_VERTEX, 1, &vertexSource_horse_BLENDER, NULL);                                                                        
      glCompileShader(horse_BLENDER_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_horse_BLENDER =                                                                                                            

      " #ifdef GL_ES                                                                                                     \n"                       
      " #else                                                                                                            \n"                       
      " #define highp                                                                                                    \n"                       
      " #endif                                                                                                           \n"                       

      "    uniform sampler3D     Texture1;                                                                               \n"                       
      
      
      "    uniform sampler2D     NormalMap;                                                                              \n"                       
      "    uniform highp float   shininess;                                                                              \n"                       
      "    uniform highp float   attenuation;                                                                            \n"                       
      
      "    uniform highp float   noiseScale;                                                                             \n"          

      "    varying highp vec4    lightPosition_PASS;                                                                     \n"                       
      "    varying highp vec3    mcPosition;                                                                             \n"         
      "    varying highp vec2    varTexcoord;                                                                            \n"                       

      "     highp  float         NdotL1;                                                                                 \n"                       
      "     highp  vec3          normal;                                                                                 \n"                       
      "     highp  vec3          NormalTex;                                                                              \n"                       

      "     highp  vec3  VeinColor   = vec3(0.8, 0.7, 0.8);                                                              \n"     
      "     highp  vec3  MarbleColor = vec3(0.7, 0.5, 0.8);                                                              \n"    
      
      "     highp  vec4  noisevec;                                                                                       \n"  
      "     highp  float intensity;                                                                                      \n"  
      "     highp  vec3  color;                                                                                          \n"  
    
      
      "     void main()                                                                                                  \n"                       
      "     {                                                                                                            \n"                       
     
      "         noisevec  = texture3D(Texture1, mcPosition* 1.00)*noiseScale;                                                       \n"  
      "         intensity = abs(noisevec[0] ) + abs(noisevec[1] ) + abs(noisevec[2]  ) + abs(noisevec[3] );              \n" 
 
      "     float sineval = sin(mcPosition.y * 6.0 + intensity * 12.0) * 0.5 + 0.5;                                      \n" 


      "         color   = mix(VeinColor, MarbleColor, sineval*1.0);                                                      \n"  
    
 //   "         color.r += noiseScale;                                                                                   \n"      
    
      "         gl_FragColor = vec4(color.xyz, 1.0);                                                                     \n"  

    
      "    }\n";                                                                                                                                   

      //---------------------------------------------------------------------                                                                         
      horse_BLENDER_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(horse_BLENDER_SHADER_FRAGMENT, 1, &fragmentSource_horse_BLENDER, NULL);                                                                          
      glCompileShader(horse_BLENDER_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(horse_BLENDER_SHADER, horse_BLENDER_SHADER_VERTEX);                                                                                              
      glAttachShader(horse_BLENDER_SHADER, horse_BLENDER_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(horse_BLENDER_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(horse_BLENDER_SHADER, 1, "texture");                                                                                             
      //glBindAttribLocation(horse_BLENDER _SHADER, 2, "normal");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(horse_BLENDER_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(horse_BLENDER_SHADER, horse_BLENDER_SHADER_VERTEX);                                                                                              
      glDetachShader(horse_BLENDER_SHADER, horse_BLENDER_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(horse_BLENDER_SHADER_VERTEX);                                                                                                            
      glDeleteShader(horse_BLENDER_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_horse_BLENDER                   = glGetUniformLocation(horse_BLENDER_SHADER,   "mvpMatrix");                                              
      UNIFORM_LIGHT_MATRIX_horse_BLENDER                    = glGetUniformLocation(horse_BLENDER_SHADER,   "lightMatrix");                                            
      UNIFORM_LIGHT_POSITION_01_horse_BLENDER               = glGetUniformLocation(horse_BLENDER_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_horse_BLENDER                       = glGetUniformLocation(horse_BLENDER_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_horse_BLENDER                     = glGetUniformLocation(horse_BLENDER_SHADER,   "attenuation");                                              
      UNIFORM_scale_UV_MAP_horse_BLENDER                     = glGetUniformLocation(horse_BLENDER_SHADER,   "scale_UV_MAP");  
      UNIFORM_UV_WINDOW                                      = glGetUniformLocation(horse_BLENDER_SHADER,   "UV_WINDOW");             
     UNIFORM_scaleNoise                                      = glGetUniformLocation(horse_BLENDER_SHADER,   "noiseScale");        
     UNIFORM_scalePerlin                                      = glGetUniformLocation(horse_BLENDER_SHADER,   "scale"); 
           
      UNIFORM_TEXTURE_DOT3_horse_BLENDER                    = glGetUniformLocation(horse_BLENDER_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_horse_BLENDER                         = glGetUniformLocation(horse_BLENDER_SHADER,   "Texture1");                                               
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
