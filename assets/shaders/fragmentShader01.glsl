#version 450 core
out vec4 fragColor;
uniform sampler2D samplerA;
in vec2 uv;
void main()
{
    vec4 color = texture(samplerA, uv);
    fragColor = color;
}
