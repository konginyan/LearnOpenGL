#include "element.h"
#include "light.h"

namespace ace
{
    namespace runtime
    {
        scene::scene()
        {
            auto cam = new ace::runtime::camera();
            cam->setPersProj(45.0f, 800.0f, 600.0f, 0.1f, 100.0f);
            cam->t_trans.translate(0.0f, 0.0f, 3.0f);
            t_cameras["main"] = cam;
            setActiveCamera("main");
        }

        scene::scene(const scene &scn)
        {
            t_elements = scn.t_elements;
            t_cameras = scn.t_cameras;
            t_active_camera = scn.t_active_camera;
            t_lights = scn.t_lights;
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

            for(auto lig: t_lights)
            {
                delete lig.second;
            }
        }

        void scene::addElement(std::string name, element* elm)
        {
            t_elements[name] = elm;
        }

        camera* scene::addCamera(std::string name)
        {
            auto cam = new camera();
            t_cameras[name] = cam;
            return cam;
        }

        light* scene::addLight(std::string name, lightType lt, ace::render::vec3 ambient, ace::render::vec3 diffuse, ace::render::vec3 specular)
        {
            auto lig = new light(this, lt, ambient, diffuse, specular);
            t_lights[name] = lig;
            return lig;
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