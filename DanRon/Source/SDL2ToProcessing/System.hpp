//
//  System.hpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/09/26.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#ifndef System_hpp
#define System_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include <map>
#include <math.h>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#define PI 3.141592653589793

typedef SDL_Surface *PImage;
typedef TTF_Font *PFont;

enum aPosition { LEFT, CENTER, RIGHT };
enum vPosition { TOP, CENTER2, BOTTOM };

using namespace std;

extern int frameCount;

//作りかけ
class String {
  string text;

public:
  explicit String(string text) { this->text = text; }

  static int dst(unsigned char x) {
    if (x >= 0x00 && x <= 0x7f) {
      return 1;
    } else if (x >= 0xc2 && x <= 0xdf) {
      return 2;
    } else if (x >= 0xe0 && x <= 0xef) {
      return 3;
    } else if (x >= 0xf0 && x <= 0xf7) {
      return 4;
    } else if (x >= 0xf8 && x <= 0xfb) {
      return 5;
    } else if (x >= 0xfc && x <= 0xfd) {
      return 6;
    } else
      return -1;
  }

  operator string const() { return text; }

  size_t length() {
    int ri = 0;
    for (int k = 0; k < text.length();) {
      unsigned char x = text[k];
      if (x == '\0') {
        break;
      }
      k += dst(x);
      ri++;
    }
    return ri;
  }

  String &operator=(const string &e) {
    this->text = e;
    return *this;
  }

  String &operator+=(const string &e) {
    this->text += e;
    return *this;
  }

  string operator[](int i) {
    int ri = 0;
    for (int k = 0; k < text.length();) {
      unsigned char x = text[k];
      if (ri == i) {
        return text.substr(k, dst(x));
      }
      k += dst(x);
      ri++;
    }
    return this->text;
  }
};

class systemVar {
public:
  static int R, G, B, Al;

  static TTF_Font *nowFont;
  static int tSize;

  static bool endTh;

  static int FPS;

  static aPosition nowA;
  static vPosition nowV;

  static aPosition nowAT;
  static vPosition nowVT;

  static SDL_Window *systemWindow;
  static SDL_Renderer *systemRender;
  static SDL_Event *systemEv;

  static double angle;
};

extern thread countFrame;

void initLPSystem(SDL_Renderer *nRender, SDL_Window *nWindow, SDL_Event *nEv);
void deleteLPSystem();

void fill(int nR, int nG, int nB, int nAl);

void fill(int C, int nAl);

void fill(int C);

void rect(int x, int y, int width, int height);
void rect(int x, int y, int width, int height, int rd);

void line(int x1, int y1, int x2, int y2);

void text(string tx, int x, int y);

void image(PImage img, int x, int y);
void image(PImage img, int x, int y, int width, int height);

void textFont(PFont fon);

void imageMode(aPosition a);
void imageMode(aPosition a, vPosition v);

void textAlign(aPosition a);
void textAlign(aPosition a, vPosition v);

double radians(int deg);

void textSize(int size);

void rotate(double angle);

void setBold();
void unSetBold();

SDL_Rect textRect(string text);

PFont loadFont(string path);
PImage loadImage(string path);

void frameRate(int fps);

void dd(int x, int y, int r);

#endif /* System_hpp */
