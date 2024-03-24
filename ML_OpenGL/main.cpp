#include "stdafx.h"
#include "PopulationManager.h"

PopulationManager pop;

HWND  ghWnd;
HDC   ghDC;
HGLRC ghRC;

#define SWAPBUFFERS SwapBuffers(ghDC) 
#define BLACK_INDEX     0 

#define WIDTH 800 
#define HEIGHT 600


#define NEAR_PLANE 0.1
#define FAR_PLANE 500.0

static LRESULT CALLBACK MainWndProc( HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param );
BOOL bSetupPixelFormat( HDC );

GLvoid resize( GLsizei, GLsizei );
GLvoid initializeGL( GLsizei, GLsizei );
GLvoid updateScene( GLvoid );
GLvoid drawScene( GLvoid );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	MSG        msg;
	WNDCLASS   wndclass = {};

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = MainWndProc;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = "WinOpenGL";

	if ( !RegisterClass( &wndclass ) )
		return FALSE;

	ghWnd = CreateWindowEx( 0, wndclass.lpszClassName,
		"Generic OpenGL Sample",
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL );

	if ( !ghWnd )
		return FALSE;


	ShowWindow( ghWnd, nCmdShow );
	UpdateWindow( ghWnd );

	srand( ( unsigned int )time( NULL ) );
	pop.Start();


	while ( true )
	{
		while ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) == TRUE )
		{
			if ( GetMessage( &msg, NULL, 0, 0 ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				return TRUE;
			}
		}

		updateScene();
		drawScene();
	}
}

LRESULT CALLBACK MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT result = 0;

	PAINTSTRUCT ps;
	RECT rect;

	switch ( uMsg )
	{

	case WM_CREATE:
		ghDC = GetDC( hWnd );
		if ( !bSetupPixelFormat( ghDC ) )
			PostQuitMessage( 0 );

		ghRC = wglCreateContext( ghDC );
		wglMakeCurrent( ghDC, ghRC );
		GetClientRect( hWnd, &rect );
		initializeGL( rect.right, rect.bottom );
		break;

	case WM_PAINT:
		BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;

	case WM_SIZE:
		GetClientRect( hWnd, &rect );
		resize( rect.right, rect.bottom );
		break;

	case WM_CLOSE:
		if ( ghRC )
			wglDeleteContext( ghRC );
		if ( ghDC )
			ReleaseDC( hWnd, ghDC );
		ghRC = 0;
		ghDC = 0;

		DestroyWindow( hWnd );
		break;

	case WM_DESTROY:
		if ( ghRC )
			wglDeleteContext( ghRC );
		if ( ghDC )
			ReleaseDC( hWnd, ghDC );

		PostQuitMessage( 0 );
		break;

	default:
		result = DefWindowProc( hWnd, uMsg, wParam, lParam );
		break;
	}

	return result;
}

BOOL bSetupPixelFormat( HDC hdc )
{
	PIXELFORMATDESCRIPTOR pfd, * ppfd;
	int pixelformat;

	ppfd = &pfd;

	ppfd->nSize = sizeof( PIXELFORMATDESCRIPTOR );
	ppfd->nVersion = 1;
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	ppfd->dwLayerMask = PFD_MAIN_PLANE;
	ppfd->iPixelType = PFD_TYPE_COLORINDEX;
	ppfd->cColorBits = 8;
	ppfd->cDepthBits = 16;
	ppfd->cAccumBits = 0;
	ppfd->cStencilBits = 0;

	pixelformat = ChoosePixelFormat( hdc, ppfd );

	if ( ( pixelformat = ChoosePixelFormat( hdc, ppfd ) ) == 0 )
	{
		MessageBox( NULL, "ChoosePixelFormat failed", "Error", MB_OK );
		return FALSE;
	}

	if ( SetPixelFormat( hdc, pixelformat, ppfd ) == FALSE )
	{
		MessageBox( NULL, "SetPixelFormat failed", "Error", MB_OK );
		return FALSE;
	}

	return TRUE;
}

GLvoid resize( GLsizei width, GLsizei height )
{
	GLfloat aspect;

	glViewport( 0, 0, width, height );

	aspect = ( GLfloat )width / height;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45.0, aspect, NEAR_PLANE, FAR_PLANE );
	glMatrixMode( GL_MODELVIEW );
}

GLvoid initializeGL( GLsizei width, GLsizei height )
{
	glClearIndex( ( GLfloat )BLACK_INDEX );
	glClearDepth( 1.0 );

	glEnable( GL_DEPTH_TEST );

	glMatrixMode( GL_PROJECTION );

	gluPerspective( 45.0, ( GLfloat )width / height, NEAR_PLANE, FAR_PLANE );
	glMatrixMode( GL_MODELVIEW );
}

GLvoid drawScene( GLvoid )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	pop.Draw();

	SWAPBUFFERS;
}

GLvoid updateScene( GLvoid )
{
	pop.Update();
}