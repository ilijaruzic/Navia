#type vertex
#version 330 core

layout(location = 0) in vec3 v_inPosition;

uniform mat4 v_uViewProjection;
uniform mat4 v_uTransform;

void main() {
    gl_Position = v_uViewProjection * v_uTransform * vec4(v_inPosition, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 f_outColor;

uniform vec4 f_uColor;

void main() {
    f_outColor = f_uColor;
}