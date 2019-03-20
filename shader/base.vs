#version 330 core
layout (location = 0) in vec3 aPos; // 直接给世界坐标

#ifdef NORMAL
layout (location = 1) in vec3 aNormal;
out vec3 Normal;
#endif

#ifdef TEXTURE
layout (location = 2) in vec2 aTexCoords;
out vec2 TexCoords;
#endif

out vec3 FragPos;

#ifdef NORMAL
uniform mat4 model;
#endif

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    FragPos = aPos;

    #ifdef NORMAL
    Normal = mat3(transpose(inverse(model))) * aNormal;
    #endif

    #ifdef TEXTURE
    TexCoords = aTexCoords;
    #endif
}