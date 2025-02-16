#version 450 core
out vec4 fragColor;
uniform sampler2D samplerA;
uniform sampler2D samplerB;
uniform sampler2D samplerC;
in vec2 uv;
void main()
{
    vec4 grassColor = texture(samplerA, uv);
    vec4 landColor = texture(samplerB, uv);
    vec4 noiseColor = texture(samplerC, uv);

    float weigh = noiseColor.r;
    fragColor = grassColor * weigh + landColor * (1.0 - weigh);
}
