#type vertex
#version 450 core
layout (location=0) in vec3 vPos;
layout (location=1) in vec3 vColor;

out vec3 fColor;

uniform mat4 uView;
uniform mat4 uProjection;

void main(void)
{
	fColor = vColor;
	gl_Position = uProjection * uView * vec4(vPos, 1.0);
}

#type fragment
#version 450 
in vec3 fColor;

out vec4 color;

void main(void)
{
	color = vec4(fColor, 1.0);
}
