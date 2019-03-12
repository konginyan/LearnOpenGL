#include "camera.h"

namespace ace
{
    namespace runtime
    {
        glm::vec3 camera::c_up = glm::vec3(0.0f, 1.0f, 0.0f);

        camera::camera()
        {
        }

        camera::camera(const camera &cam)
        {
            t_proj = cam.t_proj;
            t_trans = cam.t_trans;
        }
        
        camera::~camera()
        {
        }

        void camera::setOrthProj(float left, float right, float bottom, float top, float near, float far)
        {
            t_proj.setOrthProj(left, right, bottom, top, near, far);
        }

        void camera::setPersProj(float fov, float width, float height, float near, float far)
        {
            t_proj.setPersProj(fov, width, height, near, far);
        }

        glm::mat4 camera::getProj()
        {
            return t_proj.getProj();
        }

        glm::mat4 camera::getViewMat()
        {
            auto view_pos = glm::mat4(1.0);
            auto view_rot = glm::mat4(1.0);
            auto view_scale = glm::mat4(1.0);

            glm::vec3 revert_pos = -t_trans.getPosition();
            view_pos = glm::translate(view_pos, revert_pos);

            glm::vec3 revert_rot = -t_trans.getRotation();
            auto view_quat = glm::quat(revert_rot);
            view_rot = glm::mat4_cast(view_quat);

            glm::vec3 revert_scale = t_trans.getScale();
            revert_scale[0] = 1/revert_scale[0];
            revert_scale[1] = 1/revert_scale[1];
            revert_scale[2] = 1/revert_scale[2];
            view_scale = glm::scale(view_scale, revert_scale);

            // std::cout << glm::to_string(view_pos) << std::endl;
            // std::cout << glm::to_string(view_rot) << std::endl;
            // std::cout << glm::to_string(view_scale) << std::endl;

            return view_scale * view_rot * view_pos;
        }
    }
}