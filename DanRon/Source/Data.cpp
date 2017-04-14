//
//  Data.cpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/09/26.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#include "Data.hpp"

bool Pause; //ポーズ画面用フラグ
bool Skip;  //メッセージ飛ばし用フラグ

PFont pixelFont;   //システムフォント
PImage titleImage; //タイトル画像

PImage Rb; //リボルバー用画像

vector<CHuman *> Chara;   //キャラ用変数
vector<CStory *> Chapter; //ストーリー用変数

bool mouseLeft;    //左クリックの状態
int mouseLeftTime; //左クリックの押されてる時間
bool keyUP;        //上キー
int keyUPTime;
bool keyDOWN; //下キー
int keyDOWNTime;

int mouseX;
int mouseY;

bool isTitle;
bool debugEnd;


int CStory::storySize;

//初期化関数
void initData() {
  //システムフォント読み込み
  pixelFont = loadFont("Resource/PixelMplus10-Regular.ttf");

  //タイトル画像読み込み
  titleImage = loadImage("Resource/Title.png");

  //リボルバー画像読み込み
  Rb = loadImage("Resource/Rb.png");

  //描画用フォントをシステムフォントに設定
  textFont(pixelFont);

  //ポーズ・スキップフラグはオフ
  Pause = false;
  Skip = false;

  isTitle = true;

  //デバック（キャラ画像代入）
  Chara.push_back(new CHuman("Resource/human.png", "test1", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test2", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test3", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test4", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test5", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test6", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test7", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test8", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test9", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test10", "???"));
  Chara.push_back(new CHuman("Resource/human.png", "test11", "???"));

  //デバック（ストーリー）
  for (int i = 0; i < 1; i++) {
    Chapter.push_back(new CStory(move(String("StoryData/Story01.xml"))));
  }
  CStory::storySize = (int)Chapter.size();

  //画像などの回転を０度に
  rotate(0);

  mouseLeft = false; //左クリックの状態
  mouseLeftTime = 0; //左クリックの押されてる時間
  keyUP = false;     //上キー
  keyUPTime = 0;
  keyDOWN = false; //下キー
  keyDOWNTime = 0;
  mouseX = 0;
  mouseY = 0;
}

void deleteData() {}

CStory::CStory(String storyXmlPath) {
  using namespace boost::property_tree;
  //裁判の読み込み
  trial = new CTrial();
  //デバッグ（裁判読み込み）

  ptree pt;
  read_xml(storyXmlPath, pt);
  for (const ptree::value_type &child : pt.get_child("root.TrialSerifu")) {
    string str = boost::lexical_cast<string>(child.second.data());
    trialStory.push_back(move(String(move(str))));
  }

  int i = 0, k = 0;
  for (const ptree::value_type &child : pt.get_child("root.TrialNonStop")) {
    nonStopBase *read;
    for (const ptree::value_type &child : child.second.get_child("get")) {

      int charaNum = child.second.get<int>("charaNum");
      bool isWeak = child.second.get<bool>("isWeak");
      string serifu = child.second.get<string>("serifu");
      int x = child.second.get<int>("x");
      int y = child.second.get<int>("y");
      double speedX = child.second.get<double>("speedX");
      double speedY = child.second.get<double>("speedY");
      int stayCount = child.second.get<int>("stayCount");

      if (isWeak) {
        int weakPointPos = child.second.get<int>("weakPointPos");
        int weakPointPosEnd = child.second.get<int>("weakPointPosEnd");
        bool isCorrect = child.second.get<bool>("isCorrect");
        int cKotoDamaNum = child.second.get<int>("cKotoDamaNum");
        read = new nonStopA(serifu, charaNum, x, y, speedX, speedY, stayCount,
                            weakPointPos, weakPointPosEnd, isCorrect,
                            cKotoDamaNum);
        bool isSub = child.second.get<bool>("isSub");
        if (i) {
          if (!isSub) {
            trial->nonStopSerifu[k]->setNext(read);
          } else {
            int goTiming = child.second.get<int>("goTiming");
            trial->nonStopSerifu[k]->setSub(read, goTiming);
          }
        }
      } else {
        read = new nonStopA(serifu, charaNum, x, y, speedX, speedY, stayCount);
        if (i) {
          bool isSub = child.second.get<bool>("isSub");
          if (!isSub) {

            trial->nonStopSerifu[k]->setNext(read);
          } else {
            int goTiming = child.second.get<int>("goTiming");
            trial->nonStopSerifu[k]->setSub(read, goTiming);
          }
        }
      }
      if (!i)
        trial->nonStopSerifu.push_back(move(read));

      i++;
    }
    k++;
    i = 0;
  }
  for (const ptree::value_type &child : pt.get_child("root.TrialKotodama")) {
    vector<string> kotoDamaRead;
    for (const ptree::value_type &child : child.second.get_child("get")) {
      kotoDamaRead.push_back(move(child.second.get<string>("str")));
    }
    trial->nonStopKotodama.push_back(move(kotoDamaRead));
  }
  cout << trial->nonStopSerifu.size();
  prologCounter = 0;
  isProlog = true;
  isOpening = false;
  isNichijo = false;
  isNowStory = false;
  isTrial = false;
  nichijo = new CNichijo(storyXmlPath);
  prolog = new CProlog(storyXmlPath);
  opening = new COpening();
}

int CStory::storyGo(int nowStory) {
  //学級裁判
  nextStory = nowStory + 1;

  if (isProlog) {
    if (prologCounter > 100) {
      prolog->goProlog(&isProlog);
      if (!isProlog) {
        isOpening = true;
      }
    } else {
      fill(10, 255);
      rect(0, 0, winWidth, winHeight);
      prologCounter++;
    }
  } else if (isNichijo) {
    nichijo->nichijoGo(&isNichijo);
    if (!isNichijo) {
      isTrial = true;
    }
  } else if (isOpening) {
    opening->openingGo(&isOpening, nowStory);
    if (!isOpening) {
      isNichijo = true;
    }
  } else if (isTrial) {
    trial->Trial(this);
  }
  return 1;
}

CHuman::CHuman(string path, string _name, string _kata) {
  //画像読み込み（システム変更予定）
  normal = loadImage(path);
  this->name = new String(_name);
  this->kata = new String(_kata);
  this->missSerifu = new String("You missed");
}

String *CHuman::getName() { return name; }

String *CHuman::getMissSerifu() { return missSerifu; }

PImage CHuman::normalImage() {
  //立ち絵（通常）を返す
  return normal;
}
