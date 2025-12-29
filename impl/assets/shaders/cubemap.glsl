#type vertex
#version 450 core
layout (location=0) in vec3 vPos;

out vec3 fUv;

uniform mat4 uView;
uniform mat4 uProjection;

void main(void)
{
    fUv = vPos;
    gl_Position = uProjection * uView * vec4(vPos, 1.0);
}

#type fragment
#version 450 core
in vec3 fUv;

layout (location=0) out vec4 color;

uniform samplerCube uCubemap;

void main(void)
{
    color = vec4(texture(uCubemap, fUv).rgb, 1.0);
}
