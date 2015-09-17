#define var GLfloat
//####################################################################################################################


#ifdef WIN32
        #define   glGenerateMipmap       glGenerateMipmapEXT        
        #define   glGenFramebuffers      glGenFramebuffersEXT    
        #define   glBindFramebuffer      glBindFramebufferEXT          
        #define   glFramebufferTexture2D glFramebufferTexture2DEXT            
         
        #define   STRICT
        #define   WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #include <iostream.h>
        #include <fstream.h>
        //using namespace std; //___used for string object

        #include <GL/gl.h>

        HDC	       hDC        = NULL;
        HGLRC      hRC        = NULL;
        HWND       hWnd       = NULL;
        HINSTANCE  hInstance  = NULL;
        //-------------------------------
        int        WINAPI       WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
        LRESULT    CALLBACK     WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        //-------------------------------
        void       ProcessKeyboard();
        //-------------------------------
        var keys[256], keypressed[256];



        #include "headerFiles/glext.h" 
        #include "headerFiles/glext_Init_A.cpp" 
        
        #include "headerFiles/VSync.h"   
        
        #include <windows.h>

        void      ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight );
        #include "headerFiles/glaux.h"        
        #include "headerFiles/FreeImage.h"
 

       
       
       
       #include "cpp/freeImage.cpp"
        //------------------------------------------
        //#include "headerFiles/WGL_ARB_multisample.h"    
        //#include "headerFiles/arb_multisample.h"
        //bool domulti = true;
        //bool doangle = true;    

    
#endif

//####################################################################################################################


#include <math.h>
  

//####################################################################################################################

#include "MATRIX_MATH.cpp"

//####################################################################################################################


//-------------------------------------------------------------------------------------------------------------------- 

int TEXTURE_WIDTH  = 1024;
int TEXTURE_HEIGHT = 1024;
//------------------------------------


//--------------------------------------------------------------------------------------------------------------
#define BUFFER_OFFSET(i) ((char *)0 + (i))
//----------------------------------------------------------------------------------------

        extern GLuint msaaFramebuffer;

        void RenderGL(void);
        void InitGL  (void);
        void shutDownGL(void);
      
        #ifdef WIN32
               var viewWidth    = 1920;
               var viewHeight   = 1080;
               
               #include "cpp/WGL_ARB_multisample.cpp"  
        #endif
        #ifdef __APPLE__
               var viewWidth;
               var viewHeight;
               GLuint  viewFramebuffer;        
        #endif        
        //-------------------------------------------------------------------------------

               var eyePosition[3];
               var look_LEFT_RIGHT;
               var look_UP_DOWN;   
               //-------------------------------
               var eyePosition_TEXTUREBAKE[3];


//#########################################################################################################

void ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight )
{

        #ifdef __APPLE__
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        #endif
        
        #ifdef WIN32
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	        
        glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);
        #endif 
     
        
}

//===============================================================================================================================                                                   

var     modelView[16];
var     projection[16];
var     mvpMatrix[16];
var     mvpMatrixInverse[16];
var     lightMatrix[16];  
var     moveSetMatrix[16]; 
var     textureMatrix[16];
var     ProjectionShadow[16];
var     LightModelViewMatrix[16];


GLuint      UNIFORM_MODELVIEWPROJ;
GLuint      UNIFORM_MODELVIEWPROJ_INVERSE;
GLuint      UNIFORM_LIGHT_MATRIX;

//===============================================================================================================================

