#type vertex
#version 450 core
layout (location=0) in vec2 vPos;
layout (location=1) in vec4 vColor;

out vec4 fColor;

uniform int uZIndex;
uniform mat4 uProjection;

void main()
{
    fColor = vColor;
    gl_Position = uProjection * vec4(vPos, uZIndex, 1)
}

#type fragment
#version 450 core
in vec4 fColor;

out vec4 color;

void main()
{
    color = fColor;
}
