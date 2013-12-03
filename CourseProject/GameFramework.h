#pragma once

/**************  A simple game framework   ******************/

class GameFramework // derive your own game class from this
{
protected:
	bool  game_over ;
	int   frames ;
	float elapsed_time ;

	GameFramework( void ) ;
	virtual ~GameFramework(void);

	virtual void Update_Model() = 0 ; // you must override this with your own Update_Model
	virtual void Render_Model() = 0 ; // you must override this with your own Render_Model

public:
	void Open_Window( void* window_handle, char* title, int left, int bottom, int width, int height, byte red, byte green, byte blue ) ;
	void Run() ;
};