//######################################################################################################################






                               
                                var spinModel = 0.0;
                                //---------------------------------------------------- 
                                #include  "_SHADERS/SHADOWS/shadows_24B_GLOBALS.cpp"                              
                                var       adjustShadowMove[]                                        =  {  0.11, 0.0, 0.0, 1.0}; 
                                //=========================================================================================== 
                                var       shadows_POSITION[]                                        =  {  0.0, 0.0, 0.0, 1.0}; 
                                var       shadows_ROTATE[]                                          =  {  1.0, 0.0, 0.0, 0.0};
                                //-------------------------
                                var       moveShadow_A[]                                            =  { -5.93004, -7.35991, -12.7902,   1.0};
                                var       rotateShadow_A[]                                          =  {  0, 1,     0.66,     30.0};
                                var       adjustModelShadow_A_ROTATION                              =    33;
                                //-------------------------
                                var       moveShadow_B[]                                            =  {  0.71,    -0.27,      0.0,      1.0};
                                var       rotateShadow_02[]                                         =  {  0.12,    -4.7,       2.42,   -32.456};
                                var       adjustModelShadow_02_ROTATION                             =    25.0;
                                //-------------------------
                                var       moveShadow_03[]                                           =  { -0.515,  -12.6952,   -0.4400,   1.0};
                                var       rotateShadow_03[]                                         =  {  0.0,      1.0,       1.0,     29.28};                           
                                var       darkness_shadow[]                                         =  {  0.0,      0.0,       0.0,      1.0};                                                      
                                //===========================================================================================                                  
                                
                                bool runOnce = true;
                                
                                //#################################################################################### 
                                GLfloat     horse_BLENDER_LIGHT_POSITION_01[] = {-50.8202, -19.8, 7.26, 1};
                                GLfloat     horse_BLENDER_ATTENUATION         =  0.85;
                                GLfloat     horse_BLENDER_SHININESS           =  19.162;   
                                //-----
                                GLfloat     horse_BLENDER_scale_UV_MAP          =  2.0;  
                                bool        UV_WINDOW                           =  1.0;
                                //--------------------------------------------------------------------------------------                               
                                #include "_SHADERS/PROCEDURALS/perlin_TABLE.cpp"                                                
                                #include "_SHADERS/PROCEDURALS/Perlin.h"
                                #define NOISE_3D_SIZE 64                                                         
                                unsigned int g_perlin = 0;                                 
                                //------------------------
                                GLfloat     scalePerlin      = 4.72006;    //_    64/(GLfloat)NOISE_3D_SIZE*1.0;  
                                //-----------------------
                                GLfloat     scaleNoise      =  0.0;                                  
                                
                                //------------------------------------------------------------
                                #include "_MODEL_FOLDERS_/horseParts/horse_BLENDER_GLOBALS.cpp"      //_SHADER                            
                                //====================================================================================                                        
                                #include "_MODEL_FOLDERS_/horseParts/torso/torso_Globals.cpp"     
                                //====================================================================================                                          
/* 
                                #include "_MODEL_FOLDERS_/horseParts/tail/tail_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/neck/neck_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/head/head_Globals.cpp"                                                                
                                //====================================================================================
                                #include "_MODEL_FOLDERS_/horseParts/frontRightUpperLeg/frontRightUpperLeg_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/frontRightLowerLeg/frontRightLowerLeg_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/frontRightFoot/frontRightFoot_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/backRightUpperLeg/backRightUpperLeg_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/backRightLowerLeg/backRightLowerLeg_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/backRightFoot/backRightFoot_Globals.cpp"                                                                
                                //====================================================================================   
                                #include "_MODEL_FOLDERS_/horseParts/frontLeftUpperLeg/frontLeftUpperLeg_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/frontLeftLowerLeg/frontLeftLowerLeg_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/frontLeftFoot/frontLeftFoot_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/backLeftUpperLeg/backLeftUpperLeg_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/backLeftLowerLeg/backLeftLowerLeg_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/horseParts/backLeftFoot/backLeftFoot_Globals.cpp"                                                                
                                //====================================================================================  
*/



//======================================================================================================================================================================================



          #ifdef WIN32
             #include "cpp/winInit.cpp"
          #endif  
          
          
          
          
          
//------------------------------------------------------------------------------------------------------------------------                 
  

//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
GLuint  snowy_CUBEMAP;
GLuint	cubemapTexture[1];

