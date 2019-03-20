#pragma once
#include <map>
#include <string>
#include "camera.h"
#include "render/manager.h"

namespace ace
{
    namespace runtime
    {
        class scene;
        class element;
        class light;
        enum lightType;

        class renderer
        {
        private:
            std::map<std::string, int> t_batches;
            scene* t_scn;

        public:
            bool t_isbatch;

        public:
            renderer(scene* scn);
            ~renderer();

            void onRenderBegin();
            void render(element* elm);
            void onRenderEnd();
        };

        class scene
        {
        private:
            std::map<std::string, element*> t_elements;
            std::map<std::string, camera*> t_cameras;
            std::string t_active_camera;

        public:
            std::map<std::string, light*> t_lights;
            renderer t_render;

        public:
            scene();
            scene(const scene &scn) = delete;
            ~scene();

            void addElement(std::string name, element* elm);
            camera* addCamera(std::string name);
            light* addLight(std::string name, lightType lt, ace::render::vec3 ambient, ace::render::vec3 diffuse, ace::render::vec3 specular);
            void setActiveCamera(std::string name);
            camera* getActiveCamera();
            element* operator[](std::string name);

            void render();
        };
    }
}