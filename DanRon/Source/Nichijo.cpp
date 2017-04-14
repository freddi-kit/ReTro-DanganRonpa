//
//  Nichijo.cpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/10/02.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#include "Nichijo.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cctype>

CProlog::CProlog(String storyXmlPath) {
  using namespace boost::property_tree;
  ptree pt;
  read_xml(storyXmlPath, pt);
  for (const ptree::value_type &child : pt.get_child("root.PrologSerifu")) {
    string str = boost::lexical_cast<string>(child.second.data());
    serifu.push_back(move(String(move(str))));
  }
  mesSpeed = 2;
  mesPos = 0;
  serifuPos = 0;
  name = String("");
  charaPointNum = 0;
  linePos = 0;
  Skip = false;
  isSceneChange = false;
  isShowChara = false;
  for (auto i = 0; i < 3; i++) {
    mesBoxGo.push_back(String(""));
  }
}

void CProlog::nextMes() {
  mesPos = 0;
  mesBoxGo.clear();
  for (int i = 0; i < 3; i++) {
    mesBoxGo.push_back(String(""));
  }
  serifuPos++;
  linePos = 0;
  Skip = false;
}

void CProlog::goProlog(bool *isProlog) {
  if (!Pause) {
    if (mesPos < serifu[serifuPos].length()) {
      if ((Skip) ? (frameCount % mesSpeed != 0)
                 : (frameCount % mesSpeed == 0)) {
        if (serifu[serifuPos][mesPos] != "\\") {
          while (serifu[serifuPos][mesPos] == "[") {
            mesPos++;
            if (serifu[serifuPos][mesPos] == "n") {
              mesPos += 2;
              name = "";
              if (isdigit(*serifu[serifuPos][mesPos].c_str())) {
                int charaNum = 0;
                for (; serifu[serifuPos][mesPos] != "]"; mesPos++) {
                  charaNum =
                      charaNum * 10 + atoi(serifu[serifuPos][mesPos].c_str());
                }
                charaPointNum = charaNum;
                name = *Chara[charaPointNum]->getName();
              } else {
                for (; serifu[serifuPos][mesPos] != "]"; mesPos++) {
                  name += (serifu[serifuPos][mesPos].c_str());
                }
              }
            } else if (serifu[serifuPos][mesPos] == "c") {
              mesPos += 2;
              if (isdigit(*serifu[serifuPos][mesPos].c_str())) {
                int charaNum = 0;
                for (; serifu[serifuPos][mesPos] != "]"; mesPos++) {
                  charaNum =
                      charaNum * 10 + atoi(serifu[serifuPos][mesPos].c_str());
                }
                charaDrawNum = charaNum;
                isShowChara = true;
              } else {
                isShowChara = false;
                mesPos++;
              }
            }

            mesPos++;
          }

          mesBoxGo[linePos] += serifu[serifuPos][mesPos];
        } else
          linePos++;
        mesPos++;
      }
      if (mouseLeft) {
        if (!Skip) {
          if (mesPos > 1)
            Skip = true;
        }
      }

    } else {
      if (mouseLeft) {
        nextMes();
        if (serifu.size() == serifuPos) {
          *isProlog = false;
        }
      }
    }
  }

  fill(10, 255);
  rect(0, 0, winWidth, winHeight);

  if (isShowChara)
    image(Chara[charaDrawNum]->normalImage(), winWidth / 2, winHeight / 2);

  fill(255, 255);
  rect(0, winHeight / 2 + 20, winWidth, 100, 5);
  fill(55, 255);
  rect(0, winHeight / 2 + 20, winWidth, 20, 5);
  //メッセージ
  textAlign(LEFT, TOP);
  fill(10, 255);
  textSize(12);
  rotate(0);
  int j = 0;
  if (!isSceneChange) {
    for (auto x : mesBoxGo) {
      text(mesBoxGo[j], 10, (winHeight / 4) * 3 + 2 + j * 14);
      j++;
    }
  }
  //名前
  textAlign(LEFT, TOP);
  textSize(12);
  fill(255);
  text(name, 10, (winHeight / 3) * 2 - 8);
}

