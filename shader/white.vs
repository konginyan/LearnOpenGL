#version 330 core
layout (location = 0) in vec3 aPos; // 直接给世界坐标

void main()
{
    gl_Position = vec4(aPos, 1.0);
}