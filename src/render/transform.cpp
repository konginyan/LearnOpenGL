#include "transform.h"

namespace ace
{
    namespace render
    {
        // -------- transform -------------
        transform::transform()
        {
            t_position = glm::mat4(1.0);
            t_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
            t_scale = glm::mat4(1.0);
        }

        transform::transform(const transform &trans)
        {
            t_position = trans.t_position;
            t_rotation = trans.t_rotation;
            t_scale = trans.t_scale;
        }
        
        transform::~transform()
        {
        }

        // 叠加位移矩阵
        void transform::translate(float x, float y, float z)
        {
            t_position = glm::translate(t_position, glm::vec3(x, y, z));
        }

        // 叠加旋转矩阵（四元数）
        void transform::rotate(float pitch, float yaw, float roll)
        {
            glm::vec3 euler(pitch, yaw, roll);
            euler = glm::radians(euler);
            glm::quat rot_quat = glm::quat(euler);
            t_rotation *= rot_quat;
        }

        // 叠加大小矩阵
        void transform::scale(float x, float y, float z)
        {
            t_scale = glm::scale(t_scale, glm::vec3(x, y, z));
        }

        glm::vec3 transform::getPosition()
        {
            glm::vec4 pos = glm::vec4(0.0, 0.0, 0.0, 1.0);
            pos = t_position * pos;
            return glm::vec3(pos.x, pos.y, pos.z);
        }

        glm::vec3 transform::getRotation()
        {
            return glm::eulerAngles(t_rotation);
        }

        glm::vec3 transform::getScale()
        {
            return glm::vec3(t_scale[0][0], t_scale[1][1], t_scale[2][2]);
        }

        // 获取完全的变换矩阵
        glm::mat4 transform::getTransform()
        {
            glm::mat4 rotate = glm::mat4_cast(t_rotation);
            return t_scale * t_position * rotate;
        }

        // 重置位移矩阵
        void transform::setPosition(float x, float y, float z)
        {
            t_position = glm::mat4(1.0);
            translate(x, y, z);
        }

        // 重置旋转矩阵
        void transform::setRotation(float pitch, float yaw, float roll)
        {
            t_rotation = glm::quat();
            rotate(pitch, yaw, roll);
        }

        // 重置大小矩阵
        void transform::setScale(float x, float y, float z)
        {
            t_scale = glm::mat4(1.0);
            scale(x, y, z);
        }

        // -------- projection -------------
        projection::projection()
        {
        }

        projection::projection(const projection &p)
        {
            t_proj_mat = p.t_proj_mat;
            t_proj_mode = p.t_proj_mode;
        }
        
        projection::~projection()
        {
        }

        void projection::setOrthProj(float left, float right, float bottom, float top, float near, float far)
        {
            t_proj_mat = glm::ortho(left, right, bottom, top, near, far);
            t_proj_mode = ORTHO;
        }

        void projection::setPersProj(float fov, float width, float height, float near, float far)
        {
            t_proj_mat = glm::perspective(glm::radians(fov), width/height, near, far);
            t_proj_mode = PERSPECTIVE;
        }

        glm::mat4 projection::getProj()
        {
            return t_proj_mat;
        }
    }
}