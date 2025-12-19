#type vertex
#version 450 core
layout (location=0) in vec3 vPos;
layout (location=1) in vec2 vUv;

out vec2 fUv;

void main(void)
{
    fUv = vUv;
    gl_Position = vec4(vPos, 1.0);
}

#type fragment
#version 450 core
in vec2 fUv;

layout (location=0) out vec4 frag;

uniform sampler2D screen;

void main(void)
{
    frag = vec4(texture(screen, fUv).rgb, 1.0);
}
