#include "interaction/player.h"
#include "runtime/scene.h"
#include "runtime/trangle.h"
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
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); mac

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

    // char* vx = "../../shader/base.vs";
    // char* fx = "../../shader/base.fs";
    // ace::render::shaderProgram sp(vx, fx);

    // float vertices[] = {
    //     0.5f, 0.5f, 0.0f,   // 右上角
    //     0.5f, -0.5f, 0.0f,  // 右下角
    //     -0.5f, -0.5f, 0.0f, // 左下角
    //     -0.5f, 0.5f, 0.0f   // 左上角
    // };

    // ace::render::vertex vv(3);
    // vv.setBuffer(sizeof(vertices), vertices);
    // vv.setAttr(3);

    ace::render::point p1 = {0.5f, 0.5f, 0.0f};
    ace::render::point p2 = {0.5f, -0.5f, 0.0f};
    ace::render::point p3 = {-0.5f, -0.5f, 0.0f};

    auto scn = new ace::runtime::scene();

    auto cam = new ace::runtime::camera();
    cam->setPersProj(45.0f, screen_width, screen_height, 0.1f, 100.0f);
	cam->t_trans.translate(0.0f, 0.0f, 3.0f);
    scn->addCamera("main", cam);
    scn->setActiveCamera("main");

    auto elm = new ace::runtime::trangle(scn, p1, p2, p3);
    scn->addElement("trangle", elm);

    auto input_mgr = new ace::interaction::playerInput();
    input_mgr->link(GLFW_KEY_ESCAPE, "", [&window](){glfwSetWindowShouldClose(window, true);});
    input_mgr->link(GLFW_KEY_W, "", [&cam](){cam->t_trans.translate(0.0f,0.0f,-1.0f);});
    input_mgr->link(GLFW_KEY_S, "", [&cam](){cam->t_trans.translate(0.0f,0.0f,1.0f);});
    input_mgr->link(GLFW_KEY_A, "", [&cam](){cam->t_trans.rotate(0.0f,0.3f,0.0f);});
    input_mgr->link(GLFW_KEY_D, "", [&cam](){cam->t_trans.rotate(0.0f,-0.3f,0.0f);});

    glfwSetWindowUserPointer(window, input_mgr);

    auto func = [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        static_cast<ace::interaction::playerInput*>(glfwGetWindowUserPointer(w))->dispatch(key);
    };

    glfwSetKeyCallback(window, func);

    while(!glfwWindowShouldClose(window))
    {
        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        scn->render();

        // 交互前后帧（双缓冲）
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}