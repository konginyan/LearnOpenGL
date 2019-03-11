#pragma once
#include <map>
#include <string>
#include <functional>
#include "render/glSupport.h"

namespace ace
{
    namespace interaction
    {
        class playerInput
        {
        private:
            std::map<unsigned int, std::map<std::string, std::function<void(void)>>> t_events;
            std::string t_condition;

        public:
            playerInput();
            playerInput(const playerInput &p);
            ~playerInput();

            void link(unsigned int input, std::string condition, std::function<void(void)> callback);
            void dispatch(unsigned int input);
            std::map<std::string, std::function<void(void)>> operator[](unsigned int input);

            void keyInputCb(GLFWwindow* window, int key, int scancode, int action, int mods);
        };
    }
}