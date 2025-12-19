#type vertex
#version 450 core
layout (location=0) in vec2 vPos;
layout (location=1) in vec3 vColor;

out vec3 fColor;

uniform int uZIndex;
uniform bool uIsWorldSpace;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
	fColor = vColor;

	if (uIsWorldSpace != false) {
		gl_Position = uProjection * uView * vec4(vPos, uZIndex, 1.0);
	} else {
		gl_Position = uProjection * vec4(vPos, uZIndex, 1.0);
	}
}

#type fragment
#version 450 core
in vec3 fColor;

out vec4 color;

void main()
{
	color = vec4(fColor, 1.0);
}
