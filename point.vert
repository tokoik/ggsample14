#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// 頂点属性
layout (location = 0) in vec4 pv;                   // ローカル座標系の頂点位置

void main(void)
{
  gl_Position = pv;
}
