#include "element.h"
#include "light.h"

namespace ace
{
    namespace runtime
    {
        scene::scene():t_render(this)
        {
            auto cam = new ace::runtime::camera();
            cam->setPersProj(45.0f, 800.0f, 600.0f, 0.1f, 100.0f);
            cam->t_trans.translate(0.0f, 0.0f, 3.0f);
            t_cameras["main"] = cam;
            setActiveCamera("main");
        }

        scene::~scene()
        {
            for(auto &elm: t_elements)
            {
                delete elm.second;
            }

            for(auto &cam: t_cameras)
            {
                delete cam.second;
            }

            for(auto &lig: t_lights)
            {
                delete lig.second;
            }
        }

        void scene::addElement(std::string name, element* elm)
        {
            t_elements[name] = elm;
        }

        camera* scene::addCamera(std::string name)
        {
            auto cam = new camera();
            t_cameras[name] = cam;
            return cam;
        }

        light* scene::addLight(std::string name, lightType lt, ace::render::vec3 ambient, ace::render::vec3 diffuse, ace::render::vec3 specular)
        {
            auto lig = new light(this, lt, ambient, diffuse, specular);
            t_lights[name] = lig;
            return lig;
        }

        void scene::setActiveCamera(std::string name)
        {
            t_active_camera = name;
        }

        camera* scene::getActiveCamera()
        {
            return t_cameras[t_active_camera];
        }

        element* scene::operator[](std::string name)
        {
            return t_elements[name];
        }

        void scene::render()
        {
            t_render.onRenderBegin();
            t_render.render();
            t_render.onRenderEnd();
        }

        // ============= renderer ===================
        renderer::renderer(scene* scn):t_isbatch(false),t_scn(scn),t_drawcall(0)
        {
        }
        
        renderer::~renderer()
        {
        }

        void renderer::makeBatch()
        {
            if (!t_isbatch)
                return;

            auto mgr = ace::render::manager::instance();
            mgr->clearVert();
            t_batches.clear();
            for (auto &e : t_scn->t_elements)
            {
                auto elm = e.second;
                int v_cnt = mgr->getVertCount(elm->t_bat.vert);
                auto v = mgr->getVert(elm->t_bat.vert, v_cnt);
                int start_size = v->appendBuffer(elm->t_vert_size, elm->t_vertices);

                if (start_size == -1)
                {
                    v_cnt = mgr->genVert(elm->t_bat.vert);
                    v = mgr->getVert(elm->t_bat.vert, v_cnt);
                    v->appendBuffer(elm->t_vert_size, elm->t_vertices);
                    elm->t_bat.vert_part = v_cnt;
                    elm->t_bat.vert_start = 0;
                }
                else
                {
                    elm->t_bat.vert_part = v_cnt;
                    elm->t_bat.vert_start = start_size;
                }

                auto batch_code = mgr->merge(elm->t_bat);
                auto b = t_batches.find(batch_code);
                if (b == t_batches.end())
                {
                    t_batches[batch_code] = 0;
                }
                else
                {
                    t_batches[batch_code] = v_cnt;
                }
            }
        }

        void renderer::onRenderBegin()
        {
            t_drawcall = 0;

            auto mgr = ace::render::manager::instance();
            auto shader = mgr->getShad(ace::render::manager::base_shader_id);
            shader->use();
            auto active_camera = t_scn->getActiveCamera();
            auto view_mat = active_camera->getViewMat();
            auto proj_mat = active_camera->getProj();

            shader->setUniformMatrix4fv("view", glm::value_ptr(view_mat));
            shader->setUniformMatrix4fv("projection", glm::value_ptr(proj_mat));
        }

        void renderer::render()
        {
            auto mgr = ace::render::manager::instance();
            if(t_isbatch)
            {
                for (auto &bat : t_batches)
                {
                    for (int i = 0; i <= bat.second; i++)
                    {
                        ace::render::batch b = mgr->split(bat.first);
                        mgr->getTex(b.tex)->bind(GL_TEXTURE0);
                        mgr->getShad(b.shad)->use();
                        auto v = mgr->getVert(b.vert, i);
                        v->bind();
                        glDrawArrays(GL_TRIANGLES, 0, v->drawArrayCount());
                        t_drawcall++;
                    }
                }
            }
            else
            {
                for (auto &e : t_scn->t_elements)
                {
                    auto elm = e.second;
                    ace::render::batch b = elm->t_bat;
                    mgr->getTex(b.tex)->bind(GL_TEXTURE0);
                    mgr->getShad(b.shad)->use();
                    auto v = mgr->getVert(b.vert, b.vert_part);
                    v->setBuffer(elm->t_vert_size, elm->t_vertices);
                    v->bind();
                    glDrawArrays(GL_TRIANGLES, 0, v->drawArrayCount());
                    t_drawcall++;
                }
            }
        }

        void renderer::onRenderEnd()
        {
            
        }
    }
}