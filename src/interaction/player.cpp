#include "player.h"

namespace ace
{
    namespace interaction
    {
        playerInput::playerInput():t_condition("")
        {
        }

        playerInput::playerInput(const playerInput &p)
        {
            t_events = p.t_events;
            t_condition = p.t_condition;
        }

        playerInput::~playerInput()
        {
        }

        void playerInput::link(unsigned int input, std::string condition, std::function<void(void)> callback)
        {
            t_events[input][condition] = callback;
        }

        void playerInput::dispatch(unsigned int input)
        {
            auto iter_input = t_events.find(input);
            if(iter_input != t_events.end())
            {
                auto evt = iter_input->second;
                auto iter_con = evt.find(t_condition);
                if(iter_con != evt.end())
                {
                    auto callback = iter_con->second;
                    callback();
                }
            }
        }

        std::map<std::string, std::function<void(void)>> playerInput::operator[](unsigned int input)
        {
            return t_events[input];
        }

        void playerInput::keyInputCb(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if(action == GLFW_PRESS)
            {
                dispatch(key);
            }

        }
    }
}