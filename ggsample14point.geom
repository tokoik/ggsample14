#version 410 core

// 三角形の頂点位置
const vec4 position[] = vec4[](
  vec4(-0.1, -0.0866, 0.0, 0.0),
  vec4( 0.1, -0.0866, 0.0, 0.0),
  vec4( 0.0,  0.0866, 0.0, 0.0)
  );

// 三角形の頂点色
const vec4 color[] = vec4[](
  vec4(1.0, 0.0, 0.0, 1.0),
  vec4(0.0, 1.0, 0.0, 1.0),
  vec4(0.0, 0.0, 1.0, 1.0)
  );

// 光源
layout (std140) uniform Light
{
  vec4 lamb;                                          // 環境光成分
  vec4 ldiff;                                         // 拡散反射光成分
  vec4 lspec;                                         // 鏡面反射光成分
  vec4 lpos;                                          // 位置
};

// 材質
layout (std140) uniform Material
{
  vec4 kamb;                                          // 環境光の反射係数
  vec4 kdiff;                                         // 拡散反射係数
  vec4 kspec;                                         // 鏡面反射係数
  float kshi;                                         // 輝き係数
};

// 変換行列
uniform mat4 mv;                                      // モデルビュー変換行列
uniform mat4 mp;                                      // 投影変換行列
uniform mat4 mn;                                      // 法線ベクトルの変換行列

// ジオメトリシェーダに入力される図形要素
layout(points) in;

// ジオメトリシェーダから出力する図形要素と最大頂点数
layout(triangle_strip, max_vertices = 12) out;

// ラスタライザに送る頂点属性
out vec4 iamb;                                        // 環境光の反射光強度
out vec4 idiff;                                       // 拡散反射光強度
out vec4 ispec;                                       // 鏡面反射光強度

void main()
{
  // 点の位置をモデルビュー変換する
  vec4 p = mv * gl_in[0].gl_Position;

  for (int i = 0; i < 3; ++i)
  {
    // モデルビュー変換後の点の位置を中心として頂点位置を求め投影変換する
    gl_Position = mp * (p + position[i]);

    iamb = vec4(0.0);
    idiff = color[i];
    ispec = vec4(0.0);

    EmitVertex();
  }

  EndPrimitive();
}