char *g_cCubemaps[6] = 
{

	"CG_ENVIRO_MAPPING/snowy/snowy_POSX.png",
	"CG_ENVIRO_MAPPING/snowy/snowy_NEGX.png",
	"CG_ENVIRO_MAPPING/snowy/snowy_POSY.png",
	"CG_ENVIRO_MAPPING/snowy/snowy_NEGY.png",
	"CG_ENVIRO_MAPPING/snowy/snowy_POSZ.png",
	"CG_ENVIRO_MAPPING/snowy/snowy_NEGZ.png"
};
//####################################################################################################################################################

void InitGL( void )//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___END_INIT__
{
          
          eyePosition[0]         =  -7.72412;
          eyePosition[1]         =   0;
          eyePosition[2]         =  17.8886;          
          
          look_LEFT_RIGHT        =   0;
          look_UP_DOWN           =   0;           
          //-----------------------------------
        
          eyePosition_TEXTUREBAKE[0]   =    0;
          eyePosition_TEXTUREBAKE[1]   =    0;
          eyePosition_TEXTUREBAKE[2]   =    1;    

        
        

        //==========================================================================
        #ifdef WIN32 
            #include "cpp/setPixelFormat.cpp"
            #include "headerFiles/glext_Init_B.cpp" 
            //-------------------------------------
            SetVSyncState(true);        
        #endif
        
     
  #include "_SHADERS/PROCEDURALS/perlin.cpp"      
        
        
//==========================================================================================================================================================================



        




//####################################################################################
#include "_MODEL_FOLDERS_/horseParts/horse_BLENDER_INIT.cpp"    //_SHADER                                                                
//====================================================================================                                             
#include "_MODEL_FOLDERS_/horseParts/torso/torso_Init.cpp"                                                                   
//====================================================================================                                          
/*
#include "_MODEL_FOLDERS_/horseParts/tail/tail_Init.cpp"                                                                   
//====================================================================================  
#include "_MODEL_FOLDERS_/horseParts/neck/neck_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/head/head_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/frontRightUpperLeg/frontRightUpperLeg_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/frontRightLowerLeg/frontRightLowerLeg_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/frontRightFoot/frontRightFoot_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backRightUpperLeg/backRightUpperLeg_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backRightLowerLeg/backRightLowerLeg_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backRightFoot/backRightFoot_Init.cpp"                                                                   
//====================================================================================                                         
#include "_MODEL_FOLDERS_/horseParts/frontLeftUpperLeg/frontLeftUpperLeg_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/frontLeftLowerLeg/frontLeftLowerLeg_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/frontLeftFoot/frontLeftFoot_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backLeftUpperLeg/backLeftUpperLeg_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backLeftLowerLeg/backLeftLowerLeg_Init.cpp"                                                                   
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backLeftFoot/backLeftFoot_Init.cpp"                                                                   
//====================================================================================   
 */                                      

//=================================================================================================================== 


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);	
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);  


//=====================================================================================================================

    



}//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___END_INIT__



//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################


