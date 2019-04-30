#include "interaction/log.h"
#include "texture.h"

namespace ace
{
    namespace render
    {
        texture::texture(const char* filename)
        {
            glGenTextures(1, &t_id);
            int width, height, nrChannels;
            unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
            if(data)
            {
                glBindTexture(GL_TEXTURE_2D, t_id);
                if(nrChannels == 3)
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                else
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                LOG_DEFAULT("Failed to load texture: %s\n", filename);
            }
            stbi_image_free(data);
        }

        void texture::bind(int idx)
        {
            glActiveTexture(idx);
            glBindTexture(GL_TEXTURE_2D, t_id);
        }
        
        texture::~texture()
        {
            glDeleteTextures(1, &t_id);
        }
    }
}