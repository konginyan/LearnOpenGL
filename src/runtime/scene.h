#pragma once
#include <unordered_map>
#include <string>
#include "camera.h"
#include "manager.h"

namespace ace
{
    namespace runtime
    {
        class scene;
        class element;
        class light;
        enum lightType;

        class scene
        {
        private:
            GLuint t_id;
            std::unordered_map<std::string, camera*> t_cameras;
            std::string t_active_camera;

        public:
            std::unordered_map<std::string, element*> t_elements;
            std::unordered_map<std::string, light*> t_lights;

        public:
            scene(GLuint id);
            scene(const scene &scn) = delete;
            ~scene();

            void addElement(std::string name, element* elm);
            camera* addCamera(std::string name);
            light* addLight(std::string name, lightType lt);
            void setActiveCamera(std::string name);
            camera* getActiveCamera();
            element* operator[](std::string name);

            inline GLuint id() {return t_id;}
        };
    }
}