#include "scene.h"

namespace ace
{
    namespace runtime
    {
        scene::scene():t_active_camera("")
        {
        }

        scene::scene(const scene &scn)
        {
            t_elements = scn.t_elements;
            t_cameras = scn.t_cameras;
            t_active_camera = scn.t_active_camera;
        }
        
        scene::~scene()
        {
            for(auto elm: t_elements)
            {
                delete elm.second;
            }

            for(auto cam: t_cameras)
            {
                delete cam.second;
            }
        }

        void scene::addElement(std::string name, element* elm)
        {
            t_elements[name] = elm;
        }

        void scene::addCamera(std::string name, camera* cam)
        {
            t_cameras[name] = cam;
        }

        void scene::setActiveCamera(std::string name)
        {
            t_active_camera = name;
        }

        camera* scene::getActiveCamera()
        {
            return t_cameras[t_active_camera];
        }

        element* scene::operator[](std::string name)
        {
            return t_elements[name];
        }

        void scene::render()
        {
            for(auto elm: t_elements)
            {
                elm.second->render();
            }
        }
    }
}