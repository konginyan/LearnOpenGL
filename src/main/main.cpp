#include <ctime>
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
    scn->t_render.t_isbatch = true;

    ace::render::shaderOption options = ace::render::default_shader_option;
    options.TEXTURE = true;
    auto base_shader = new ace::render::shaderProgram("../../../shader/base.vs", "../../../shader/base.fs", options);
    ace::render::manager::base_shader_id = base_shader->id();
    ace::render::manager::instance()->genShad(base_shader);
    std::cout << "generate base shader: " << base_shader->id() << std::endl;

    auto base_texture = new ace::render::texture("../../../res/wall.jpg");
    ace::render::manager::base_texture_id = base_texture->id();
    ace::render::manager::instance()->genTex(base_texture);
    std::cout << "generate base texture: " << base_texture->id() << std::endl;


    ace::render::vec3 p1 = {-0.5f, -0.5f, 0.0f};
    ace::render::vec3 p2 = {0.5f, -0.5f, 0.0f};
    ace::render::vec3 p3 = {0.0f, 0.5f, 0.0f};
    ace::runtime::trangle* elm;
    char elm_name[10000];
    for(int i=0; i<10000; i++)
    {
        //p1.z += 1;
        //p2.z += 1;
        //p3.z += 1;
        elm = new ace::runtime::trangle(scn, p1, p2, p3);
        sprintf(elm_name, "t%d", i);
        scn->addElement(elm_name, elm);
    }
    scn->t_render.makeBatch();

    // ace::render::vec3 amb = {0.2f, 0.2f, 0.2f};
    // ace::render::vec3 dif = {0.5f, 0.5f, 0.5f};
    // ace::render::vec3 spc = {1.0f, 1.0f, 1.0f};
    // auto lig = scn->addLight("light", ace::runtime::lightType::POINT, amb, dif, spc);
    // lig->t_trans.translate(3.0f, 3.0f, 3.0f);

    auto cam = scn->getActiveCamera();
    auto input_mgr = new ace::interaction::playerInput();
    input_mgr->link(GLFW_KEY_ESCAPE, "", [&window](){glfwSetWindowShouldClose(window, true);});
    input_mgr->link(GLFW_KEY_W, "", [&cam]() {cam->t_trans.translate(0.0f, 0.0f, -0.1f); });
    input_mgr->link(GLFW_KEY_S, "", [&cam]() {cam->t_trans.translate(0.0f, 0.0f, 0.1f); });
    input_mgr->link(GLFW_KEY_A, "", [&cam]() {cam->t_trans.translate(-0.1f, 0.0f, 0.0f); });
    input_mgr->link(GLFW_KEY_D, "", [&cam]() {cam->t_trans.translate(0.1f, 0.0f, 0.0f); });
    input_mgr->link(GLFW_KEY_LEFT, "", [&cam]() {cam->t_trans.rotate(0.0f, 0.6f, 0.0f); });
    input_mgr->link(GLFW_KEY_RIGHT, "", [&cam]() {cam->t_trans.rotate(0.0f, -0.6f, 0.0f); });
    input_mgr->link(GLFW_KEY_E, "", [&elm]() {elm->t_trans.translate(0.1f, 0.0f, 0.0f); elm->update(); });

    glfwSetWindowUserPointer(window, input_mgr);

    auto func = [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        static_cast<ace::interaction::playerInput*>(glfwGetWindowUserPointer(w))->dispatch(key);
    };

    glfwSetKeyCallback(window, func);

    std::clock_t start, end;

    while(!glfwWindowShouldClose(window))
    {
        start = std::clock();

        // 渲染
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //scn->update();
        scn->render();

        // 交互前后帧（双缓冲）
        glfwSwapBuffers(window);
        glfwPollEvents();

        end = std::clock();
        auto duration = (float)(end - start) / CLOCKS_PER_SEC;
        std::cout << "frame rate: " << 1.0f / duration << "  drawcall time: " << scn->t_render.t_drawcall << std::endl;
    }

    glfwTerminate();

    return 0;
}