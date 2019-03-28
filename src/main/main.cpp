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
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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

    ///////////////////////// shader ///////////////////////////////
    ace::render::shaderOption options = ace::render::default_shader_option;
    options.TEXTURE = true;
    auto base_shader = ace::render::manager::instance()->genShad("../../../shader/base.vs", "../../../shader/base.fs", options);

    options = ace::render::default_shader_option;
    options.COLOR = true;
    auto color_shader = ace::render::manager::instance()->genShad("../../../shader/base.vs", "../../../shader/base.fs", options);

    options = ace::render::default_shader_option;
    auto empty_shader = ace::render::manager::instance()->genShad("../../../shader/base.vs", "../../../shader/base.fs", options);

    options = ace::render::default_shader_option;
    options.LIGHT = true;
    options.NORMAL = true;
    options.L_DIRECTION = 1;
    auto light_shader = ace::render::manager::instance()->genShad("../../../shader/base.vs", "../../../shader/base.fs", options);

    ////////////////////////// texture ///////////////////////////
    auto wall_texture = ace::render::manager::instance()->genTex("../../../res/wall.jpg");
    ace::render::manager::instance()->getTex(wall_texture)->bind(GL_TEXTURE0);
    auto wood_texture = ace::render::manager::instance()->genTex("../../../res/wood.png");
    ace::render::manager::instance()->getTex(wood_texture)->bind(GL_TEXTURE1);
    auto metal_texture = ace::render::manager::instance()->genTex("../../../res/metal.png");
    ace::render::manager::instance()->getTex(metal_texture)->bind(GL_TEXTURE2);

    ////////////////////////// scene ////////////////////////////
    auto scn = new ace::runtime::scene();
    scn->t_render.t_isbatch = false;

    //ace::render::vec3 p1 = { -0.5f, -0.5f, 0.0f };
    //ace::render::vec3 p2 = { 0.5f, -0.5f, 0.0f };
    //ace::render::vec3 p3 = { 0.0f, 0.5f, 0.0f };
    //ace::runtime::element* elm;
    //char elm_name[30000];
    //for (int i = 0; i < 30000; i++)
    //{
    //    elm = new ace::runtime::trangle(scn, p1, p2, p3);
    //    elm->t_bat.shad = base_shader;
    //    elm->t_bat.tex = wall_texture;
    //    sprintf(elm_name, "t%d", i);
    //    scn->addElement(elm_name, elm);
    //}
    //scn->t_render.makeBatch();

    ace::render::vec3 amb = { 0.2f, 0.2f, 0.2f };
    ace::render::vec3 dif = { 0.5f, 0.5f, 0.5f };
    ace::render::vec3 spc = { 1.0f, 1.0f, 1.0f };
    float shine[] = { 0.1f };
    auto lig = scn->addLight("light", ace::runtime::lightType::DIRECT);
    lig->t_bat.shad = empty_shader;
    lig->setLightUniform("dirLight[0].direction", ace::render::m3fv, ace::render::float2array(-0.8f, 0.0f, -0.3f));
    lig->setLightUniform("dirLight[0].ambient", ace::render::m3fv, ace::render::float2array(0.3f, 0.3f, 0.3f));
    lig->setLightUniform("dirLight[0].diffuse", ace::render::m3fv, ace::render::float2array(0.8f, 0.8f, 0.8f));
    lig->setLightUniform("dirLight[0].specular", ace::render::m3fv, ace::render::float2array(0.8f, 0.8f, 0.8f));
    lig->t_trans.translate(1.0f, 0.0f, 0.0f);
    lig->update();

    auto elm = new ace::runtime::cube(scn, 0.5f, 0.5f, 0.5f);
    elm->t_bat.shad = light_shader;
    elm->setUniform("material.diffuse", ace::render::m1i, ace::render::float2array(1.0f));
    elm->setUniform("material.specular", ace::render::m1i, ace::render::float2array(2.0f));
    elm->setUniform("material.shininess", ace::render::m1f, ace::render::float2array(32.0f));
    scn->addElement("ccc", elm);

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
    glEnable(GL_DEPTH_TEST);

    std::clock_t start, end;

    while(!glfwWindowShouldClose(window))
    {
        start = std::clock();

        // 渲染
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //scn->update();
        scn->render();

        // 交互前后帧（双缓冲）
        glfwSwapBuffers(window);
        glfwPollEvents();

        end = std::clock();
        auto duration = (float)(end - start) / CLOCKS_PER_SEC;
        //std::cout << "frame rate: " << 1.0f / duration << "  drawcall time: " << scn->t_render.t_drawcall << std::endl;
    }

    glfwTerminate();

    return 0;
}