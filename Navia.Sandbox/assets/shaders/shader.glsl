#type vertex
#version 330 core

layout(location = 0) in vec3 v_inPosition;
layout(location = 1) in vec2 v_inTextureCoords;

uniform mat4 v_uViewProjection;
uniform mat4 v_uTransform;

out vec2 v_outTextureCoords;

void main() {
    v_outTextureCoords = v_inTextureCoords;
    gl_Position = v_uViewProjection * v_uTransform * vec4(v_inPosition, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 f_outColor;

uniform vec4 f_uColor;
uniform sampler2D f_uTexture;

in vec2 v_outTextureCoords;

void main() {
    f_outColor = texture(f_uTexture, v_outTextureCoords * 10.0) * f_uColor;
}