#version 330 core

uniform sampler2D tex;

in vec2 fs_texcoord;
in vec3 fs_normal;
in vec3 fs_position;
out vec4 FragColor;


const vec3 light_pos = vec3(0.0, -20.0, 15.0);
const vec3 view_pos = vec3(0.0, -10.0, 5.0);
const float spec_strength = 5;

void main()
{
    vec3 light_dir = normalize(light_pos - fs_position);
    float diff = max(dot(fs_normal, light_dir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    vec3 view_dir = normalize(view_pos - fs_position);
    vec3 reflect_dir = reflect(-light_dir, fs_normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = spec_strength * spec * vec3(1.0, 1.0, 1.0);

    // FragColor = vec4((fs_normal + 1) / 2.0f, 1.0);
    FragColor = vec4(texture(tex, fs_texcoord).xyz * (diffuse + 0.1 + specular), 1.0);
}