void RenderGL(void)
{
        
        //======================================================_SHADOWS_BEGIN_===========================================================================	                       
        //======================================================_SHADOWS_BEGIN_===========================================================================	                       
        //======================================================_SHADOWS_BEGIN_===========================================================================	                       
        //======================================================_SHADOWS_BEGIN_===========================================================================	                       
        
        glEnable(GL_DEPTH_TEST);                                 
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 	                       
        	                       
        //======================================================_SHADOWS_END_=============================================================================	                       
        //======================================================_SHADOWS_END_=============================================================================	                       
        //======================================================_SHADOWS_END_=============================================================================	                       
        //======================================================_SHADOWS_END_=============================================================================	 

//##################################################################################################################################################################################################        
//##################################################################################################################################################################################################         
//##################################################################################################################################################################################################         
//##################################################################################################################################################################################################          
        
        //========================================================================================================================================================        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //========================================================================================================================================================        
        #ifdef __APPLE__    
            glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
        #endif    
        //========================================================================================================================================================        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!          
        //========================================================================================================================================================

UV_WINDOW = 1.0;

        //=========================================================================================================================================================    
        glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        //----------------------------------------------------------------------------------
        glViewport(0, 0, TEXTURE_WIDTH, TEXTURE_WIDTH);
        
        TextureBakeViewMatrix(projection, (float)TEXTURE_WIDTH / (float)TEXTURE_WIDTH);
        
        
        //Ortho_2(var *matrix, var near2, var far2, var left, var right, var top, var bottom)
       
        //LoadOrthoMatrix(projection, 0.001, 100.0, -1, 1, 1,-1);
            

        //=========================================================================================================================================================
        #ifdef __APPLE__
        Rotate(projection, 0.0, 0.0, 1.0, -90.0);//_____FOR_iOS_LANDSCAPE_VIEW 
        projection[12] = eyePosition_TEXTUREBAKE[1];
        projection[13] = eyePosition_TEXTUREBAKE[0];
        projection[15] = eyePosition_TEXTUREBAKE[2];        
        #endif        
        //=========================================================================================================================================================        
        #ifdef WIN32        
        projection[12] = eyePosition_TEXTUREBAKE[0];
        projection[13] = eyePosition_TEXTUREBAKE[1];
        projection[15] = eyePosition_TEXTUREBAKE[2];
        #endif           
        //=========================================================================================================================================================               
      
//#################################################################################################################################################################        
        

glEnable(GL_TEXTURE_3D);
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/torso/torso_Render.cpp"                                                                 
//====================================================================================  
/*#include "_MODEL_FOLDERS_/horseParts/tail/tail_Render.cpp"                                                                 
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/neck/neck_Render.cpp"                                                                 
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/head/head_Render.cpp"                                                                 
//====================================================================================   
#include "_MODEL_FOLDERS_/horseParts/frontRightUpperLeg/frontRightUpperLeg_Render.cpp"                                                                 
//=====================================================                                        
#include "_MODEL_FOLDERS_/horseParts/frontRightLowerLeg/frontRightLowerLeg_Render.cpp"                                                                 
//=====================================================                                          
#include "_MODEL_FOLDERS_/horseParts/frontRightFoot/frontRightFoot_Render.cpp"                                                                 
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backRightUpperLeg/backRightUpperLeg_Render.cpp"                                                                 
//=====================================================                                         
#include "_MODEL_FOLDERS_/horseParts/backRightLowerLeg/backRightLowerLeg_Render.cpp"                                                                 
//=====================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backRightFoot/backRightFoot_Render.cpp"                                                                 
//====================================================================================      
#include "_MODEL_FOLDERS_/horseParts/frontLeftUpperLeg/frontLeftUpperLeg_Render.cpp"                                                                 
//=====================================================                                        
#include "_MODEL_FOLDERS_/horseParts/frontLeftLowerLeg/frontLeftLowerLeg_Render.cpp"                                                                 
//=====================================================                                        
#include "_MODEL_FOLDERS_/horseParts/frontLeftFoot/frontLeftFoot_Render.cpp"                                                                 
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backLeftUpperLeg/backLeftUpperLeg_Render.cpp"                                                                 
//=====================================================                                        
#include "_MODEL_FOLDERS_/horseParts/backLeftLowerLeg/backLeftLowerLeg_Render.cpp"                                                                 
//=====================================================                                       
#include "_MODEL_FOLDERS_/horseParts/backLeftFoot/backLeftFoot_Render.cpp"                                                                 
//====================================================================================            
*/    
  
  
  
//##################################################################################################################################################################################################        
//##################################################################################################################################################################################################         
//##################################################################################################################################################################################################         
//##################################################################################################################################################################################################          
        
        UV_WINDOW = 0.0;
        //=========================================================================================================================================================    
        //----------------------------------------------------------------------------------
        glViewport((GLsizei)viewWidth/2, 0, (GLsizei)viewWidth, (GLsizei)viewHeight);
        PerspectiveMatrix(projection, 45, (float)viewWidth / (float)viewHeight, 0.01, 1000.0);
        //=========================================================================================================================================================
        #ifdef __APPLE__
        Rotate(projection, 0.0, 0.0, 1.0, -90.0);//_____FOR_iOS_LANDSCAPE_VIEW 
        projection[12] = eyePosition[1];
        projection[13] = eyePosition[0];
        projection[15] = eyePosition[2];        
        #endif        
        //=========================================================================================================================================================        
        #ifdef WIN32        
        projection[12] = eyePosition[0];
        projection[13] = eyePosition[1];
        projection[15] = eyePosition[2];
        #endif           
        //=========================================================================================================================================================               
        Rotate(projection, 1.0, 0.0, 0.0,  look_UP_DOWN);
        Rotate(projection, 0.0, 1.0, 0.0, -look_LEFT_RIGHT);        
     
//#################################################################################################################################################################        
        

//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/torso/torso_Render.cpp"                                                                 
//====================================================================================  
/*#include "_MODEL_FOLDERS_/horseParts/tail/tail_Render.cpp"                                                                 
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/neck/neck_Render.cpp"                                                                 
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/head/head_Render.cpp"                                                                 
//====================================================================================   
#include "_MODEL_FOLDERS_/horseParts/frontRightUpperLeg/frontRightUpperLeg_Render.cpp"                                                                 
//=====================================================                                        
#include "_MODEL_FOLDERS_/horseParts/frontRightLowerLeg/frontRightLowerLeg_Render.cpp"                                                                 
//=====================================================                                          
#include "_MODEL_FOLDERS_/horseParts/frontRightFoot/frontRightFoot_Render.cpp"                                                                 
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backRightUpperLeg/backRightUpperLeg_Render.cpp"                                                                 
//=====================================================                                         
#include "_MODEL_FOLDERS_/horseParts/backRightLowerLeg/backRightLowerLeg_Render.cpp"                                                                 
//=====================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backRightFoot/backRightFoot_Render.cpp"                                                                 
//====================================================================================      
#include "_MODEL_FOLDERS_/horseParts/frontLeftUpperLeg/frontLeftUpperLeg_Render.cpp"                                                                 
//=====================================================                                        
#include "_MODEL_FOLDERS_/horseParts/frontLeftLowerLeg/frontLeftLowerLeg_Render.cpp"                                                                 
//=====================================================                                        
#include "_MODEL_FOLDERS_/horseParts/frontLeftFoot/frontLeftFoot_Render.cpp"                                                                 
//====================================================================================                                          
#include "_MODEL_FOLDERS_/horseParts/backLeftUpperLeg/backLeftUpperLeg_Render.cpp"                                                                 
//=====================================================                                        
#include "_MODEL_FOLDERS_/horseParts/backLeftLowerLeg/backLeftLowerLeg_Render.cpp"                                                                 
//=====================================================                                       
#include "_MODEL_FOLDERS_/horseParts/backLeftFoot/backLeftFoot_Render.cpp"                                                                 
//====================================================================================      
*/
  
     
        
        #ifdef WIN32
             SwapBuffers( hDC );
        #endif
}

