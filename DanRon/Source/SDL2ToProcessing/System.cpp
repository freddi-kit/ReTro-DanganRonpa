//
//  System.cpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/09/26.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#include "System.hpp"
#include <memory>

constexpr int PRE_SET_TXT_SIZE = 24.0;

SDL_Window *systemVar::systemWindow;
SDL_Renderer *systemVar::systemRender;
SDL_Event *systemVar::systemEv;



int systemVar::R;
int systemVar::G;
int systemVar::B;
int systemVar::Al;

int frameCount;

aPosition systemVar::nowAT;
vPosition systemVar::nowVT;

aPosition systemVar::nowA;
vPosition systemVar::nowV;

double systemVar::angle;

int systemVar::FPS;

bool systemVar::endTh;

thread countFrame;

int systemVar::tSize;

TTF_Font *systemVar::nowFont;

vector<PImage> cashPImage(0);
vector<PFont> cashPFont(0);

void initLPSystem(SDL_Renderer *nRender, SDL_Window *nWindow, SDL_Event *nEv) {
  fill(0, 150, 0, 255);

  frameCount = 0;
  frameRate(60);

  systemVar::systemWindow = nWindow;

  systemVar::systemRender = nRender;

  textAlign(CENTER, CENTER2);
  imageMode(CENTER, CENTER2);

  systemVar::endTh = false;
  systemVar::angle = 0;
  systemVar::systemEv = nEv;

  countFrame = thread([] {
    while (!systemVar::endTh) {
      this_thread::sleep_for(
          std::chrono::microseconds(1000000 / systemVar::FPS));
      frameCount++;
    }
  });
}

void deleteLPSystem() {
  for (auto x : cashPImage) {
    SDL_FreeSurface(x);
  }
  for (auto x : cashPFont) {
    TTF_CloseFont(x);
  }

  systemVar::endTh = true;
  countFrame.join();
}

void fill(int nR, int nG, int nB, int nAl) {
  systemVar::R = nR;
  systemVar::G = nG;
  systemVar::B = nB;
  systemVar::Al = nAl;
  SDL_SetRenderDrawColor(systemVar::systemRender, systemVar::R, systemVar::G,
                         systemVar::B, systemVar::Al);
}

void fill(int C, int nAl) { fill(C, C, C, nAl); }

void fill(int C) {
  systemVar::R = C;
  systemVar::G = C;
  systemVar::B = C;
  SDL_SetRenderDrawColor(systemVar::systemRender, systemVar::R, systemVar::G,
                         systemVar::B, systemVar::Al);
}

void line(int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(systemVar::systemRender, x1, y1, x2, y2);
}

void rect(int x, int y, int width, int height) {
  SDL_Rect rc;
  rc.x = x;
  rc.y = y;
  rc.w = width;
  rc.h = height;
  SDL_RenderFillRect(systemVar::systemRender, &rc);
}

void rect(int x, int y, int width, int height, int rd) {
  if (rd) {
    rd = (rd > height / 2) ? height / 2 : rd;
    rd = (rd > width / 2) ? width / 2 : rd;
    rect(x + rd, y, width - rd * 2, height);

    //こっから先の処理が気に食わない
    map<int, int> mp;
    for (double rad = 0; rad < 90; rad++) {
      mp[rd - rd * cos(radians(rad))] = rd - rd * sin(radians(rad));
      // SDL_RenderDrawPoint(systemVar::systemRender, x + rd - rd *
      // cos(radians(rad)),y + rd - rd * sin(radians(rad)));
    }

    for (int iy = 0; iy < rd; iy++) {
      line(x + iy, y + mp[iy], x + iy, y + height - 1 - mp[iy]);

      line(x + width - rd + iy, y + mp[rd - iy - 1], x + width - rd + iy,
           y + height - 1 - mp[rd - iy - 1]);
    }
    mp.clear();
  } else
    rect(x, y, width, height);
}

PFont loadFont(string path) {
  auto rf = TTF_OpenFont(path.c_str(), PRE_SET_TXT_SIZE);
  cashPFont.push_back(rf);
  return rf;
}

PImage loadImage(string path) {
  auto rw = SDL_RWFromFile(path.c_str(), "r");
  auto imageR = IMG_LoadPNG_RW(rw);
  cashPImage.push_back(imageR);
  return imageR;
}

void textFont(PFont fon) { systemVar::nowFont = fon; }

void imageMode(aPosition a) { systemVar::nowA = a; }
void imageMode(aPosition a, vPosition v) {
  imageMode(a);
  systemVar::nowV = v;
}

void textAlign(aPosition a) { systemVar::nowAT = a; }
void textAlign(aPosition a, vPosition v) {
  textAlign(a);
  systemVar::nowVT = v;
}

void textSize(int size) { systemVar::tSize = size; }

