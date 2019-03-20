#include "texture.h"

namespace ace
{
    namespace render
    {
        texture::texture(char* filename)
        {
            glGenTextures(1, &t_id);
            int width, height, nrChannels;
            unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
            if(data)
            {
                glBindTexture(GL_TEXTURE_2D, t_id);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture: " << filename << std::endl;
            }
            stbi_image_free(data);
        }

        texture::texture(const texture &tex)
        {
            t_id = tex.t_id;
        }
        
        texture::~texture()
        {
        }
    }
}