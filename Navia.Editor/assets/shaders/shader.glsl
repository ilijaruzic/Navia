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
    vec4 textureColor = v_outColor;
    switch(int(v_outTextureIndex)) {
        case  0: textureColor *= texture(f_uTextures[0],  v_outTextureCoords * v_outTilingFactor); break;
        case  1: textureColor *= texture(f_uTextures[1],  v_outTextureCoords * v_outTilingFactor); break;
        case  2: textureColor *= texture(f_uTextures[2],  v_outTextureCoords * v_outTilingFactor); break;
        case  3: textureColor *= texture(f_uTextures[3],  v_outTextureCoords * v_outTilingFactor); break;
        case  4: textureColor *= texture(f_uTextures[4],  v_outTextureCoords * v_outTilingFactor); break;
        case  5: textureColor *= texture(f_uTextures[5],  v_outTextureCoords * v_outTilingFactor); break;
        case  6: textureColor *= texture(f_uTextures[6],  v_outTextureCoords * v_outTilingFactor); break;
        case  7: textureColor *= texture(f_uTextures[7],  v_outTextureCoords * v_outTilingFactor); break;
        case  8: textureColor *= texture(f_uTextures[8],  v_outTextureCoords * v_outTilingFactor); break;
        case  9: textureColor *= texture(f_uTextures[9],  v_outTextureCoords * v_outTilingFactor); break;
        case 10: textureColor *= texture(f_uTextures[10], v_outTextureCoords * v_outTilingFactor); break;
        case 11: textureColor *= texture(f_uTextures[11], v_outTextureCoords * v_outTilingFactor); break;
        case 12: textureColor *= texture(f_uTextures[12], v_outTextureCoords * v_outTilingFactor); break;
        case 13: textureColor *= texture(f_uTextures[13], v_outTextureCoords * v_outTilingFactor); break;
        case 14: textureColor *= texture(f_uTextures[14], v_outTextureCoords * v_outTilingFactor); break;
        case 15: textureColor *= texture(f_uTextures[15], v_outTextureCoords * v_outTilingFactor); break;
        case 16: textureColor *= texture(f_uTextures[16], v_outTextureCoords * v_outTilingFactor); break;
        case 17: textureColor *= texture(f_uTextures[17], v_outTextureCoords * v_outTilingFactor); break;
        case 18: textureColor *= texture(f_uTextures[18], v_outTextureCoords * v_outTilingFactor); break;
        case 19: textureColor *= texture(f_uTextures[19], v_outTextureCoords * v_outTilingFactor); break;
        case 20: textureColor *= texture(f_uTextures[20], v_outTextureCoords * v_outTilingFactor); break;
        case 21: textureColor *= texture(f_uTextures[21], v_outTextureCoords * v_outTilingFactor); break;
        case 22: textureColor *= texture(f_uTextures[22], v_outTextureCoords * v_outTilingFactor); break;
        case 23: textureColor *= texture(f_uTextures[23], v_outTextureCoords * v_outTilingFactor); break;
        case 24: textureColor *= texture(f_uTextures[24], v_outTextureCoords * v_outTilingFactor); break;
        case 25: textureColor *= texture(f_uTextures[25], v_outTextureCoords * v_outTilingFactor); break;
        case 26: textureColor *= texture(f_uTextures[26], v_outTextureCoords * v_outTilingFactor); break;
        case 27: textureColor *= texture(f_uTextures[27], v_outTextureCoords * v_outTilingFactor); break;
        case 28: textureColor *= texture(f_uTextures[28], v_outTextureCoords * v_outTilingFactor); break;
        case 29: textureColor *= texture(f_uTextures[29], v_outTextureCoords * v_outTilingFactor); break;
        case 30: textureColor *= texture(f_uTextures[30], v_outTextureCoords * v_outTilingFactor); break;
        case 31: textureColor *= texture(f_uTextures[31], v_outTextureCoords * v_outTilingFactor); break;
    }
    f_outColor = textureColor;
}