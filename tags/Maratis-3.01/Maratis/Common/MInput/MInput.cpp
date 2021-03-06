/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Maratis
// MInput.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
// Copyright (c) 2003-2011 Anael Seghezzi <www.maratis3d.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================


#include "MInput.h"


MInput::MInput(void)
{
	// ASCII keys
	char name[2] = {0, 0};
	for(int i=65; i<=90; i++){
		name[0] = i;
		createKey(name);
	}

	// keyboard keys
	createKey("BACKSPACE");
	createKey("TAB");
	createKey("ESCAPE");
	createKey("SPACE");
	createKey("DELETE");
	createKey("0");
	createKey("1");
	createKey("2");
	createKey("3");
	createKey("4");
	createKey("5");
	createKey("6");
	createKey("7");
	createKey("8");
	createKey("9");
	createKey("ENTER");
	createKey("UP");
	createKey("DOWN");
	createKey("LEFT");
	createKey("RIGHT");
	createKey("F1");
	createKey("F2");
	createKey("F3");
	createKey("F4");
	createKey("F5");
	createKey("F6");
	createKey("F7");
	createKey("F8");
	createKey("F9");
	createKey("F10");
	createKey("F11");
	createKey("F12");
	createKey("RSHIFT");
	createKey("LSHIFT");
	createKey("RCONTROL");
	createKey("LCONTROL");
	createKey("RALT");
	createKey("LALT");

	// mouse keys
	createKey("MOUSE_BUTTON1");
	createKey("MOUSE_BUTTON2");
	createKey("MOUSE_BUTTON3");

	// joystick keys
	createKey("JOY1_BUTTON1");
	createKey("JOY1_BUTTON2");
	createKey("JOY1_BUTTON3");
	createKey("JOY1_BUTTON4");
	createKey("JOY1_BUTTON5");
	createKey("JOY1_BUTTON6");
	createKey("JOY1_BUTTON7");
	createKey("JOY1_BUTTON8");

	createKey("JOY2_BUTTON1");
	createKey("JOY2_BUTTON2");
	createKey("JOY2_BUTTON3");
	createKey("JOY2_BUTTON4");
	createKey("JOY2_BUTTON5");
	createKey("JOY2_BUTTON6");
	createKey("JOY2_BUTTON7");
	createKey("JOY2_BUTTON8");

	// axis
	createAxis("MOUSE_X");
	createAxis("MOUSE_Y");

	createAxis("JOY1_X");
	createAxis("JOY1_Y");
	createAxis("JOY1_Z");
	createAxis("JOY1_R");
	createAxis("JOY1_U");
	createAxis("JOY1_V");

	createAxis("JOY2_X");
	createAxis("JOY2_Y");
	createAxis("JOY2_Z");
	createAxis("JOY2_R");
	createAxis("JOY2_U");
	createAxis("JOY2_V");
}

MInput::~MInput(void)
{}

void MInput::createKey(const char * name)
{
	if(name)
		m_keys[name] = 0;
}

void MInput::createAxis(const char * name)
{
	if(name)
		m_axis[name] = 0;
}

void MInput::downKey(const char * name)
{
	map<string, int>::iterator iter = m_keys.find(name);
	if(iter != m_keys.end())
		iter->second = 1;
}

void MInput::upKey(const char * name)
{
	map<string, int>::iterator iter = m_keys.find(name);
	if(iter != m_keys.end())
		iter->second = 3;
}

void MInput::setAxis(const char * name, float axis)
{
	map<string, float>::iterator iter = m_axis.find(name);
	if(iter != m_axis.end())
		iter->second = axis;
}

bool MInput::isKeyPressed(const char * name)
{
	map<string, int>::iterator iter = m_keys.find(name);
	if(iter != m_keys.end())
		return (iter->second == 1 || iter->second == 2);

	return false;
}

bool MInput::onKeyDown(const char * name)
{
	map<string, int>::iterator iter = m_keys.find(name);
	if(iter != m_keys.end())
		return (iter->second == 1);

	return false;
}

bool MInput::onKeyUp(const char * name)
{
	map<string, int>::iterator iter = m_keys.find(name);
	if(iter != m_keys.end())
		return (iter->second == 3);

	return false;
}

float MInput::getAxis(const char * name)
{
	map<string, float>::iterator iter = m_axis.find(name);
	if(iter != m_axis.end())
		return iter->second;

	return 0;
}

void MInput::flush(void)
{
	// keys
	map<string, int>::iterator
		mit (m_keys.begin()),
		mend(m_keys.end());

	for(;mit!=mend;++mit)
	{
	  if(mit->second == 1)
		  mit->second = 2;
	  else if(mit->second == 3)
		  mit->second = 0;
	}
}