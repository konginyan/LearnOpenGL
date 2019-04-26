#pragma once
#include <vector>
#include <unordered_map>
#include "light.h"
#include "render/frame.h"

namespace ace
{
    namespace runtime
    {
        enum passType
        {
            FORWARD,
            POSTPROCESS
        };

        const std::string ALL_PASS = "all";

        class pass
        {
        private:
            GLuint t_id;
            passType t_type;
            ace::render::vertex t_quad;

        public:
            GLuint t_target;
            GLuint t_shader;
            scene* t_scene;
            std::string t_pass_filter;

            std::unordered_map<char*, uniform> t_uniforms;
            std::unordered_map<GLuint, GLuint> t_tex_idx; // 所需fbo参数格式 (attach_type, texture_index)
            std::unordered_map<GLuint, GLuint> t_tex_input; // 接受上一个pass生成的fbo (texture_id, texture_index)

        public:
            pass(GLuint id, passType type);
            ~pass();
            void setUniform(char* name, ace::render::uniformType utype, const float* val);

            void render();

            inline GLuint id() {return t_id;}
        };

        class pipeline
        {
        private:
            std::unordered_map<GLuint, scene*> t_scenes;
            std::unordered_map<GLuint, pass*> t_passes;
            std::unordered_map<GLuint, ace::render::frame*> t_frames;
            std::vector<GLuint> t_pipeline;

            GLuint t_active_scene;
            GLuint t_pass_count;
            GLuint t_scene_count;

        public:
            static pipeline* instance()
            {
                static pipeline t_ins;
                return &t_ins;
            }

        public:
            pipeline();
            ~pipeline();

            scene* appendScene();
            void setActiveScene(GLuint id);
            scene* getActiveScene() {return t_scenes[t_active_scene];}
            pass* genPass(passType type);
            pass* getPass(GLuint id) {return t_passes[id];}
            ace::render::frame* genFrame();
            ace::render::frame* getFrame(GLuint id) {return t_frames[id];}
            void appendPass(GLuint id) {t_pipeline.push_back(id);}

            void render();
        };
    }
}