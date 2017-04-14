/*
 * matrix2x2.h
 * 2次元正方行列型(C++版)
 *
 */

#ifndef MATRIX2X2_H_
#define MATRIX2X2_H_

#include "vector2d.h"
#include <iostream>
#include <vector>

/* 2次元ベクトル型 */
class matrix2x2 {
  /*
   *  以下のように明示的に private, public を指定した場合は struct matrix2x2
   * と宣言しても同じである
   */

private:
  double xval, yval; /* x 座標値, y 座標値 */
  std::vector<std::vector<double>> val;

public:
  /* デフォルトコンストラクタ */
  matrix2x2() {
    val.clear();
    for (int i = 0; i < 2; i++) {
      std::vector<double> v;
      for (int j = 0; j < 2; j++) {
        v.push_back(0);
      }
      val.push_back(v);
    }
    std::cout << "default con " << *this << std::endl;
  }

  /* 初期化引数つきコンストラクタ */
  matrix2x2(double x1, double y1, double x2, double y2) {
    val.clear();
    for (int i = 0; i < 2; i++) {
      std::vector<double> v;
      for (int j = 0; j < 2; j++) {
        if (j == 0) {
          v.push_back(0);
        } else {
        }
      }
      val.push_back(v);
    }
    std::cout << "set con " << *this << std::endl;
  }

  matrix2x2(const matrix2x2 &cop) {
    xval = cop.x();
    yval = cop.y();
    std::cout << "copy con " << *this << std::endl;
  }

  double x() const { return xval; }
  double y() const { return yval; }

  double x(double x) { return xval = x; }
  double y(double y) { return yval = y; }

  /* x, y を与えて自身 = (x, y) にする */
  void set(double x, double y);

  /* x, y を与えて自身 = (v.x, v.y) にする */
  void set(matrix2x2 v);

  /* 自身と v を加えたベクトルを返す */
  matrix2x2 add(const matrix2x2 &v);
  matrix2x2 sub(const matrix2x2 &v);

  /* 文字列から浮動小数点数を 2 つ読み，それぞれを成分の値としてセットする */
  char *readFrom(char *);

  /* ストリームから浮動小数点数を 2 つ読み，それぞれを成分の値としてセットする
   */
  std::istream &readFrom(std::istream &);

  /* ベクトル v の値をファイルストリームに出力する */
  std::ostream &printOn(std::ostream &) const;

  /* ストリーム出力演算子 */
  friend std::ostream &operator<<(std::ostream &os, const matrix2x2 &v) {
    return v.printOn(os);
  }
};

#endif /* MATRIX2X2_H_ */
