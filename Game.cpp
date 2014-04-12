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
#include "Game.h"
Game::Game()
{
    // plus tard on utilisera un fichier
    m_graphics  =   new CGraphics(1600,900,true,"game engine",32,2,
                                  3,3); // tant pis pour le support de mac os
    m_input     =   new CInput;

}
int     Game::run()
{

    CMD2Model   model;
    CEntity     entity;
    CScene      scene;

    //
    model.LoadModel("./data/md2/cobra/cobra.md2");
    model.LoadTexture("./data/md2/cobra/cobra.jpg");
    model.LoadVBO();
    entity.SetModel(&model);
    entity.SetScale(0.1);
    MD2Object   md2Object(&entity);
    md2Object.SetAnimation(0,20,true);

    //m_input->GrabCursor(true);    // ne fonctionne pas bien
    m_input->ShowCursor(false);
    scene.AttachObject(&md2Object);
    scene.AttachInput(m_input);
    Uint32 framerate = (1000/50);
    Uint32 debutBoucle(0), elapsed(0), finBoucle(0);
    while (!m_input->terminer())
    {

        debutBoucle =   SDL_GetTicks();
        m_input->UpdateEvent();

        glClearColor(200/255.0,200/255.0,200/255.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.Show(elapsed);

        m_graphics->SwapWindow();

        finBoucle   =   SDL_GetTicks();
        elapsed =   finBoucle - debutBoucle;
        if (elapsed < framerate)
            SDL_Delay(framerate - elapsed);
        if (m_input->GetTouche(SDL_SCANCODE_ESCAPE))
            break;
        elapsed =   SDL_GetTicks() - debutBoucle;
    }

    return 0;
}
Game::~Game()
{
    delete m_graphics;
    delete m_input;
    SDL_Quit();
}
