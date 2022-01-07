#include "Game.h"

Game::Game()
{

}
Game::~Game()
{

}
bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,
			width, height, flags);
		if (m_pWindow != 0) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer,
					255, 0, 0, 255);

				//SDL_Surface* pTempSurface = SDL_LoadBMP("assets/animate.bmp");
				SDL_Surface* pTempSurface = IMG_Load("assets/run_frames.png");
				m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer,
					pTempSurface);
				SDL_FreeSurface(pTempSurface);
				
				m_sourceRectangle.w = 200;
				m_sourceRectangle.h = 160;

				m_destinationRectangle.x = m_sourceRectangle.x = 0;
				m_destinationRectangle.y = m_sourceRectangle.y = 0;
				m_destinationRectangle.w = m_sourceRectangle.w;
				m_destinationRectangle.h = m_sourceRectangle.h;
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}
	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully, start the main loop
		return true;
}
void Game::update()
{
	
	m_sourceRectangle.y = 160 * int(((SDL_GetTicks() / 100) % 5));
	cout << m_sourceRectangle.y << endl;
	if (m_sourceRectangle.y == 160 * 5)
	{
		m_sourceRectangle.x = 200 * int(((SDL_GetTicks() / 100) % 4));
	//	m_sourceRectangle.x += 200;
	}
		
		
	//	if(i % 4 == 0)
	
//	m_sourceRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6));

}
void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color
	
	SDL_RenderCopyEx(m_pRenderer, m_pTexture,
		&m_sourceRectangle, &m_destinationRectangle,
		0, 0, SDL_FLIP_NONE); // pass in the horizontal flip

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}
void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}