//
//  Nichijo.hpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/10/02.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#ifndef Nichijo_hpp
#define Nichijo_hpp

#include "Data.hpp"
#include "System.hpp"

using namespace std;

class CProlog {
private:
  //メッセージボックス描画用
  vector<String> mesBoxGo;

  void nextMes();

  int serifuPos;
  int mesPos;
  int mesSpeed;
  int charaDrawNum;
  vector<String> serifu;
  String name = move(String(""));
  ;

  int charaPointNum;
  int linePos;
  bool Skip;
  bool isSceneChange;
  bool isShowChara;

public:
  CProlog(String storyXmlPath);
  void goProlog(bool *isProlog);
};
class CNichijo {
private:
  //メッセージボックス描画用
  vector<String> mesBoxGo;

  void nextMes();

  int serifuPos;
  int mesPos;
  int mesSpeed;
  int charaDrawNum;
  int itDrawNum;
  int bgDrawNum;
  vector<String> serifu;
  String name = move(String(""));
  

  int charaPointNum;
  int linePos;
  bool Skip;
  bool isSceneChange;
  bool isShowChara;
  bool isShowBG;
  bool isShowItem;
  vector<PImage> item;
  vector<PImage> backGround;

public:
  CNichijo(string storyXmlPath);
  void nichijoGo(bool *isNichijo);
};

class COpening {
private:
  PImage monokuma;
  int counterOp;
  vector<string> goS;

public:
  COpening();
  void openingGo(bool *isOpening, int nowStory);
};

#endif /* Nichijo_hpp */