void image(PImage img, int x, int y) {
  SDL_Rect src, dst;

  auto imgTxr = SDL_CreateTextureFromSurface(systemVar::systemRender, img);

  src.x = 0;
  src.y = 0;
  src.w = img->w;
  src.h = img->h;

  dst.x = x + ((systemVar::nowA == CENTER)
                   ? -(img->w) / 2
                   : ((systemVar::nowA == RIGHT) ? -(img->w) : 0));

  dst.y = y + ((systemVar::nowV == CENTER2)
                   ? -(img->h) / 2
                   : ((systemVar::nowV == BOTTOM) ? -(img->h) : 0));

  dst.w = img->w;
  dst.h = img->h;

  SDL_RenderCopyEx(systemVar::systemRender, imgTxr, &src, &dst,
                   systemVar::angle, NULL, SDL_FLIP_NONE);
  SDL_DestroyTexture(imgTxr);
}

void image(PImage img, int x, int y, int width, int height) {
  SDL_Rect src, dst;

  auto imgTxr = SDL_CreateTextureFromSurface(systemVar::systemRender, img);

  src.x = 0;
  src.y = 0;
  src.w = img->w;
  src.h = img->h;

  dst.x = x + ((systemVar::nowA == CENTER)
                   ? -(width) / 2
                   : ((systemVar::nowA == RIGHT) ? -(width) : 0));

  dst.y = y + ((systemVar::nowV == CENTER2)
                   ? -(height) / 2
                   : ((systemVar::nowV == BOTTOM) ? -(height) : 0));

  dst.w = width;
  dst.h = height;

  SDL_RenderCopyEx(systemVar::systemRender, imgTxr, &src, &dst,
                   systemVar::angle, NULL, SDL_FLIP_NONE);
  SDL_DestroyTexture(imgTxr);
}

double radians(int deg) { return deg * PI / 180.0; }

void text(string tx, int x, int y) {
  if (tx != "") {
    SDL_Color cl;
    SDL_Rect src, dst;

    cl.r = systemVar::R;
    cl.g = systemVar::G;
    cl.b = systemVar::B;
    cl.a = systemVar::Al;

    auto txSuf = TTF_RenderUTF8_Blended(systemVar::nowFont, tx.c_str(), cl);
    SDL_SetSurfaceBlendMode(txSuf, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(txSuf, systemVar::Al);
    auto txTxr = SDL_CreateTextureFromSurface(systemVar::systemRender, txSuf);

    src.x = 0;
    src.y = 0;
    src.w = txSuf->w;
    src.h = txSuf->h;

    dst.x = x + ((systemVar::nowAT == CENTER)
                     ? -(txSuf->w * ((double)systemVar::tSize /
                                     (double)PRE_SET_TXT_SIZE)) /
                           (double)2
                     : ((systemVar::nowAT == RIGHT)
                            ? -(txSuf->w * ((double)systemVar::tSize /
                                            (double)PRE_SET_TXT_SIZE))
                            : 0));

    dst.y = y + ((systemVar::nowVT == CENTER2)
                     ? -(txSuf->h * ((double)systemVar::tSize /
                                     (double)PRE_SET_TXT_SIZE)) /
                           (double)2
                     : ((systemVar::nowVT == BOTTOM)
                            ? -(txSuf->h * ((double)systemVar::tSize /
                                            (double)PRE_SET_TXT_SIZE))
                            : 0));

    dst.w = txSuf->w * ((double)systemVar::tSize / (double)PRE_SET_TXT_SIZE);
    dst.h = txSuf->h * ((double)systemVar::tSize / (double)PRE_SET_TXT_SIZE);

    SDL_FreeSurface(txSuf);

    SDL_RenderCopyEx(systemVar::systemRender, txTxr, &src, &dst,
                     systemVar::angle, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(txTxr);
  }
}

void setBold() { TTF_SetFontStyle(systemVar::nowFont, TTF_STYLE_BOLD); }

void unSetBold() { TTF_SetFontStyle(systemVar::nowFont, TTF_STYLE_NORMAL); }

void rotate(double angle) { systemVar::angle = angle; }

void frameRate(int fps) { systemVar::FPS = fps; }

SDL_Rect textRect(string text) {
  SDL_Rect dst;
  dst.w = 0;
  dst.h = 0;
  if (text != "") {
    SDL_Color cl;

    cl.r = systemVar::R;
    cl.g = systemVar::G;
    cl.b = systemVar::B;
    cl.a = systemVar::Al;

    auto txSuf = TTF_RenderUTF8_Blended(systemVar::nowFont, text.c_str(), cl);

    dst.w = txSuf->w * ((double)systemVar::tSize / (double)PRE_SET_TXT_SIZE);
    dst.h = txSuf->h * ((double)systemVar::tSize / (double)PRE_SET_TXT_SIZE);

    SDL_FreeSurface(txSuf);
    return dst;

  } else
    return dst;
}

