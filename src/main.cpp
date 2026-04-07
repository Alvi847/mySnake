#include <raylib.h>
#include <game.hpp>
#include <textureManager.hpp>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = (WINDOW_WIDTH * 3) / 4;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "mySnake");

	TextureManager textureManager;
	Game game(textureManager);
	
	// game loop
	while (!WindowShouldClose() && !game.ended())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		game.gameLoop(GetFrameTime());
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	textureManager.unloadAll();

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}