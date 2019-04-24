#pragma once
#include "render/transform.h"

namespace ace
{
    namespace runtime
    {
        class camera
        {
        private:
            ace::render::projection t_proj;
            ace::render::transform t_trans;
            glm::vec3 t_up;
            glm::vec3 t_right;
            float t_up_angle;
            float t_right_angle;

        public:
            camera();
            camera(const camera &cam);
            ~camera();

            void move(float forward, float right);
            void turn(float up, float right);

            void setOrthProj(float left, float right, float bottom, float top, float near, float far);
            void setPersProj(float fov, float width, float height, float near, float far);
            glm::mat4 getProj() {return t_proj.getProj();}
            glm::vec3 getPosition() {return t_trans.getPosition();}
            glm::mat4 getViewMat();
        };
    }
}