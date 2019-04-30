#include "model.h"
#include "interaction/log.h"

namespace ace
{
    namespace runtime
    {
        // ============ mesh ===================
        mesh::mesh(scene* scn, GLuint matl, std::string name, std::vector<float> vertices, std::vector<unsigned int> indices):element(scn, matl, name)
        {
            t_vertices = vertices;
            t_indices = indices;
            t_vert = new ace::render::vertex(8);
            t_vert->setAttr(ace::render::vertexDataType::position);
            t_vert->setAttr(ace::render::vertexDataType::normal);
            t_vert->setAttr(ace::render::vertexDataType::texcoord2d);
            t_vert->setBuffer(t_vertices.size() * sizeof(float), &t_vertices[0]);
            t_vert->setIndex(t_indices.size() * sizeof(unsigned int), &t_indices[0]);
        }
        
        mesh::~mesh()
        {
        }


        // ============ model ==================
        model::model(scene* scn, GLuint matl, std::string name, std::string path):element(scn, matl, name)
        {
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                LOG_DEFAULT("error on load model: %s\n", importer.GetErrorString());
                return;
            }

            t_dir = path.substr(0, path.find_last_of('/'));
            processNode(scene->mRootNode, scene);
        }

        model::~model()
        {
        }

        void model::processNode(aiNode* node, const aiScene* scene)
        {
            for(unsigned int i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh* amesh = scene->mMeshes[node->mMeshes[i]];
                processMesh(amesh, scene);
            }

            for(unsigned int i = 0; i < node->mNumChildren; i++)
            {
                processNode(node->mChildren[i], scene);
            }
        }

        void model::processMesh(aiMesh* amesh, const aiScene* scene)
        {
            auto res_mgr = ace::runtime::manager::instance();
            std::vector<float> vertices;
            std::vector<unsigned int> indices;

            for(unsigned int i = 0; i < amesh->mNumVertices; i++)
            {
                // positions
                vertices.push_back(amesh->mVertices[i].x);
                vertices.push_back(amesh->mVertices[i].y);
                vertices.push_back(amesh->mVertices[i].z);
                // normals
                vertices.push_back(amesh->mNormals[i].x);
                vertices.push_back(amesh->mNormals[i].y);
                vertices.push_back(amesh->mNormals[i].z);
                // texture coordinates
                if(amesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {
                    vertices.push_back(amesh->mTextureCoords[0][i].x); 
                    vertices.push_back(amesh->mTextureCoords[0][i].y);
                }
                else
                {
                    vertices.push_back(0.0f);
                    vertices.push_back(0.0f);
                }
            }

            for(unsigned int i = 0; i < amesh->mNumFaces; i++)
            {
                aiFace face = amesh->mFaces[i];
                for(unsigned int j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }

            aiMaterial* mat = scene->mMaterials[amesh->mMaterialIndex];
            material* matl = res_mgr->genMaterial();
            auto submesh = new mesh(t_scn, matl->id, std::to_string(t_children.size()), vertices, indices);

            unsigned int tex_count = 0;

            std::unordered_map<aiTextureType, char*> tex_types = {
                { aiTextureType_DIFFUSE, "texture_diffuse" },
                { aiTextureType_SPECULAR, "texture_specular"},
                { aiTextureType_HEIGHT, "texture_height"},
                { aiTextureType_AMBIENT, "texture_ambient"}
            };

            for(auto tex_type : tex_types)
            {
                for(unsigned int i = 0; i < mat->GetTextureCount(tex_type.first); i++)
                {
                    aiString str;
                    mat->GetTexture(tex_type.first, i, &str);
                    auto tex = res_mgr->genTex((t_dir + "/" + str.C_Str()).c_str());
                    matl->tex[tex_count] = tex->id();

                    auto name = std::string();
                    name.append(tex_type.second);
                    name.append(std::to_string(i));
                    submesh->setUniform(name, ace::render::m1i, ace::render::float2array(tex_count));
                    tex_count++;
                }
            }
            
            addChild(submesh);
        }
    }
}