/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MaratisPlayer
// main.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
//  Maratis, Copyright (c) 2003-2011 Anael Seghezzi <www.maratis3d.com>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
//========================================================================


#include <MEngine.h>
#include <MWindow.h>

#include <MGameWinEvents.h>
#include "Maratis/MaratisPlayer.h"


// window events
void windowEvents(MWinEvent * windowEvents)
{
	MEngine * engine = MEngine::getInstance();

	// game
	MGame * game = engine->getGame();
	if(game)
	{
		if(game->isRunning()){
			gameWinEvents(windowEvents);
		}
	}

	if(windowEvents->type == MWIN_EVENT_KEY_DOWN && windowEvents->data[0] == MKEY_ESCAPE){
		MWindow::getInstance()->setActive(false);
	}

	if(windowEvents->type == MWIN_EVENT_WINDOW_CLOSE){
		MWindow::getInstance()->setActive(false);
	}
}

// update
void update(void)
{
	MaratisPlayer::getInstance()->logicLoop();
}

// draw
void draw(void)
{
	MaratisPlayer::getInstance()->graphicLoop();
	MWindow::getInstance()->swapBuffer();
}


// main
int main(int argc, char **argv)
{
	setlocale(LC_NUMERIC, "C");

	unsigned int width = 1024;
	unsigned int height = 768;
	int fullscreen = false;

	if(argc > 2)
		sscanf(argv[2], "%d", &width);
	if(argc > 3)
		sscanf(argv[3], "%d", &height);
	if(argc > 4)
		sscanf(argv[4], "%d", &fullscreen);

	// get engine (first time call onstructor)
	MEngine * engine = MEngine::getInstance();

	// get window (first time call onstructor)
	MWindow * window = MWindow::getInstance();

	// create window
	window->create("Maratis", width, height, 32, fullscreen == 1);
	if(fullscreen)
		window->hideCursor();

	// set current directory
	char rep[256];
	getRepertory(rep, argv[0]);
	window->setCurrentDirectory(rep);

	// get Maratis (first time call onstructor)
	MaratisPlayer * maratis = MaratisPlayer::getInstance();
	MRenderingContext * render = engine->getRenderingContext();

	// window pointer event
	window->setPointerEvent(windowEvents);

	// load project
	if(argc > 1){
		char filename[256];
		getGlobalFilename(filename, window->getCurrentDirectory(), argv[1]);
		maratis->loadProject(filename);
		engine->getGame()->begin();
	}

	// time
	unsigned int frequency = 60;
	unsigned long previousFrame = 0;
	unsigned long startTick = window->getSystemTick();
	
	
	// on events
	while(window->isActive())
	{
		// on events
		if(window->onEvents())
		{
			// compute target tick
			unsigned long currentTick = window->getSystemTick();

			unsigned long tick = currentTick - startTick;
			unsigned long frame = (unsigned long)(tick * (frequency * 0.001f));

			// update elapsed time
			unsigned int i;
			unsigned int steps = (unsigned int)(frame - previousFrame);

			if(window->getFocus())
			{
				// don't wait too much
				if(steps >= (frequency/2))
				{
					update();
					draw();
					previousFrame += steps;
					continue;
				}
				
				// update
				for(i=0; i<steps; i++)
				{
					update();
					previousFrame++;
				}

				// draw
				if(steps > 0){
					draw();
				}
			}
			else
			{
				previousFrame = frame;
				window->swapBuffer();
			}
		}
	}

	maratis->clear();
	return 0;
}
