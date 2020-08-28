#type vertex
#version 330 core

layout(location = 0) in vec3 v_inPosition;
layout(location = 1) in vec4 v_inColor;
layout(location = 2) in vec2 v_inTextureCoords;

uniform mat4 v_uViewProjection;

out vec4 v_outColor;
out vec2 v_outTextureCoords;

void main() {
    v_outColor = v_inColor;
    v_outTextureCoords = v_inTextureCoords;
    gl_Position = v_uViewProjection * vec4(v_inPosition, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 f_outColor;

uniform vec4 f_uColor;
uniform float f_uTilingFactor;
uniform sampler2D f_uTexture;

in vec4 v_outColor;
in vec2 v_outTextureCoords;

void main() {
    // f_outColor = texture(f_uTexture, v_outTextureCoords * f_uTilingFactor) * f_uColor;
    f_outColor = v_outColor;
}