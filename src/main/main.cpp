#include <ctime>
#include "interaction/player.h"
#include "interaction/log.h"
#include "runtime/cube.h"
#include "runtime/light.h"
#include "runtime/camera.h"
#include "runtime/pipeline.h"

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
        LOG_DEFAULT("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_DEFAULT("Failed to initialize GLAD\n");
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    ///////////////////////// shader ///////////////////////////////
    auto lightmap_shader = ace::runtime::manager::instance()->genShad("../../../shader/base.vs", "../../../shader/base.fs");
    lightmap_shader->setMarco("L_DIRECTION 1");
    lightmap_shader->setMarco("L_POINT 0");
    lightmap_shader->setMarco("L_SPOT 0");

    ////////////////////////// texture ///////////////////////////
    auto wall_texture = ace::runtime::manager::instance()->genTex("../../../res/wall.jpg");
    auto wood_texture = ace::runtime::manager::instance()->genTex("../../../res/wood.png");
    auto metal_texture = ace::runtime::manager::instance()->genTex("../../../res/metal.png");

    ////////////////////////// pass ///////////////////////////////
    auto ple = ace::runtime::pipeline::instance();
    auto ps = ple->genPass(ace::runtime::passType::FORWARD);

    ///////////////////////// scene ///////////////////////////
    auto scn = ple->appendScene();
    auto cam = scn->getActiveCamera();
    auto view_mat = cam->getViewMat();
    auto proj_mat = cam->getProj();
    ps->setUniform("view", ace::render::uniformType::mMatrix4fv, glm::value_ptr(view_mat));
    ps->setUniform("projection", ace::render::uniformType::mMatrix4fv, glm::value_ptr(proj_mat));

    ///////////////////////// light ///////////////////////////
    ace::render::vec3 amb = { 0.2f, 0.2f, 0.2f };
    ace::render::vec3 dif = { 0.5f, 0.5f, 0.5f };
    ace::render::vec3 spc = { 1.0f, 1.0f, 1.0f };
    float shine[] = { 0.1f };
    auto lig = scn->addLight("light", ace::runtime::lightType::DIRECT);
    lig->setLightUniform("dirLight[0].direction", ace::render::m3fv, ace::render::float2array(-0.8f, 0.0f, -0.3f));
    lig->setLightUniform("dirLight[0].ambient", ace::render::m3fv, ace::render::float2array(0.3f, 0.3f, 0.3f));
    lig->setLightUniform("dirLight[0].diffuse", ace::render::m3fv, ace::render::float2array(0.8f, 0.8f, 0.8f));
    lig->setLightUniform("dirLight[0].specular", ace::render::m3fv, ace::render::float2array(0.8f, 0.8f, 0.8f));
    lig->t_trans.translate(1.0f, 0.0f, 0.0f);

    ///////////////////////// element ///////////////////////////
    auto elm = new ace::runtime::cube(scn, 0.5f, 0.5f, 0.5f);
    elm->t_matl.shad = lightmap_shader->id();
    elm->t_matl.tex0 = wall_texture->id();
    elm->t_matl.tex1 = wood_texture->id();
    elm->t_matl.tex2 = metal_texture->id();
    elm->setUniform("material.diffuse", ace::render::m1i, ace::render::float2array(1.0f));
    elm->setUniform("material.specular", ace::render::m1i, ace::render::float2array(2.0f));
    elm->setUniform("material.shininess", ace::render::m1f, ace::render::float2array(32.0f));
    scn->addElement("box", elm);

    ////////////////////// input ////////////////////////////////////
    auto input_mgr = new ace::interaction::playerInput();
    input_mgr->link(GLFW_KEY_ESCAPE, "", [&window](){glfwSetWindowShouldClose(window, true);});
    input_mgr->link(GLFW_KEY_W, "", [&cam]() {cam->move(0.2f, 0.0f);});
    input_mgr->link(GLFW_KEY_S, "", [&cam]() {cam->move(-0.2f, 0.0f);});
    input_mgr->link(GLFW_KEY_A, "", [&cam]() {cam->move(0.0f, -0.2f);});
    input_mgr->link(GLFW_KEY_D, "", [&cam]() {cam->move(0.0f, 0.2f);});
    input_mgr->link(GLFW_KEY_LEFT, "", [&cam]() {cam->turn(0.6f, 0.0f);});
    input_mgr->link(GLFW_KEY_RIGHT, "", [&cam]() {cam->turn(-0.6f, 0.0f);});
    input_mgr->link(GLFW_KEY_UP, "", [&cam]() {cam->turn(0.0f, 0.6f);});
    input_mgr->link(GLFW_KEY_DOWN, "", [&cam]() {cam->turn(0.0f, -0.6f);});

    glfwSetWindowUserPointer(window, input_mgr);

    auto func = [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
        static_cast<ace::interaction::playerInput*>(glfwGetWindowUserPointer(w))->dispatch(key);
    };

    glfwSetKeyCallback(window, func);
    glEnable(GL_DEPTH_TEST);

    std::clock_t start, end;

    //////////////// main loop /////////////////
    while(!glfwWindowShouldClose(window))
    {
        start = std::clock();

        // 渲染
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ple->render();

        // 交互前后帧（双缓冲）
        glfwSwapBuffers(window);
        glfwPollEvents();

        end = std::clock();
        auto duration = (float)(end - start) / CLOCKS_PER_SEC;
        // LOG_DEFAULT("frame rate: %f  drawcall time: %d\n", 1.0f / duration, scn->t_render.t_drawcall);
    }

    glfwTerminate();

    return 0;
}