COpening::COpening() {

  counterOp = 0;
  monokuma = loadImage("Resource/モノクマ.png");
  goS.push_back("Program by freddi");
  goS.push_back("Test!");
  goS.push_back("");

  goS.push_back("Monoc OS X Version 0.9.9.11");
  goS.push_back("Update for this OS is not Available");
  goS.push_back("Starting System...");
  goS.push_back(".");
  goS.push_back(".");
  goS.push_back("qawsesedrftgyhujikolp;=']");
  goS.push_back(".");
  goS.push_back(".");
  goS.push_back("Hello! World!");
  goS.push_back(".");
  goS.push_back(".");
  goS.push_back(".");
  goS.push_back(".");
  goS.push_back(".");
  goS.push_back(".");
  goS.push_back(".");
  goS.push_back(".");
  goS.push_back(".");
}

void COpening::openingGo(bool *isOpening, int nowStory) {

  if (nowStory == 0) {
    imageMode(CENTER, CENTER2);
    counterOp++;
    if (counterOp < 100) {
      image(monokuma, winWidth / 2, winHeight / 2 - 20);
      fill(10, 255 - ((counterOp * 3 > 255) ? 255 : counterOp * 3));
      rect(0, 0, winWidth, winHeight);

    } else if (counterOp < 300) {
      image(monokuma, winWidth / 2, winHeight / 2 - 20);
      fill(200, 255);
      rect(winWidth / 2 - 100 / 2, winHeight / 2 + 10, 100, 10);

      fill(10, 255);
      double lenPerc = (double)(counterOp - 100) / 100.0;
      if (lenPerc > 1.0)
        lenPerc = 1.0;
      rect(winWidth / 2 - 94 / 2, winHeight / 2 + 10 + 1, 94.0 * lenPerc, 8);

    } else if (counterOp < 500) {
      image(monokuma, winWidth / 2, winHeight / 2 - 20);
      fill(10, 255);
      textAlign(CENTER, CENTER2);
      textSize(12);
      text("MoNoc OS X", winWidth / 2, winHeight / 2 + 15);
    } else if (counterOp < 1000) {
      image(monokuma, winWidth / 2, winHeight / 2 - 20);
      int go = (counterOp - 500) / 20;
      if (go > goS.size())
        go = (int)goS.size();

      int zure = 0;
      if (go * 15 > winHeight) {
        zure = go * 15 - winHeight;
      }
      textAlign(LEFT, TOP);
      textSize(15);

      fill(10, 200);
      rect(0, 0, winWidth, winHeight);

      fill(255, 255);
      for (int i = 0; i < go; i++) {
        text(goS[i], 0, 0 + 15 * i - zure);
      }

    } else if (counterOp < 1200) {
      image(monokuma, winWidth / 2, winHeight / 2 - 20);
      fill(10, 200);
      rect(0, 0, winWidth, winHeight);

      if (counterOp > 1100) {
        fill(255,
             (((counterOp - 1100) * 10 < 255) ? (counterOp - 1100) * 10 : 255));
        rect(0, 0, winWidth, winHeight);
      }

      if (frameCount % 90 > 30)
        image(titleImage, winWidth / 2, winHeight / 2);

    } else if (counterOp < 1700) {
      image(titleImage, winWidth / 2, winHeight / 2);

    } else if (counterOp < 2000) {
      image(titleImage, winWidth / 2, winHeight / 2);
      fill(10,
           (((counterOp - 1700) * 10 < 255) ? (counterOp - 1700) * 10 : 255));
      rect(0, 0, winWidth, winHeight);

    }

    else
      *isOpening = false;
  }
}

//日常編用コンストラクタ
CNichijo::CNichijo(string storyXmlPath) {
  using namespace boost::property_tree;
  ptree pt;
  read_xml(storyXmlPath, pt);
  for (const ptree::value_type &child : pt.get_child("root.NichijoSerifu")) {
    string str = boost::lexical_cast<string>(child.second.data());
    serifu.push_back(move(String(move(str))));
  }
  
  for (const ptree::value_type &child : pt.get_child("root.NiBackground")) {
      string str = boost::lexical_cast<string>(child.second.data());
      backGround.push_back(loadImage(str));
  }
    
  for (const ptree::value_type &child : pt.get_child("root.NiItem")) {
      string str = boost::lexical_cast<string>(child.second.data());
      item.push_back(loadImage(str));
  }
    
  
   
  mesSpeed = 2;
  mesPos = 0;
  serifuPos = 0;
  name = String("");
  charaPointNum = 0;
  linePos = 0;
  Skip = false;
  isSceneChange = false;
  isShowChara = false;
  isShowBG = false;
  isShowItem= false;
  bgDrawNum = 0;
  itDrawNum = 0;
  for (auto i = 0; i < 3; i++) {
    mesBoxGo.push_back(String(""));
  }
}

