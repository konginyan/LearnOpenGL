#include "interaction/player.h"
#include "runtime/scene.h"
#include "runtime/trangle.h"
#include "runtime/cube.h"
#include "runtime/light.h"
#include "runtime/camera.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // mac

    float screen_width = 800.0f;
    float screen_height = 600.0f;

	GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Ace Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    auto scn = new ace::runtime::scene();

    auto elm = new ace::runtime::cube(scn, 0.5f, 0.5f, 0.5f);
    scn->addElement("cube", elm);

    ace::render::vec3 amb = {0.2f, 0.2f, 0.2f};
    ace::render::vec3 dif = {0.5f, 0.5f, 0.5f};
    ace::render::vec3 spc = {1.0f, 1.0f, 1.0f};
    auto lig = scn->addLight("light", ace::runtime::lightType::POINT, amb, dif, spc);
    lig->t_trans.translate(3.0f, 3.0f, 3.0f);

    auto input_mgr = new ace::interaction::playerInput();
    input_mgr->link(GLFW_KEY_ESCAPE, "", [&window](){glfwSetWindowShouldClose(window, true);});
    // input_mgr->link(GLFW_KEY_W, "", [&cam](){cam->t_trans.rotate(1.0f,0.0f,0.0f);});
    // input_mgr->link(GLFW_KEY_S, "", [&cam](){cam->t_trans.rotate(-1.0f,0.0f,0.0f);});
    // input_mgr->link(GLFW_KEY_A, "", [&cam](){cam->t_trans.rotate(0.0f,1.0f,0.0f);});
    // input_mgr->link(GLFW_KEY_D, "", [&cam](){cam->t_trans.rotate(0.0f,-1.0f,0.0f);});
    input_mgr->link(GLFW_KEY_UP, "", [&elm](){elm->t_trans.rotate(-1.0f,0.0f,0.0f);});
    input_mgr->link(GLFW_KEY_DOWN, "", [&elm](){elm->t_trans.rotate(1.0f,0.0f,0.0f);});
    input_mgr->link(GLFW_KEY_LEFT, "", [&elm](){elm->t_trans.rotate(0.0f,-1.0f,0.0f);});
    input_mgr->link(GLFW_KEY_RIGHT, "", [&elm](){elm->t_trans.rotate(0.0f,1.0f,0.0f);});

    glfwSetWindowUserPointer(window, input_mgr);

    auto func = [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        static_cast<ace::interaction::playerInput*>(glfwGetWindowUserPointer(w))->dispatch(key);
    };

    glfwSetKeyCallback(window, func);

    while(!glfwWindowShouldClose(window))
    {
        // 渲染
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        scn->render();

        // 交互前后帧（双缓冲）
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}