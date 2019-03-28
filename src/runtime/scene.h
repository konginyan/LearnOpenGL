#pragma once
#include <unordered_map>
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
            std::unordered_map<std::string, int> t_batches;
            scene* t_scn;

        public:
            bool t_isbatch;
            int t_drawcall;

        public:
            renderer(scene* scn);
            ~renderer();

            void makeBatch();
            void onRenderBegin();
            void render();
            void onRenderEnd();
        };

        class scene
        {
        private:
            std::unordered_map<std::string, camera*> t_cameras;
            std::string t_active_camera;

        public:
            std::unordered_map<std::string, element*> t_elements;
            std::unordered_map<std::string, light*> t_lights;
            renderer t_render;

        public:
            scene();
            scene(const scene &scn) = delete;
            ~scene();

            void addElement(std::string name, element* elm);
            camera* addCamera(std::string name);
            light* addLight(std::string name, lightType lt);
            void setActiveCamera(std::string name);
            camera* getActiveCamera();
            element* operator[](std::string name);

            void update();
            void render();
        };
    }
}