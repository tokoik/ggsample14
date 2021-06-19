#version 410 core

// 頂点属性
layout (location = 0) in vec4 pv;                   // ローカル座標系の頂点位置

void main(void)
{
  gl_Position = pv;
}
