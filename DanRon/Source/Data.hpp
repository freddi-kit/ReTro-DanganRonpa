//
//  Data.hpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/09/26.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#ifndef Data_hpp
#define Data_hpp

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "Nichijo.hpp"
#include "System.hpp"
#include "Trial.hpp"
#include "sceneSys.hpp"

extern bool Pause; //ポーズ画面フラグ
extern bool Skip;  //メッセージ飛ばしフラグ

extern PImage titleImage; //タイトル画像
extern PFont pixelFont;   //システムフォント

extern PImage Rb; //リボルバー用画像

void initData();   //データ初期化用
void deleteData(); //データ解放用

extern bool mouseLeft;    //左クリックの状態
extern int mouseLeftTime; //左クリックの押されてる時間
extern bool keyUP;        //上キー
extern int keyUPTime;
extern bool keyDOWN; //下キー
extern int keyDOWNTime;

extern int mouseX;
extern int mouseY;

extern bool isTitle;
extern bool debugEnd;

//画面の大きさ
const int winWidth = 320;
const int winHeight = 200;

class CStory; //ストーリークラス
class CTrial; //学級裁判クラス
class CHuman; //キャラクラス

class CProlog;
class COpening;

class CNichijo; //日常編

extern vector<CHuman *> Chara;   //キャラ用変数
extern vector<CStory *> Chapter; //ストーリ用変数


//キャラクラス
class CHuman {
private:
  PImage normal; //キャラ立ち絵（通常）
  String *missSerifu;
  String *name;
  String *kata;

public:
  CHuman(string path, string _name, string _kata); //コンストラクタ
  PImage normalImage(); //立ち絵（通常）を返す
  String *getName();
  String *getMissSerifu();
};

//ストーリークラス
class CStory {
private:
  int prologCounter;
  CTrial *trial; //学級裁判用
  CProlog *prolog;
  COpening *opening;
  CNichijo *nichijo;
  int nextStory;

public:
  CStory(String storyNum);   //コンストラクタ
  int storyGo(int nowStory); //ストーリーを流す
  vector<String> trialStory; //学級裁判の流れを格納
  bool isNowStory;
  bool isTrial;
  bool isProlog;
  bool isOpening;
  bool isNichijo;

  static int storySize;
};

#endif /* Data_hpp */
