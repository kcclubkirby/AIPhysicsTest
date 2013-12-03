#include "pch.h"
#include "GameFramework.h"
#include "DrawingSurface.h"

using namespace DrawingSurface ;

GameFramework::GameFramework(void)
{
	game_over = false ;
	frames = 0 ;
	elapsed_time = 0.0 ;
}

void GameFramework::Open_Window( void* window_handle, char* title, int left, int bottom, int width, int height, byte r, byte g, byte b )
{
	Initialize_Graphics( HINSTANCE(window_handle), title, left, bottom, width, height ) ;
	Construct_DrawingSurface( width, height ) ;
	Set_Background_Color( r, g, b ) ;
}

GameFramework::~GameFramework(void)
{
}

void GameFramework::Update_Model( )
{
	// orverride this method and put your own code for updating the model here
}

void GameFramework::Render_Model( )
{
	// orverride this method and put your own code for updating the model here
}


void GameFramework::Run()
{

	while ( !game_over )
	{
		frames++ ;
		Sample_Input( &elapsed_time, &game_over ) ;

		Update_Model() ;

		Draw_Background() ;
		Render_Model() ;
		Display_Graphics() ;
	}
}



