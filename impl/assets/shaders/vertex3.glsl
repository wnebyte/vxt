#type vertex
#version 450 core
layout (location=0) in vec3 vPos;
layout (location=1) in vec3 vColor; 
layout (location=2) in vec2 vUv; 
layout (location=3) in int vTexId;

out vec3 fColor;
out vec2 fUv;
out flat int fTexId;

uniform mat4 uView;
uniform mat4 uProjection;

void main(void)
{
    fColor = vColor;
    fUv = vUv;
    fTexId = vTexId;
    gl_Position = uProjection * uview * vec4(vPos, 1.0);
}

#type fragment
#version 450 core
in vec3 fColor;
in vec2 fUv;
in flat in fTexId;

#define NUM_OF_TEXTURES 8

uniform sampler2D uTextures[NUM_OF_TEXTURES];

out vec4 color;

void main(void)
{
    color = vec4(fColor, 1.0)

    if (0 <= fTexId) {
        color *= texture(uTextures[fTexId], fUv)
    }
}
