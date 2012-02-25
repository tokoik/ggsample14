// ウィンドウ関連の処理
#include "Window.h"

// 標準ライブラリ
#include <cmath>
#include <memory>

// 光源
const GgSimpleShader::Light light =
{
  { 0.2f, 0.2f, 0.2f, 1.0f },
  { 1.0f, 1.0f, 1.0f, 1.0f },
  { 1.0f, 1.0f, 1.0f, 1.0f },
  { 3.0f, 4.0f, 5.0f, 1.0f }
};

// オブジェクトの材質
const GgSimpleShader::Material material =
{
  { 0.7f, 0.5f, 0.5f, 1.0f },
  { 0.7f, 0.5f, 0.5f, 1.0f },
  { 0.2f, 0.2f, 0.2f, 1.0f },
  50.0f
};

//
// メインプログラム
//
int main(int argc, const char *argv[])
{
  // ウィンドウを作成する
  Window window("ggsample14");

  // 背景色を指定する
  glClearColor(0.2f, 0.4f, 0.6f, 0.0f);

  // 隠面消去を有効にする
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // 図形用のプログラムオブジェクト
  GgSimpleShader simple("simple.vert", "simple.frag");

  // 点群のシェーダ
  GgPointShader point("point.vert", "point.frag", "point.geom");

  // OBJ ファイルの読み込み
  const std::unique_ptr<const GgElements> object(ggElementsObj("bunny.obj"));

  // 点
  const std::unique_ptr<const GgPoints> sphere(ggPointsSphere(100, 1.0f, 0.0f, 0.0f, 0.0f));

  // ビュー変換行列を mv に求める
  const GgMatrix mv(ggLookat(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));

  // ウィンドウが開いている間くり返し描画する
  while (window.shouldClose() == GL_FALSE)
  {
    // 投影変換行列
    const GgMatrix mp(ggPerspective(0.5f, window.getAspect(), 1.0f, 15.0f));

    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 図形の描画
    simple.use();
    simple.loadLightMaterial(light);
    simple.loadLightPosition(light.position);
    simple.loadMaterial(material);
    simple.loadMatrix(mp, mv);
    object->draw();

    // 点群の描画
    point.use();
    point.loadMatrix(mp, mv * window.getLeftTrackball());
    sphere->draw();

    // カラーバッファを入れ替えてイベントを取り出す
    window.swapBuffers();
  }

  return 0;
}
