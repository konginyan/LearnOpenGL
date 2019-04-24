#include "camera.h"
#include "interaction/log.h"

namespace ace
{
    namespace runtime
    {
        camera::camera():t_up(0.0f, 1.0f, 0.0f), t_right(1.0f, 0.0f, 0.0f), t_up_angle(0.0f), t_right_angle(0.0f)
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

        void camera::move(float forward, float right)
        {
            auto vec_forward = glm::cross(t_up, t_right);
            vec_forward = glm::normalize(vec_forward);
            auto val_forward = forward * vec_forward;
            auto val_right = right * t_right;
            t_trans.translate(val_forward.x, 0.0f, val_forward.z);
            t_trans.translate(val_right.x, 0.0f, val_right.z);
        }

        void camera::turn(float up, float right)
        {
            glm::vec3 euler(0.0f, up, 0.0f);
            euler = glm::radians(euler);
            glm::quat rot_quat = glm::quat(euler);
            t_right = rot_quat * t_right;

            t_up_angle += up;
            t_right_angle += right;
        }

        void camera::setOrthProj(float left, float right, float bottom, float top, float near, float far)
        {
            t_proj.setOrthProj(left, right, bottom, top, near, far);
        }

        void camera::setPersProj(float fov, float width, float height, float near, float far)
        {
            t_proj.setPersProj(fov, width, height, near, far);
        }

        glm::mat4 camera::getViewMat()
        {
            auto view_pos = glm::mat4(1.0);
            auto view_rot = glm::mat4(1.0);
            auto view_scale = glm::mat4(1.0);

            glm::vec3 revert_pos = -t_trans.getPosition();
            view_pos = glm::translate(view_pos, revert_pos);

            glm::quat q = glm::angleAxis(glm::radians(-t_right_angle), glm::vec3(1,0,0));
            q *= glm::angleAxis(glm::radians(-t_up_angle), glm::vec3(0,1,0));
            view_rot = glm::mat4_cast(q);

            glm::vec3 revert_scale = t_trans.getScale();
            revert_scale[0] = 1/revert_scale[0];
            revert_scale[1] = 1/revert_scale[1];
            revert_scale[2] = 1/revert_scale[2];
            view_scale = glm::scale(view_scale, revert_scale);

            // LOG_DEFAULT("%s\n", glm::to_string(view_pos));
            // LOG_DEFAULT("%s\n", glm::to_string(view_rot);
            // LOG_DEFAULT("%s\n", glm::to_string(view_scale);

            return view_scale * view_rot * view_pos;
        }
    }
}