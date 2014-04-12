#include "Input.h"

CInput::CInput():m_x(0),m_y(0),m_xRel(0),m_yRel(0),m_terminer(false)
{
    for (unsigned i =0; i < SDL_NUM_SCANCODES; ++i)
        m_touches[i]        =   false;

    for (unsigned int i=0; i < 8 ; ++i)
        m_boutonSouris[i]   =   false;

}
CInput::~CInput()
{

}
void    CInput::UpdateEvent()
{
    m_xRel  =   0;
    m_yRel  =   0;
    while (SDL_PollEvent(&m_event))
    {
        switch (m_event.type)
        {
            case SDL_KEYDOWN:
                m_touches[m_event.key.keysym.scancode]  =   true;
                break;

            case SDL_KEYUP:
                m_touches[m_event.key.keysym.scancode]  =   false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_boutonSouris[m_event.button.button]   =   true;
                break;

            case SDL_MOUSEBUTTONUP:
                m_boutonSouris[m_event.button.button]   =   false;
                break;

            case    SDL_MOUSEMOTION:
                m_x                                     =   m_event.motion.x;
                m_y                                     =   m_event.motion.y;
                m_xRel                                  =   m_event.motion.xrel;
                m_yRel                                  =   m_event.motion.yrel;
                break;

            case SDL_WINDOWEVENT:
                if (m_event.window.event    ==  SDL_WINDOWEVENT_CLOSE)
                    m_terminer  =   true;
            default:
                break;
        }


    }
}
bool       CInput::terminer() const
{
    return m_terminer;
}
bool       CInput::GetTouche(const SDL_Scancode touche) const
{
    return m_touches[touche];
}
bool        CInput::GetBoutonSouris(const Uint8 bouton) const
{
    return m_boutonSouris[bouton];
}
bool        CInput::MotionMouse() const
{
    if (m_xRel == 0 && m_yRel == 0)
        return false;
    else
        return true;
}
int         CInput::GetX() const
{
    return m_x;
}
int         CInput::GetY() const
{
    return m_y;
}
int         CInput::GetXRel() const
{
    return m_xRel;
}
int         CInput::GetYRel() const
{
    return m_yRel;
}
void        CInput::ShowCursor(bool reponse) const
{
    reponse ? SDL_ShowCursor(SDL_ENABLE) : SDL_ShowCursor(SDL_DISABLE);
}
void        CInput::GrabCursor(bool reponse) const
{
    reponse ? SDL_SetRelativeMouseMode(SDL_TRUE) : SDL_SetRelativeMouseMode(SDL_FALSE);
}