//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################


#ifdef WIN32 
void ProcessKeyboard()					
{

//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/torso/torso_Keyboard.cpp"                                                               
//====================================================================================
//#include "_MODEL_FOLDERS_/horseParts/tail/tail_Keyboard.cpp"                                                               
//====================================================================================
//#include "_MODEL_FOLDERS_/horseParts/neck/neck_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/head/head_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/head/head_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/frontRightUpperLeg/frontRightUpperLeg_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/frontRightLowerLeg/frontRightLowerLeg_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/frontRightFoot/frontRightFoot_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/backRightUpperLeg/backRightUpperLeg_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/backRightLowerLeg/backRightLowerLeg_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/backRightFoot/backRightFoot_Keyboard.cpp"                                                               
//====================================================================================                                    

//#include "_MODEL_FOLDERS_/horseParts/backLeftUpperLeg/backLeftUpperLeg_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/backLeftLowerLeg/backLeftLowerLeg_Keyboard.cpp"                                                               
//====================================================================================                                          
//nclude "_MODEL_FOLDERS_/horseParts/backLeftFoot/backLeftFoot_Keyboard.cpp"                                                               
//====================================================================================        
//#include "_MODEL_FOLDERS_/horseParts/frontLeftUpperLeg/frontLeftUpperLeg_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/frontLeftLowerLeg/frontLeftLowerLeg_Keyboard.cpp"                                                               
//====================================================================================                                          
//#include "_MODEL_FOLDERS_/horseParts/frontLeftFoot/frontLeftFoot_Keyboard.cpp"                                                               
//====================================================================================                   
if (keys['J'])                                                                                                                   
    {                                                                                                                                   
             torso_POSITION[0]         -=  .1;                                                                         
    }	                                                                                                                                  
    if (keys['L'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[0]         +=  .1;                                                                            
    }                                                                                                                                   
    if (keys['I'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[1]         +=  .1;                                                                            
    }	                                                                                                                                  
    if (keys['K'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[1]         -=  .1;                                                                            
    }                                                                                                                                   
    if (keys['O'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[2]         +=  .1;                                                                            
    }	                                                                                                                                  
    if (keys['U'])                                                                                                                      
    {	                                                                                                                                  
             torso_POSITION[2]         -=  .1;                                                                            
    } 
    if (keys['M'])                                                                                                                      
    {	                                                                                                                                  
             scaleNoise                  +=   .01;                                                                            
    }	                                                                                                                                  
    if (keys['N'])                                                                                                                      
    {	                                                                                                                                  
             scaleNoise                  -=   .01;                                                                            
    }                                                                                                                                   
    if (keys['X'])                                                                                                                      
    {	                                                                                                                                  
             scalePerlin                  +=  0.005;                                                                            
    }	                                                                                                                                  
    if (keys['Z'])                                                                                                                      
    {	                                                                                                                                  
             scalePerlin                  -=  0.005;                                                                                       
    }                                                                                                                                            
 
//=============================================================================================================================    
   
    if (keys[VK_F8]) 			                                                                                                                   
	{                                                                                                                                              
         ofstream outKeys("lightPosition.cpp");                                                                                     
        
        
         outKeys << "  GLfloat     torso_POSITION[]                  = {" << torso_POSITION[0]  << ", "                               
                                                                          << torso_POSITION[1]  << ", "                               
                                                                          << torso_POSITION [2] << ", " << 1.0 << "};\n";          
      
         outKeys << "  GLfloat     scaleNoise         =  " << scaleNoise   << ";\n";                                    
         outKeys << "  GLfloat     scalePerlin          =  " << scalePerlin  << ";\n";            
        
         
         outKeys << "  var     eyePosition[]                         = {" << eyePosition[0]   << ", "  << eyePosition[1] << ", " << eyePosition[2] << ", " << 1.0 << "};\n";          
         outKeys << "  var     look_LEFT_RIGHT                       =  " << look_LEFT_RIGHT  << ";\n";  
         outKeys << "  var     look_UP_DOWN                          =  " << look_UP_DOWN     << ";\n";                                    
    
    
    

    GLubyte *pixmap =(GLubyte *)malloc(TEXTURE_WIDTH*TEXTURE_WIDTH*4);
    
    glReadPixels(0,0,TEXTURE_WIDTH,TEXTURE_WIDTH,GL_BGRA,GL_UNSIGNED_BYTE,pixmap);
    
    FIBITMAP *texture = FreeImage_ConvertFromRawBits( pixmap, TEXTURE_WIDTH, TEXTURE_WIDTH, TEXTURE_WIDTH*4, 32, 0xFF0000, 0x00FF00, 0x0000FF, true);    
    FreeImage_Save(FIF_BMP, texture, "AAAAA.bmp", 0);         
        
    free(pixmap); 
        
    runOnce = false;
   
    
    
    }             
      

//--------------------------------------------------------------------    
    if (keys['A'])
	{
          eyePosition[0]    += .01;
    }      
          if (keys['A'] && keys[VK_SHIFT])
	      {
                eyePosition[0] += .1;
          
          }       
//---------------------------------------------------    	
    if (keys['D'])
	{
          eyePosition[0]    -= .01;
    }
           if (keys['D'] && keys[VK_SHIFT])
	      {
                eyePosition[0] -= .1;
          
          }     
    
//-----------------------------------
    if (keys['S'])
	{
          eyePosition[2] += .01;
    }
          if (keys['S'] && keys[VK_SHIFT])
	      {
                eyePosition[2] += .1;
          
          }    
//-----------------------------------	
    if (keys['W'])
	{
          eyePosition[2] -= .01;       
    }    
	      if (keys['W'] && keys[VK_SHIFT])
	      {
                eyePosition[2] -= .1;      
          }	
//-----------------------------------    
    if (keys['E'])
	{
          eyePosition[1] -= 0.01;
    }
	      if (keys['E'] && keys[VK_SHIFT])
	      {
                eyePosition[1] -= .1;      
          }		
    
    if (keys['Q'])
	{
          eyePosition[1] += 0.01;      
    }
	      if (keys['Q'] && keys[VK_SHIFT])
	      {
                eyePosition[1] += .1;      
          }    
        
//--------------------------------------------------------------------

}
#endif


//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################



void shutDownGL( void )
{
        #ifdef WIN32
            #include "cpp/shutDownWin.cpp"
        #endif 	 
        

        //====================================================================================                                              
        #include "_MODEL_FOLDERS_/horseParts/torso/torso_Shutdown.cpp"                                     
        //====================================================================================                                          
/*       
       
        #include "_MODEL_FOLDERS_/horseParts/tail/tail_Shutdown.cpp"                                                               
        //====================================================================================  
        #include "_MODEL_FOLDERS_/horseParts/neck/neck_Shutdown.cpp"                                                               
        //====================================================================================    
        #include "_MODEL_FOLDERS_/horseParts/head/head_Shutdown.cpp"   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/horseParts/frontRightUpperLeg/frontRightUpperLeg_Shutdown.cpp"              
        //====================================================================================    
        #include "_MODEL_FOLDERS_/horseParts/frontRightLowerLeg/frontRightLowerLeg_Shutdown.cpp"                                                               
        //====================================================================================                                                 
        #include "_MODEL_FOLDERS_/horseParts/frontRightFoot/frontRightFoot_Shutdown.cpp"                                                               
        //====================================================================================        
        #include "_MODEL_FOLDERS_/horseParts/backRightUpperLeg/backRightUpperLeg_Shutdown.cpp"              
        //====================================================================================    
        #include "_MODEL_FOLDERS_/horseParts/backRightLowerLeg/backRightLowerLeg_Shutdown.cpp"                                                               
        //====================================================================================                                                 
        #include "_MODEL_FOLDERS_/horseParts/backRightFoot/backRightFoot_Shutdown.cpp"                                                               
        //====================================================================================                                                   
           
        #include "_MODEL_FOLDERS_/horseParts/frontLeftUpperLeg/frontLeftUpperLeg_Shutdown.cpp"              
        //====================================================================================    
        #include "_MODEL_FOLDERS_/horseParts/frontLeftLowerLeg/frontLeftLowerLeg_Shutdown.cpp"                                                               
        //====================================================================================                                                 
        #include "_MODEL_FOLDERS_/horseParts/frontLeftFoot/frontLeftFoot_Shutdown.cpp"                                                               
        //====================================================================================        
        #include "_MODEL_FOLDERS_/horseParts/backLeftUpperLeg/backLeftUpperLeg_Shutdown.cpp"              
        //====================================================================================    
        #include "_MODEL_FOLDERS_/horseParts/backLeftLowerLeg/backLeftLowerLeg_Shutdown.cpp"                                                               
        //====================================================================================                                                 
        #include "_MODEL_FOLDERS_/horseParts/backLeftFoot/backLeftFoot_Shutdown.cpp"                                                               
        //====================================================================================                                                                       
*/
   
   
                          
}


//===================================================================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//===================================================================================================================================================================




