#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "element.h"

namespace ace
{
    namespace runtime
    {
        class mesh: public element
        {
        public:
            mesh(scene* scn, GLuint matl, std::string name, std::vector<float> vertices, std::vector<unsigned int> indices);
            mesh(mesh &elm) = delete;
            ~mesh();
        };

        class model: public element
        {
        private:
            std::string t_dir;

        public:
            model(scene* scn, GLuint matl, std::string name, std::string path);
            model(model &elm) = delete;
            ~model();

            void processNode(aiNode *node, const aiScene *scene);
            void processMesh(aiMesh *mesh, const aiScene *scene);
        };
    }
}