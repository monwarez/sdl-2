#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input.h"
#include <string>
#include <map>
typedef     std::map<SDL_Scancode, bool> KeyStates;
typedef     std::map <std::string, SDL_Scancode> KeyConf;
class Camera
{
    public:
        Camera();
        Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical);
        void                orienter(int xRel,int yRel);
        void                deplacer(const CInput &event, Uint32 elapsed);
        void                keyBoardEvent(const CInput &event);
        void                lookAt(glm::mat4    &modelview);
        void                setPointCible(const glm::vec3 &cible);

        float               getSensitive() const;
        float               getSpeed() const;

        void                setSensitive(float sensitive);
        void                setSpeed(float speed);
        virtual ~Camera();
    protected:
        float               m_phi;
        float               m_theta;
        glm::vec3           m_orientation;

        glm::vec3           m_axeVertical;
        glm::vec3           m_deplacementLateral;

        glm::vec3           m_position;
        glm::vec3           m_pointCible;

        float               m_sensitive;
        float               m_speed;


        // pour la fluidit�
        KeyConf             m_keyconf;
        KeyStates           m_keystat;

        float               m_cstHauteur;

    private:
};

#endif // CAMERA_H
