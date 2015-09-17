
#include <cassert>
#include <cstdio>
#include <cstring>
#include "../headerFiles/WGL_ARB_multisample.h"


    WNDCLASSEX wcl;
    char szAAPixelFormat[32];


LRESULT CALLBACK DummyGLWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        switch (msg)
        {
        case WM_CREATE:
            if (!(hDC = GetDC(hWnd)))
                return -1;
            break;

        case WM_DESTROY:
            if (hDC)
            {
                if (hRC)
                {
                    wglMakeCurrent(hDC, 0);
                    wglDeleteContext(hRC);
                    hRC = 0;
                }

                ReleaseDC(hWnd, hDC);
                hDC = 0;
            }

            PostQuitMessage(0);
            return 0;

        default:
            break;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CreateDummyGLWindow()
{
        wcl.cbSize = sizeof(wcl);
        wcl.style = CS_OWNDC;
        wcl.lpfnWndProc = DummyGLWndProc;
        wcl.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(0));
        wcl.lpszClassName = "DummyGLWindowClass";

        if (!RegisterClassEx(&wcl))
            return false;

        hWnd = CreateWindow(wcl.lpszClassName, "", WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, 0, 0, wcl.hInstance, 0);

        if (!hWnd)
            return false;

        PIXELFORMATDESCRIPTOR pfd = {0};

        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int pf = ChoosePixelFormat(hDC, &pfd);

        if (!SetPixelFormat(hDC, pf, &pfd))
            return false;

        if (!(hRC = wglCreateContext(hDC)))
            return false;

        if (!wglMakeCurrent(hDC, hRC))
            return false;

        return true;
}

void ChooseBestMSAAPixelFormat(int &pf)
{
        int attributes[] =
        {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
            WGL_COLOR_BITS_ARB,     24,
            WGL_ALPHA_BITS_ARB,     8,
            WGL_DEPTH_BITS_ARB,     24,
            WGL_STENCIL_BITS_ARB,   8,
            WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
            WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
            WGL_SAMPLES_ARB,        0,
            0, 0
        };

        int returnedPixelFormat = 0;
        UINT numFormats = 0;
        BOOL bStatus = FALSE;
        
        for (int samples = 4; samples > 0; samples /= 2)
        {
            attributes[17] = samples;

            bStatus = wglChoosePixelFormatARB(hDC, attributes, 0, 1,
                        &returnedPixelFormat, &numFormats);

            if (bStatus == TRUE && numFormats)
            {
                pf = returnedPixelFormat;
                sprintf(szAAPixelFormat, "%dx MSAA", samples);
                break;
            }
        }

        if (bStatus == FALSE)
            szAAPixelFormat[0] = '\0';
}

void ChooseMSAAPixelFormat(int &pf, int samples)
{
        int attributes[] =
        {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
            WGL_COLOR_BITS_ARB,     24,
            WGL_ALPHA_BITS_ARB,     8,
            WGL_DEPTH_BITS_ARB,     24,
            WGL_STENCIL_BITS_ARB,   8,
            WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
            WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
            WGL_SAMPLES_ARB,        samples,
            0, 0
        };

        int  returnedPixelFormat = 0;
        UINT numFormats = 0;
        BOOL bStatus = wglChoosePixelFormatARB(hDC, attributes, 0, 1, &returnedPixelFormat, &numFormats);

        if (bStatus == TRUE && numFormats)
        {
            pf = returnedPixelFormat;
            sprintf(szAAPixelFormat, "%dx MSAA", samples);
        }
        else
        {
            szAAPixelFormat[0] = '\0';
        }
}

void DestroyDummyGLWindow()
{
        if (hWnd)
        {
            PostMessage(hWnd, WM_CLOSE, 0, 0);

            BOOL bRet;
            MSG msg;

            while ((bRet = GetMessage(&msg, 0, 0, 0)) != 0)
            { 
                TranslateMessage(&msg); 
                DispatchMessage(&msg); 
            }
        }        

        UnregisterClass(wcl.lpszClassName, wcl.hInstance);
}

bool ExtensionSupported(const char *pszExtensionName)
{
        static const char *pszGLExtensions = 0;
        static const char *pszWGLExtensions = 0;

        if (!pszGLExtensions)
            pszGLExtensions = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));

        if (!pszWGLExtensions)
        {
            // WGL_ARB_extensions_string.

            typedef const char *(WINAPI * PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC);

            PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB =
                reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGARBPROC>(
                wglGetProcAddress("wglGetExtensionsStringARB"));

            if (wglGetExtensionsStringARB)
                pszWGLExtensions = wglGetExtensionsStringARB(wglGetCurrentDC());
        }

        if (!strstr(pszGLExtensions, pszExtensionName))
        {
            if (!strstr(pszWGLExtensions, pszExtensionName))
                return false;
        }

        return true;
}

BOOL wglChoosePixelFormatARB(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats)
{
    typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
    static PFNWGLCHOOSEPIXELFORMATARBPROC pfnChoosePixelFormatARB = 0;

    if (!pfnChoosePixelFormatARB)
    {
        pfnChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
        assert(pfnChoosePixelFormatARB != 0);
    }

    return pfnChoosePixelFormatARB(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats);
}

