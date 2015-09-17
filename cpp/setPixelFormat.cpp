
	GLuint PixelFormat;

    PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    hDC = GetDC( hWnd );
    PixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, PixelFormat, &pfd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);
