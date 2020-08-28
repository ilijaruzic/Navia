#type vertex
#version 330 core

layout(location = 0) in vec3 v_inPosition;
layout(location = 1) in vec4 v_inColor;
layout(location = 2) in vec2 v_inTextureCoords;
layout(location = 3) in float v_inTextureIndex;
layout(location = 4) in float v_inTilingFactor;

uniform mat4 v_uViewProjection;

out vec4 v_outColor;
out vec2 v_outTextureCoords;
out float v_outTextureIndex;
out float v_outTilingFactor;

void main() {
    v_outColor = v_inColor;
    v_outTextureCoords = v_inTextureCoords;
    v_outTextureIndex = v_inTextureIndex;
    v_outTilingFactor = v_inTilingFactor;
    gl_Position = v_uViewProjection * vec4(v_inPosition, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 f_outColor;

uniform sampler2D f_uTextures[32];

in vec4 v_outColor;
in vec2 v_outTextureCoords;
in float v_outTextureIndex;
in float v_outTilingFactor;

void main() {
    f_outColor = texture(f_uTextures[int(v_outTextureIndex)], v_outTextureCoords * v_outTilingFactor) * v_outColor;
}