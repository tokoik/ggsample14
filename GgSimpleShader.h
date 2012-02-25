#ifndef __GG_SIMPLESHADER_H__
#define __GG_SIMPLESHADER_H__

/*
** 単純な陰影付け
*/
#include "GgPointShader.h"

namespace gg
{
  class GgSimpleShader
    : public GgPointShader
  {
    // 光源
    struct
    {
      GLfloat pos[4];   // 光源位置
      GLfloat amb[4];   // 光源強度の環境光成分
      GLfloat diff[4];  // 光源強度の拡散反射光成分
      GLfloat spec[4];  // 光源強度の鏡面反射光成分
    } l;

    // 材質
    struct
    {
      GLfloat amb[4];   // 環境光の反射係数
      GLfloat diff[4];  // 拡散反射係数
      GLfloat spec[4];  // 鏡面反射係数
      GLfloat shi;      // 輝き係数
    } k;

    // 変換
    struct
    {
      GLfloat g[16];    // モデルビュー変換の法線変換行列
      void loadNormalMatrix(const GgMatrix &m) { m.get(g); }
    } m;

    // 場所
    struct
    {
      GLint nv;         // 法線の attribute 変数の場所
      GLint pl;         // 光源位置の uniform 変数の場所
      GLint lamb;       // 光源強度の環境光成分の uniform 変数の場所
      GLint ldiff;      // 光源強度の拡散反射光成分の uniform 変数の場所
      GLint lspec;      // 光源強度の鏡面反射光成分の uniform 変数の場所
      GLint kamb;       // 環境光の反射係数の uniform 変数の場所
      GLint kdiff;      // 拡散反射係数の uniform 変数の場所
      GLint kspec;      // 鏡面反射係数の uniform 変数の場所
      GLint kshi;       // 輝き係数の uniform 変数の場所
      GLint mg;         // モデルビュー変換の法線変換行列の uniform 変数の場所
    } loc;

  public:

    // デストラクタ
    virtual ~GgSimpleShader(void) {}

    // コンストラクタ
    GgSimpleShader(void) {}
    GgSimpleShader(const char *vert, const char *frag = 0,
      const char *geom = 0, GLint nvarying = 0, const char **varyings = 0);
    GgSimpleShader(const GgSimpleShader &o)
      : GgPointShader(o), l(o.l), k(o.k), m(o.m), loc(o.loc) {}

    // 代入
    GgSimpleShader &operator=(const GgSimpleShader &o)
    {
      if (&o != this)
      {
        GgPointShader::operator=(o);
        l = o.l;
        k = o.k;
        m = o.m;
        loc = o.loc;
      }
      return *this;
    }

    // シェーダの使用開始
    virtual void use(void) const;

    // シェーダの使用終了
    virtual void unuse(void) const;

    // 光源の位置
    void setLightPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
    {
      l.pos[0] = x;
      l.pos[1] = y;
      l.pos[2] = z;
      l.pos[3] = w;
    }
    void setLightPosition(const GLfloat *pos)
    {
      setLightPosition(pos[0], pos[1], pos[2], pos[3]);
    }

    // 光源強度の環境光成分
    void setLightAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
    {
      l.amb[0] = r;
      l.amb[1] = g;
      l.amb[2] = b;
      l.amb[3] = a;
    }
    void setLightAmbient(const GLfloat *amb)
    {
      setLightAmbient(amb[0], amb[1], amb[2], amb[3]);
    }

    // 光源強度の拡散反射光成分
    void setLightDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
    {
      l.diff[0] = r;
      l.diff[1] = g;
      l.diff[2] = b;
      l.diff[3] = a;
    }
    void setLightDiffuse(const GLfloat *diff)
    {
      setLightDiffuse(diff[0], diff[1], diff[2], diff[3]);
    }

    // 光源強度の鏡面反射光成分
    void setLightSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
    {
      l.spec[0] = r;
      l.spec[1] = g;
      l.spec[2] = b;
      l.spec[3] = a;
    }
    void setLightSpecular(const GLfloat *spec)
    {
      setLightSpecular(spec[0], spec[1], spec[2], spec[3]);
    }

    // 環境光に対する反射係数
    void setMaterialAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
    {
      k.amb[0] = r;
      k.amb[1] = g;
      k.amb[2] = b;
      k.amb[3] = a;
    }
    void setMaterialAmbient(const GLfloat *amb)
    {
      setMaterialAmbient(amb[0], amb[1], amb[2], amb[3]);
    }

    // 拡散反射係数
    void setMaterialDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
    {
      k.diff[0] = r;
      k.diff[1] = g;
      k.diff[2] = b;
      k.diff[3] = a;
    }
    void setMaterialDiffuse(const GLfloat *diff)
    {
      setMaterialDiffuse(diff[0], diff[1], diff[2], diff[3]);
    }

    // 鏡面反射係数
    void setMaterialSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f)
    {
      k.spec[0] = r;
      k.spec[1] = g;
      k.spec[2] = b;
      k.spec[3] = a;
    }
    void setMaterialSpecular(const GLfloat *spec)
    {
      setMaterialSpecular(spec[0], spec[1], spec[2], spec[3]);
    }

    // 輝き係数
    void setMaterialShininess(GLfloat shi)
    {
      k.shi = shi;
    }

    // 変換行列の設定
    virtual void loadMatrix(const GgMatrix &mp, const GgMatrix &mw);
    virtual void loadMatrix(const GLfloat *mp, const GLfloat *mw);
  };

}

#endif