//日常編用メッセージボックス
void CNichijo::nichijoGo(bool *isNichijo) {
  if (!Pause) {
    if (mesPos < serifu[serifuPos].length()) {
      if ((Skip) ? (frameCount % mesSpeed != 0)
                 : (frameCount % mesSpeed == 0)) {
        if (serifu[serifuPos][mesPos] != "\\") {
          while (serifu[serifuPos][mesPos] == "[") {
            mesPos++;
            if (serifu[serifuPos][mesPos] == "n") {
              mesPos += 2;
              name = "";
              if (isdigit(*serifu[serifuPos][mesPos].c_str())) {
                int charaNum = 0;
                for (; serifu[serifuPos][mesPos] != "]"; mesPos++) {
                  charaNum =
                      charaNum * 10 + atoi(serifu[serifuPos][mesPos].c_str());
                }
                charaPointNum = charaNum;
                name = *Chara[charaPointNum]->getName();
              } else {
                for (; serifu[serifuPos][mesPos] != "]"; mesPos++) {
                  name += (serifu[serifuPos][mesPos].c_str());
                }
              }
            } else if (serifu[serifuPos][mesPos] == "c") {
              mesPos += 2;
              if (isdigit(*serifu[serifuPos][mesPos].c_str())) {
                int charaNum = 0;
                for (; serifu[serifuPos][mesPos] != "]"; mesPos++) {
                  charaNum =
                      charaNum * 10 + atoi(serifu[serifuPos][mesPos].c_str());
                }
                charaDrawNum = charaNum;
                isShowChara = true;
              } else {
                isShowChara = false;
                mesPos++;
              }
            } else if (serifu[serifuPos][mesPos] == "i") {
                mesPos += 2;
                if (isdigit(*serifu[serifuPos][mesPos].c_str())) {
                    int charaNum = 0;
                    for (; serifu[serifuPos][mesPos] != "]"; mesPos++) {
                        charaNum =
                        charaNum * 10 + atoi(serifu[serifuPos][mesPos].c_str());
                    }
                    itDrawNum = charaNum;
                    isShowItem = true;
                } else {
                    isShowItem = false;
                    mesPos++;
                }
            }

            else if (serifu[serifuPos][mesPos] == "b") {
              mesPos += 2;
              if (isdigit(*serifu[serifuPos][mesPos].c_str())) {
                int bgNum = 0;
                for (; serifu[serifuPos][mesPos] != "]"; mesPos++) {
                  bgNum = bgNum * 10 + atoi(serifu[serifuPos][mesPos].c_str());
                }
                bgDrawNum = bgNum;
                isShowBG = true;
              } else {
                isShowBG = false;
                mesPos++;
              }
            }

            mesPos++;
          }

          mesBoxGo[linePos] += serifu[serifuPos][mesPos];
        } else
          linePos++;
        mesPos++;
      }
      if (mouseLeft) {
        if (!Skip) {
          if (mesPos > 1)
            Skip = true;
        }
      }

    } else {
      if (mouseLeft) {
        nextMes();
        if (serifu.size() == serifuPos) {
          *isNichijo = false;
        }
      }
    }
  }

  fill(10, 255);
  rect(0, 0, winWidth, winHeight);

  imageMode(LEFT, TOP);
  if (isShowBG)
    image(backGround[bgDrawNum], 0, 0);

  imageMode(CENTER, CENTER2);
  if (isShowChara)
    image(Chara[charaDrawNum]->normalImage(), winWidth / 2, winHeight / 2);

  imageMode(LEFT, TOP);
  if (isShowItem)
    image(item[itDrawNum], 0, 0);
    
  fill(255, 255);
  rect(0, winHeight / 2 + 20, winWidth, 100, 5);
  fill(55, 255);
  rect(0, winHeight / 2 + 20, winWidth, 20, 5);
  //メッセージ
  textAlign(LEFT, TOP);
  fill(10, 255);
  textSize(12);
  rotate(0);
  int j = 0;
  if (!isSceneChange) {
    for (auto x : mesBoxGo) {
      text(mesBoxGo[j], 10, (winHeight / 4) * 3 + 2 + j * 14);
      j++;
    }
  }
  //名前
  textAlign(LEFT, TOP);
  textSize(12);
  fill(255);
  text(name, 10, (winHeight / 3) * 2 - 8);
}

void CNichijo::nextMes() {
  mesPos = 0;
  mesBoxGo.clear();
  for (int i = 0; i < 3; i++) {
    mesBoxGo.push_back(String(""));
  }
  serifuPos++;
  linePos = 0;
  Skip = false;
}
