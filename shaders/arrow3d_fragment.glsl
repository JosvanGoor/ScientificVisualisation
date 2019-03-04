#version 330

in vec3 g_normal;
in vec3 g_position;

out vec4 frag_color;

const float ambient = 0.1;
const vec3 light_pos = vec3(0.0, 0.0, 50.0);
const vec3 light_col = vec3(1.0, 1.0, 1.0);

void main()
{
    vec3 norm;
    if (gl_FrontFacing)
        norm = normalize(g_normal);
    else    
        norm = -normalize(g_normal);
    vec3 light_dir = normalize(light_pos - g_position);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_col;

    vec3 result = (ambient + diffuse);

    frag_color = vec4(result, 1.0);
}