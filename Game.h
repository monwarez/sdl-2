/*
Copyright (C) 2014 Payet thibault

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "Graphics.h"
#include "Input.h"
#include "Scene.h"

class   Game
{
    public:
        Game();
        virtual int run();
        virtual ~Game();
    protected:
        CGraphics*      m_graphics;
        CInput*         m_input;
        int             m_windowWidth;
        int             m_windowHeight;
};
#endif // GAME_H_INCLUDED
