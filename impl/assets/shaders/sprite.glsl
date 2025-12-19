#type vertex
#version 450 core
layout (location=0) in vec2 vPos;
layout (location=1) in vec4 vColor;
layout (location=2) in vec2 vUv;
layout (location=3) in int vTexId;
layout (location=4) in int vEntityId;

out vec4 fColor;
out vec2 fUv;
out flat int fTexId;

uniform int uZIndex;
uniform mat4 uView;
uniform mat4 uProjection;

void main(void)
{
	fTexId = vTexId;
	fUv = vUv;
	fColor = vColor;
	gl_Position = uProjection * uView * vec4(vPos, uZIndex, 1);
}

#type fragment
#version 450 core
in vec4 fColor;
in vec2 fUv;
in flat int fTexId;

#define NUM_OF_TEXTURES 8

uniform sampler2D uTextures[NUM_OF_TEXTURES];

out vec4 color;

void main(void)
{
	color = fColor;

	if (0 <= fTexId) {
		color *= texture(uTextures[fTexId], fUv);
	}
}
