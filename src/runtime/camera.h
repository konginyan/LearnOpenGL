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
            static glm::vec3 c_up;

        public:
            ace::render::transform t_trans;

        public:
            camera();
            camera(const camera &cam);
            ~camera();

            void setOrthProj(float left, float right, float bottom, float top, float near, float far);
            void setPersProj(float fov, float width, float height, float near, float far);
            glm::mat4 getProj();
            glm::mat4 getViewMat();
        };
    }
}