/*
 * matrix2x2.cpp
 * 2次元ベクトル型(C++版)
 *
 *
 */

#include <cstdlib>
#include <iostream>

#include "matrix2x2.h"

/* x, y を与えて自身を (x, y) にする */
void matrix2x2::set(double x, double y) {
  xval = x;
  yval = y;
}

/* v を与えて自身を (v.x, v.y) にする */
void matrix2x2::set(matrix2x2 v) {
  xval = v.xval;
  yval = v.yval;
}

/* 自身と v を加えたベクトルを返す */
matrix2x2 matrix2x2::add(const matrix2x2 &v) {
  matrix2x2 r(xval + v.xval, yval + v.yval);
  return r;
}

matrix2x2 matrix2x2::sub(const matrix2x2 &v) {
  matrix2x2 r(xval - v.xval, yval + v.yval);
  return r;
}

/* 文字列から浮動小数点数を 2 つ読み，それぞれを成分の値としてセットする */
char *matrix2x2::readFrom(char *str) {
  xval = strtod(str, &str);
  if (*str == ',')
    str++;
  yval = strtod(str, &str);

  return str;
}

/* ストリームから浮動小数点数を 2 つ読み，それぞれを成分の値としてセットする */
std::istream &matrix2x2::readFrom(std::istream &is) {
  is >> xval;
  is >> yval;
  return is;
}

/* ベクトル v の値をファイルストリームに出力する */
std::ostream &matrix2x2::printOn(std::ostream &os) const {
  os << "(" << xval << ", " << yval << ")";
  return os;
}
