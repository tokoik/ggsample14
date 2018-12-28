// ウィンドウ関連の処理
#include "GgApplication.h"

// 標準ライブラリ
#include <cmath>
#include <memory>

// 光源
const GgSimpleShader::Light lightProperty =
{
  { 0.2f, 0.2f, 0.2f, 1.0f },
  { 1.0f, 1.0f, 1.0f, 1.0f },
  { 1.0f, 1.0f, 1.0f, 1.0f },
  { 3.0f, 4.0f, 5.0f, 1.0f }
};

// オブジェクトの材質
const GgSimpleShader::Material objectMaterial =
{
  { 0.7f, 0.5f, 0.5f, 1.0f },
  { 0.7f, 0.5f, 0.5f, 1.0f },
  { 0.2f, 0.2f, 0.2f, 1.0f },
  50.0f
};

//
// アプリケーションの実行
//
void GgApplication::run()
{
  // ウィンドウを作成する
  Window window("ggsample14");

  // 背景色を指定する
  glClearColor(0.2f, 0.4f, 0.6f, 0.0f);

  // 隠面消去を有効にする
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // 図形用のプログラムオブジェクト
  GgSimpleShader simple("ggsample14.vert", "ggsample14.frag");

  // 点群のシェーダ
  GgPointShader point("ggsample14point.vert", "ggsample14point.frag", "ggsample14point.geom");

  // OBJ ファイルの読み込み
  const std::unique_ptr<const GgElements> object(ggElementsObj("bunny.obj", true));

  // 物体の材質
  const GgSimpleShader::MaterialBuffer material(objectMaterial);

  // 点
  const std::unique_ptr<const GgPoints> sphere(ggPointsSphere(200, 2.0f, 0.0f, 0.0f, 0.0f));

  // ビュー変換行列を mv に求める
  const GgMatrix mv(ggLookat(0.0f, 0.0f, 7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));

  // 光源の材質
  const GgSimpleShader::LightBuffer light(lightProperty);

  // ウィンドウが開いている間くり返し描画する
  while (window)
  {
    // 投影変換行列
    const GgMatrix mp(ggPerspective(0.5f, window.getAspect(), 1.0f, 15.0f));

    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 図形の描画
    simple.use(mp, mv * window.getTrackball(GLFW_MOUSE_BUTTON_2), light);
    material.select();
    object->draw();

    // 点群の描画
    point.use(mp, mv * window.getTrackball(GLFW_MOUSE_BUTTON_1));
    sphere->draw();

    // カラーバッファを入れ替えてイベントを取り出す
    window.swapBuffers();
  }
}
