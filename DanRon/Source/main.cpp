//
//  main.cpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/09/26.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string.h>
#include <unistd.h>


#include "Data.hpp"
#include "Effect.hpp"

//メイン関数
int main(int argc, char *argv[]) {
    /*
    char AppPath[1024];
    char AppPathw[1024];
    char *char_work;
    int strlen;
    
    if ( argc > 0 ) // change dir to .app/Contents/MacOS
    {
        strcpy( AppPath, argv[0] );
        char_work = strrchr( AppPath, '/' );
        strlen = char_work - AppPath;
        strncpy( AppPathw, AppPath, strlen );
        AppPathw[strlen] = '\0';
        chdir( AppPathw );
    }*/
    
  debugEnd = false;
  // SDL初期化関係
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  // Window生成
  SDL_Window *window =
      SDL_CreateWindow("ダンガンロンパC", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, winWidth, winHeight, 0);
  //レンダー生成
  SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);

  //イベント設定
  SDL_Event ev;

  // Like-Processingシステム初期化
  initLPSystem(render, window, &ev);

  //データ関係初期化
  initData();

  //レンダー描画モード
  SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
  SDL_ShowCursor(0);

  while (!debugEnd) {

    //描画を消す
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

    //レンダーをきれいにする
    SDL_RenderClear(render);
    // SDL_ShowCursor(SDL_DISABLE);

    while (SDL_PollEvent(&ev)) {

      switch (ev.type) {
      case SDL_MOUSEMOTION: {
        mouseX = ev.motion.x;
        mouseY = ev.motion.y;
      } break;
      case SDL_MOUSEBUTTONDOWN: {
        switch (ev.button.button) {
        case SDL_BUTTON_LEFT: {
          mouseLeft = true; //左クリックの状態
          mouseLeftTime = 0;
        } break;
        default:
          break;
        }
      } break;
      case SDL_MOUSEBUTTONUP: {
        switch (ev.button.button) {
        case SDL_BUTTON_LEFT: {
          mouseLeft = false; //左クリックの状態
          mouseLeftTime = 0;
        } break;
        default:
          break;
        }
        break;
      case SDL_KEYDOWN: {
        switch (ev.key.keysym.sym) {
        case SDLK_UP: {
          keyUP = true; //上キー
        } break;
        case SDLK_DOWN: {
          keyDOWN = true; //下キー
        } break;
        }

      } break;
      case SDL_KEYUP: {
        switch (ev.key.keysym.sym) {
        case SDLK_UP: {
          keyUP = false; //上キー
        } break;
        case SDLK_DOWN: {
          keyDOWN = false; //下キー
        } break;
        }

      } break;
      }
      }
      //終了時
      if (ev.type == SDL_QUIT) {
          debugEnd = true;
        std::cout << "end" << endl;
        //データ解放
        deleteData();
        // Like-Processingシステム解放
        deleteLPSystem();
        // SDL関係
        TTF_Quit();

        return 0;
      }
    }

    //以下本ゲーム描画

    gameMain();

    //画面をレトロ風に設定
    likeRetro();

    //レンダーを反映
    SDL_RenderPresent(render);
    mouseLeftTime++;
    // FPS調整
    SDL_Delay((1000 / systemVar::FPS));
  }
  std::cout << "end" << endl;
  //データ解放
  deleteData();
  // Like-Processingシステム解放
  deleteLPSystem();
  // SDL関係
  TTF_Quit();

  return 0;
}
