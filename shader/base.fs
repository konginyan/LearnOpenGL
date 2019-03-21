#version 330 core
out vec4 FragColor;
in vec3 FragPos; // 着色点世界坐标

#ifdef MATERIAL
    struct Material {
        #ifdef LIGHTMAP
            sampler2D diffuse;
            sampler2D specular;
        #else
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        #endif

        float shininess;
    };
    uniform Material material;
#endif

#ifdef LIGHT
    struct Light {
        #ifdef L_DIRECTION
            vec3 direction;
        else
            vec3 position;
        #endif

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
    uniform Light light;
    uniform vec3 viewPos; // 相机世界坐标
#endif

#ifdef COLOR
uniform vec4 objColor;
#endif

#ifdef NORMAL
in vec3 Normal; // 法线向量基于世界坐标
#endif

#ifdef TEXTURE
uniform sampler2D texture1;
in vec2 TexCoords;
#endif

void main()
{
    #ifdef LIGHT
        vec3 norm = normalize(Normal);

        #ifdef L_DIRECTION
            vec3 lightDir = normalize(light.position - FragPos); // 平行光方向
        #else
            vec3 lightDir = normalize(-light.direction); // 点到点光方向
        #endif // L_DIRECTION

        vec3 viewDir = normalize(viewPos - FragPos); // 观察方向
        vec3 reflectDir = reflect(-lightDir, norm);  // 反射方向

        float diff = max(dot(norm, lightDir), 0.0);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        #ifdef TEXTURE
            vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
            vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
            vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
        #else
            vec3 ambient = light.ambient * Material.ambient;
            vec3 diffuse = light.diffuse * diff * Material.diffuse;
            vec3 specular = light.specular * spec * Material.specular;
        #endif // TEXTURE

        vec3 result = ambient + diffuse + specular + objColor;
        FragColor = vec4(result, 1.0);
    #else // LIGHT

        #ifdef COLOR
            FragColor = objColor;
        #else // COLOR
            #ifdef TEXTURE
                FragColor = vec4(texture(texture1, TexCoords).rgba);
            #else // TEXTURE
                FragColor = vec4(1.0, 1.0, 1.0, 1.0);
            #endif
        #endif
    #endif

}