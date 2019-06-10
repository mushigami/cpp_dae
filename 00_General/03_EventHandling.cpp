#pragma region generalDirectives
// SDL libs
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")

// OpenGL libs
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

// SDL and OpenGL Includes
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#pragma endregion generalDirectives

#include <iostream>
#include <string>

#pragma region windowInformation
const float g_WindowWidth{ 500.0f };
const float g_WindowHeight{ 300.0f };
const std::string g_WindowTitle{ "Project name - Name, firstname - 1DAExx" };
bool g_IsVSyncOn{ true };
#pragma endregion windowInformation

#pragma region coreDeclarations
// Functions
void Initialize( );
void Run( );
void Cleanup( );
void QuitOnSDLError( );
void QuitOnOpenGlError( );

// Variables
SDL_Window* g_pWindow{ nullptr }; // The window we'll be rendering to
SDL_GLContext g_pContext; // OpenGL context
#pragma endregion coreDeclarations

#pragma region gameDeclarations
// Functions
void Draw( );
void ClearBackground( );
// Variables
#pragma endregion gameDeclarations


int main( int argc, char* args[] )
{
	// Initialize SDL and OpenGL
	Initialize( );

	// Event loop
	Run( );

	//// Wait for user to quit the program
	//std::cout << "Press ENTER to quit\n";
	//std::cin.get( );

	// Clean up SDL and OpenGL
	Cleanup( );

	return 0;
}

#pragma region gameImplementations
void ClearBackground( )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Draw( )
{
	ClearBackground( );
}

#pragma endregion gameImplementations

#pragma region coreImplementations
void Initialize( )
{
	//Initialize SDL
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		QuitOnSDLError( );
	}

	//Use OpenGL 2.1
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

	//Create window
	g_pWindow = SDL_CreateWindow(
		g_WindowTitle.c_str( ),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int( g_WindowWidth ),
		int( g_WindowHeight ),
		SDL_WINDOW_OPENGL );

	if ( g_pWindow == nullptr )
	{
		QuitOnSDLError( );
	}

	// Create an opengl context and attach it to the window 
	g_pContext = SDL_GL_CreateContext( g_pWindow );
	if ( g_pContext == nullptr )
	{
		QuitOnSDLError( );
	}

	if ( g_IsVSyncOn )
	{
		// Synchronize buffer swap with the monitor's vertical refresh
		if ( SDL_GL_SetSwapInterval( 1 ) < 0 )
		{
			QuitOnSDLError( );
		}
	}


	// Initialize Projection matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	// Set the clipping (viewing) area's left, right, bottom and top
	gluOrtho2D( 0, g_WindowWidth, 0, g_WindowHeight );

	// The viewport is the rectangular region of the window where the image is drawn.
	// Set it to the entire client area of the created window
	glViewport( 0, 0, int( g_WindowWidth ), int( g_WindowHeight ) );

	//Initialize Modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	// Enable color blending and use alpha blending
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}
void Run( )
{
	//Main loop flag
	bool quit{ false };

	//The event loop
	SDL_Event e{};
	while ( !quit )
	{
		// Poll next event from queue
		while ( SDL_PollEvent( &e ) != 0 )
		{
			// Handle the polled event
			//std::cout << "Event polled, type is " <<  std::hex << e.type << std::endl;
			switch ( e.type )
			{
			case SDL_QUIT:
				//std::cout << "\nSDL_QUIT\n";
				quit = true;
				break;
			case SDL_KEYDOWN:
				//std::cout << "\nSDL_KEYDOWN\n";
				break;
			case SDL_KEYUP:
				//std::cout << "\nSDL_KEYUP\n";
				//if ( e.key.keysym.sym == SDLK_LEFT )
				//{
				//	std::cout << "  Left arrow is released\n";
				//}
				//else if (e.key.keysym.sym == SDLK_RIGHT )
				//{
				//	std::cout << "  Right arrow is released\n";
				//}
				break;
			case SDL_MOUSEMOTION:
				//std::cout << "\nSDL_MOUSEMOTION\n";
				//std::cout << "  [" << e.motion.x << ", " << e.motion.y << "]\n";
				break;
			case SDL_MOUSEBUTTONDOWN:
				//std::cout << "\nSDL_MOUSEBUTTONDOWN\n";
				//std::cout << "  [" << e.button.x << ", "<< e.button.y << "]\n";
				//if ( e.button.button == SDL_BUTTON_LEFT )
				//{
				//	std::cout << "  Left mouse button went down\n";
				//}
				//else if ( e.button.button == SDL_BUTTON_MIDDLE )
				//{
				//	std::cout << "  Middle mouse button went down\n";
				//}
				//else if ( e.button.button == SDL_BUTTON_RIGHT )
				//{
				//	std::cout << "  Right mouse button went down\n";
				//}
				break;
			case SDL_MOUSEBUTTONUP:
				//std::cout << "\nSDL_MOUSEBUTTONUP\n";
				//std::cout << "  [" << e.button.x << ", " << e.button.y << "]\n";
				break;
			default:
				//std::cout << "\nSome other event\n";
				break;
			}
		}

		// Update the game

		// Draw in the back buffer
		Draw( );

		// Update screen: swap back and front buffer
		SDL_GL_SwapWindow( g_pWindow );
	}
}

void Cleanup( )
{
	SDL_GL_DeleteContext( g_pContext );

	SDL_DestroyWindow( g_pWindow );
	g_pWindow = nullptr;

	SDL_Quit( );
}


void QuitOnSDLError( )
{
	std::cout << "Problem during SDL initialization: ";
	std::cout << SDL_GetError( );
	std::cout << std::endl;
	Cleanup( );
	exit( -1 );
}
void QuitOnOpenGlError( )
{
	std::cout << "Problem during OpenGL initialization: ";
	std::cout << SDL_GetError( );
	std::cout << std::endl;
	Cleanup( );
	exit( -1 );
}

#pragma endregion coreImplementations
