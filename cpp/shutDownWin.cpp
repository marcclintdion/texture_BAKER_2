    if( hRC != NULL )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( hRC );
		hRC = NULL;							
	}
    if( hDC != NULL )
	{
		ReleaseDC( hWnd, hDC );
		hDC = NULL;
	}
