#pragma once
#include <map>
#include <string>
#include "camera.h"
#include "element.h"

namespace ace
{
    namespace runtime
    {
        class scene
        {
        private:
            std::map<std::string, element*> t_elements;
            std::map<std::string, camera*> t_cameras;
            std::string t_active_camera;

        public:
            scene();
            scene(const scene &scn);
            ~scene();

            void addElement(std::string name, element* elm);
            void addCamera(std::string name, camera* cam);
            void setActiveCamera(std::string name);
            camera* getActiveCamera();
            element* operator[](std::string name);

            void render();
        };
    }
}