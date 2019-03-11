#pragma once
#include "glmSupport.h"

namespace ace
{
    namespace render
    {
        class transform
        {
        private:
            glm::mat4 t_position;
            glm::quat t_rotation;
            glm::mat4 t_scale;
            glm::vec3 t_euler;

        public:
            transform();
            transform(const transform &trans);
            ~transform();

            void translate(float x, float y, float z);
            void rotate(float pitch, float yaw, float roll);
            void scale(float x, float y, float z);
            glm::vec3 getPosition();
            glm::vec3 getRotation();
            glm::vec3 getScale();
            glm::mat4 getTransform();
            void setPosition(float x, float y, float z);
            void setRotation(float pitch, float yaw, float roll);
            void setScale(float x, float y, float z);
        };

        enum proj_type {ORTHO, PERSPECTIVE};

        class projection
        {
        private:
            glm::mat4 t_proj_mat;
            proj_type t_proj_mode;

        public:
            projection();
            projection(const projection &p);
            ~projection();

            void setOrthProj(float left, float right, float bottom, float top, float near, float far);
            void setPersProj(float fov, float width, float height, float near, float far);
            glm::mat4 getProj();
        };
    }
}