//
// ゲームグラフィックス特論宿題アプリケーション
//
#include "GgApp.h"

// プロジェクト名
#ifndef PROJECT_NAME
#  define PROJECT_NAME "ggsample14"
#endif

// 光源
const GgSimpleShader::Light lightProperty
{
  { 0.2f, 0.2f, 0.2f, 1.0f },
  { 1.0f, 1.0f, 1.0f, 1.0f },
  { 1.0f, 1.0f, 1.0f, 1.0f },
  { 3.0f, 4.0f, 5.0f, 1.0f }
};

// オブジェクトの材質
const GgSimpleShader::Material objectMaterial
{
  { 0.7f, 0.5f, 0.5f, 1.0f },
  { 0.7f, 0.5f, 0.5f, 1.0f },
  { 0.2f, 0.2f, 0.2f, 1.0f },
  50.0f
};

//
// アプリケーション本体
//
int GgApp::main(int argc, const char* const* argv)
{
  // ウィンドウを作成する (この行は変更しないでください)
  Window window{ argc > 1 ? argv[1] : PROJECT_NAME };

  // 背景色を指定する
  glClearColor(0.2f, 0.4f, 0.6f, 0.0f);

  // 隠面消去を有効にする
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // 図形用のプログラムオブジェクト
  GgSimpleShader simple{ PROJECT_NAME ".vert", PROJECT_NAME ".frag" };

  // 点群のシェーダ
  GgSimpleShader point{ PROJECT_NAME "point.vert", PROJECT_NAME "point.frag", PROJECT_NAME "point.geom" };

  // OBJ ファイルの読み込み
  const std::unique_ptr<const GgElements> object{ ggElementsObj("bunny.obj", true) };

  // 物体の材質
  const GgSimpleShader::MaterialBuffer material{ objectMaterial };

  // 点
  const std::unique_ptr<const GgPoints> sphere{ ggPointsSphere(200, 2.0f, 0.0f, 0.0f, 0.0f) };

  // ビュー変換行列を mv に求める
  const auto mv{ ggLookat(0.0f, 0.0f, 7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f) };

  // 光源の材質
  const GgSimpleShader::LightBuffer light{ lightProperty };

  // ウィンドウが開いている間くり返し描画する
  while (window)
  {
    // 投影変換行列
    const auto mp{ ggPerspective(0.5f, window.getAspect(), 1.0f, 15.0f) };

    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 図形の描画
    simple.use(mp, mv * window.getRotationMatrix(GLFW_MOUSE_BUTTON_2), light);
    material.select();
    object->draw();

    // 点群の描画
    point.use(mp, mv * window.getRotationMatrix(GLFW_MOUSE_BUTTON_1));
    sphere->draw();

    // カラーバッファを入れ替えてイベントを取り出す
    window.swapBuffers();
  }

  return 0;
}
