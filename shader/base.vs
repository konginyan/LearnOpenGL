#version 330 core
layout (location = 0) in vec3 aPos;

#ifdef NORMAL
layout (location = 1) in vec3 aNormal;
out vec3 Normal;
#endif

#ifdef TEXTURE
layout (location = 2) in vec2 aTexCoords;
out vec2 TexCoords;
#endif

out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));

    #ifdef NORMAL
    Normal = mat3(transpose(inverse(model))) * aNormal;
    #endif

    #ifdef TEXTURE
    TexCoords = aTexCoords;
    #endif
}