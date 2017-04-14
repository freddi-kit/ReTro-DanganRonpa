//
//  Trial.cpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/10/02.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#include "Trial.hpp"

nonStopBase::nonStopBase(string _serifu, int _charaNum)
    : serifu(_serifu), charaNum(_charaNum) {
  isWeak = false;
  next = NULL;
  sub = NULL;
  order = 0;
  goTiming = 0;
  alpha = 0;
  isAlive = false;
  isAttacked = false;
  counterVanish = 0;
  isCorrect = false;
}

nonStopBase::nonStopBase(string _serifu, int _charaNum, int _weakPointPos,
                         int _weakPointPosEnd, bool _isCorrect,
                         int _cKotoDamaNum)
    : serifu(_serifu), charaNum(_charaNum), weakPointPos(_weakPointPos),
      weakPointPosEnd(_weakPointPosEnd), isCorrect(_isCorrect),
      cKotoDamaNum(_cKotoDamaNum) {
  isWeak = true;
  next = NULL;
  sub = NULL;
  order = 0;
  goTiming = 0;
  alpha = 0;
  isAlive = false;
  isAttacked = false;
  counterVanish = 0;
}

nonStopBase::~nonStopBase() { cout << &serifu << endl; }

void nonStopBase::deleteMe(nonStopBase *del) {
  if (del->next == NULL) {
    if (del->sub != NULL) {
      deleteMe(del->sub);
    }
    delete del;

    return;
  }
  deleteMe(del->next);
  if (del->sub != NULL) {
    deleteMe(del->sub);
  }
  delete del;
  return;
}

bool nonStopBase::getIsAttacked() {
  if (this->sub == NULL) {
    return isAttacked;
  } else {
    return isAttacked || sub->getIsAttacked();
  }
}

bool nonStopBase::getIsCorrect() { return isCorrect; }

void nonStopBase::setNext(nonStopBase *_next) {
  nonStopBase *sh = this;
  do {
    if (sh->next == NULL) {
      sh->next = _next;
      sh->next->setOrder(sh->getOrder() + 1);
      return;
    } else
      sh = sh->next;
  } while (1);
}

int nonStopBase::getCharaNum() { return charaNum; }
int nonStopBase::getCKotoDamaNum() { return cKotoDamaNum; }

void nonStopBase::initMoment() {
  alpha = 0;
  isAlive = false;
}

void nonStopBase::setSub(nonStopBase *_sub, int _goTiming) {
  nonStopBase *sh = this;
  do {
    if (sh->next == NULL) {
      do {
        if (sh->sub == NULL) {
          sh->sub = _sub;
          sh->sub->setOrder(0);
          sh->sub->goTiming = _goTiming;
          return;
        } else {
          sh = sh->sub;
        }
      } while (1);
    } else
      sh = sh->next;
  } while (1);
}

void nonStopBase::ronpaAttack() { isAttacked = true; }

int nonStopBase::getSubTiming() { return sub->goTiming; }

bool nonStopBase::getIsAlive() { return isAlive; }

nonStopBase *nonStopBase::sNext() { return this->next; }

nonStopBase *nonStopBase::sSub() { return this->sub; }

int nonStopBase::getOrder() const { return order; }

int nonStopBase::getLength() {
  if (next != NULL) {
    return next->getLength() + 1;
  } else
    return 1;
}

void nonStopBase::setOrder(int _order) { order = _order; }

String nonStopBase::getSerifu() const { return serifu; }

bool nonStopBase::getIsWeak() { return isWeak; }

int nonStopBase::getWeakPointPos() { return weakPointPos; }

int nonStopBase::getWeakPointPosEnd() { return weakPointPosEnd; }

nonStopA::nonStopA(string _serifu, int _chara, double _x, double _y,
                   double _speedX, double _speedY, int _stayCount)
    : nonStopBase(_serifu, _chara), x(_x), y(_y), speedX(_speedX),
      speedY(_speedY), stayCount(_stayCount) {
  moveX = 0;
  moveY = 0;
  counter = 0;
  alpha = 0;
}

nonStopA::nonStopA(string _serifu, int _chara, double _x, double _y,
                   double _speedX, double _speedY, int _stayCount,
                   int _weakPointPos, int _weakPointPosEnd, bool _isCorrect,
                   int _cKotoDamaNum)
    : nonStopBase(_serifu, _chara, _weakPointPos, _weakPointPosEnd, _isCorrect,
                  _cKotoDamaNum),
      x(_x), y(_y), speedX(_speedX), speedY(_speedY), stayCount(_stayCount) {
  moveX = 0;
  moveY = 0;
  counter = 0;
  alpha = 0;
}

void nonStopA::initMoment() {
  moveX = 0;
  moveY = 0;
  counter = 0;
  nonStopBase::initMoment();
  if (this->sub != NULL) {
    this->sub->initMoment();
  }
}

bool nonStopA::isInAttack(int x, int y) {
  if (isWeak) {
    SDL_Rect tempRect = getRectOfWeak();
    /*
    fill(10,255);
    rect(tempRect.x - 10,tempRect.y - 10,tempRect.w + 20,tempRect.h + 20);
    cout << tempRect.x - 10 << endl
         << tempRect.y - 10 << endl
         << tempRect.x + tempRect.w + 10 << endl
         << tempRect.y + tempRect.h + 10 << endl;
    cout << x << endl
         << y << endl;
    fill(255,0,255,255);
    rect(x - 5, y - 5, 10, 10);
    */

    if (x > tempRect.x - 10 && x < tempRect.x + tempRect.w + 10) {

      if (y > tempRect.y - 10 && y < tempRect.y + tempRect.h + 10) {
        return true;
      }
    }
  }
  return false;
}

bool nonStopA::drawText() {
  setBold();
  textSize(15);
  textAlign(LEFT, CENTER2);
  rotate(0);

  if (stayCount - counter > 10 && alpha != 255) {
    alpha += 50;
    if (alpha > 255)
      alpha = 255;
  }

  fill(10, alpha);

  if (getIsWeak()) {
    if (!isAttacked) {
      textAlign(LEFT, CENTER2);
      String tmp("");
      int w = weakPointPos;
      int wE = weakPointPosEnd;
      for (int i = 0; i < w; i++) {
        tmp += this->serifu[i];
      }
      text(tmp, x + moveX, y + moveY);
      SDL_Rect tmpSize = textRect(tmp);
      tmp = "";

      for (int i = w; i <= wE; i++) {
        tmp += this->serifu[i];
      }
      fill(140, 140, 140, alpha);
      text(tmp, x + moveX + tmpSize.w, y + moveY);

      SDL_Rect tmpSizeS = textRect(tmp);
      tmp = "";
      for (int i = wE + 1; i < this->serifu.length(); i++) {
        tmp += this->serifu[i];
      }

      fill(10, alpha);
      text(tmp, x + moveX + tmpSizeS.w + tmpSize.w, y + moveY);
    } else if (isCorrect) {
      counterVanish++;

      if (counterVanish <= 80) {
        textSize(15 + ((counterVanish * 2 < 10) ? counterVanish * 2 : 10));
        textAlign(LEFT, CENTER2);
        String tmp("");
        int w = weakPointPos;
        int wE = weakPointPosEnd;
        for (int i = 0; i < w; i++) {
          tmp += this->serifu[i];
        }
        SDL_Rect tmpSizeA = textRect(tmp);
        tmp = "";
        fill(140, 140, 140, 255);

        if (wE - w + 1 == 2) {
          for (int i = w; i <= wE; i++) {
            tmp = this->serifu[i];
            SDL_Rect tmpRect = textRect(tmp);
            rotate(counterVanish * 20);
            textSize(15 + counterVanish * 2);
            int xx = (i == w) ? -1 : 1;
            text(tmp, x + moveX + tmpSizeA.w + tmpRect.w * (i - w) +
                          xx * counterVanish * 5,
                 y + moveY);
            textSize(15);
            rotate(0);
          }

        } else {
          for (int i = w; i <= wE; i++) {
            tmp = this->serifu[i];
            SDL_Rect tmpRect = textRect(tmp);
            rotate(counterVanish * 20);
            textSize(15 + counterVanish * 2);
            double tmpX = i - w + 1;
            // double tmpY;
            if (tmpX <= (wE - w + 1) / 2) {
              tmpX = -((((wE - w + 1) - tmpX) / (wE - w + 1)));

            } else {
              tmpX = (((tmpX) / (wE - w + 1)));
            }
            text(tmp, x + moveX + tmpSizeA.w + tmpRect.w * (i - w) +
                          tmpX * counterVanish * 5,
                 y + moveY);
            textSize(15);
            rotate(0);
          }
        }
      }
    }
  } else {
    text(this->serifu, x + moveX, y + moveY);
  }
  unSetBold();
  /*----------------------------------------------------------------

     　システム

  ----------------------------------------------------------------*/

  bool subGo = false;
  if (this->sub != NULL) {
    if (this->getSubTiming() < counter) {
      subGo = this->sub->drawText();
    }
  }

  if ((counter > stayCount) && !subGo && !getIsAttacked()) {
    initMoment();
    return false;
  }

  else {
    isAlive = true;
    if (frameCount % 2 == 0) {
      if (!isAttacked) {
        moveX += speedX;
        moveY += speedY;
      }
    }
    counter++;
    if (stayCount - counter < 5 && !getIsAttacked()) {
      isAlive = false;
      alpha -= 75;
      if (alpha < 0)
        alpha = 0;
    }

    return true;
  }
}

SDL_Rect nonStopA::getRectOfWeak() {
  SDL_Rect result;
  string a = "";
  textSize(15);
  String serifu = String(this->serifu);
  for (int i = weakPointPos; i <= weakPointPosEnd; i++) {
    a += serifu[i];
  }
  result = textRect(a);
  a = "";

  for (int i = 0; i < weakPointPos; i++) {
    a += serifu[i];
  }
  result.x = x + moveX + textRect(a).w;
  result.y = y + moveY - textRect(a).h / 2;

  return result;
}

CTrial::CTrial() {
  isNormal = true;
  isSceneChange = false;

  rotaSpeed = 0.75;

  charaPointNum = 0;
  isFocus = false;
  isMonoFocus = false;

  for (auto i = 0; i < 3; i++) {
    mesBoxGo.push_back(String(""));
  }
  for (auto i = 0; i < 3; i++) {
    mesBoxGoNStop.push_back(String(""));
  }

  name = String("");

  Skip = false;

  mesPos = 0;
  mesSpeed = 2;
  mPos = 0;
  linePos = 0;

  tSpeed = 0;

  monoFPS = 0;

  rad = 0;
  counterDraw = 0;

  HP = 1;

  ImgHP = loadImage("Resource/HP.png");
  danganAll = loadImage("Resource/Dangan.png");
  Dangan1 = loadImage("Resource/Dangan1.png");
  Dangan2 = loadImage("Resource/Dangan2.png");
  Dangan3 = loadImage("Resource/Dangan3.png");

  Cursor = loadImage("Resource/cursor.png");

  nowKotoDamaPos = 0;

  serifuPos = 0;

  posNonStop = 0;

  // nonStopW->deleteMe(nonStopW);

  counterSceneChg = 0;

  isSetting = true;

  counterSet = 0;
  initNonStop();
}

CTrial::~CTrial() { nonStopW->deleteMe(nonStopW); }

void CTrial::initNonStop() {

  isNonStop = false;
  counterFirstNStop = 0;
  nowKotoDamaPos = 0;
  alphaNStop = 0;
  isMBoxNonStop = false;
  mesPosNStop = 0;
  linePosNonStop = 0;
  IsTamaChange = false;
  tamaChgWidth = 0;
  isTamaGoing = false;
  isJudged = false;
  counterTama = 0;
  tamaX = 0;
  tamaY = 0;
  tamaToX = 0;
  tamaToY = 0;

  isRonpa = false;
  isNotRonpa = false;
  counterNRonpa = 0;
  counterRonpa = 0;
  missCharaNum = 0;
  missSerifuChange = 0;
  counterMissNStop = 0;
  isEndNStop = false;
  isWeakPAlive = true;

  counterCharaDraw = 0;
  isFocusNStop = false;
  drawCharaNumNowNStop = 0;
  drawCharaNumOldNStop = 0;
  drawCharaXNStop = 0;

  drawCharaMoveX = 0;
}

void CTrial::drawMBox(vector<String> mes) {
    
  if(mes.size() < serifuPos){
      cout << "End " << mes.size() << " " << serifuPos << endl;
      debugEnd = true;
      return;
  }
  if (!isSetting) {
    if (!isSceneChange) {
      if (!Pause) {
        if (mesPos < mes[serifuPos].length()) {
          if ((Skip) ? (frameCount % mesSpeed != 0)
                     : (frameCount % mesSpeed == 0)) {
            if (mes[serifuPos][mesPos] != "\n") {
              while (mes[serifuPos][mesPos] == "[") {
                mesPos++;
                if (mes[serifuPos][mesPos] == "n") {
                  mesPos += 2;
                  name = "";
                  int charaNum = 0;
                  for (; mes[serifuPos][mesPos] != "]"; mesPos++) {
                    charaNum =
                        charaNum * 10 + atoi(mes[serifuPos][mesPos].c_str());
                  }
                  charaPointNum = charaNum;
                  name = *Chara[charaPointNum]->getName();

                } else if (mes[serifuPos][mesPos] == "f") {
                  mesPos += 2;
                  if (mes[serifuPos][mesPos] == "n") {
                    isFocus = false;
                  } else {
                    isFocus = true;
                  }
                  mesPos++;
                } else if (mes[serifuPos][mesPos] == "g") {
                  nonStopW = nonStopSerifu[posNonStop];
                  kotoDama = nonStopKotodama[posNonStop];
                  nowNonStop = nonStopW;
                  isSceneChange = true;
                  mesPos = 0;
                  posNonStop++;
                }

                mesPos++;
              }

              mesBoxGo[linePos] += mes[serifuPos][mesPos];
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
          }
        }
      }
    }
    /*----------------------------------------------------------------

     　描画

     ----------------------------------------------------------------*/

    //描画色を黒に設定
    fill(10, 200);
    //メッセージボックス
    rect(0, winHeight / 2 + 25, winWidth, winHeight);
    //上の部分
    rect(0, 0, winWidth, 20);
    //キャラ顔画像用
    rect(-15, 25, 100, 100, 5);

    // HPゲージ
    rect(200, 22, 150, 14, 5);

    // HPゲージ（HP反映分）
    imageMode(LEFT, TOP);
    image(ImgHP, 202, 24);
    fill(255, 200);
    rect(214, 24, 105 * HP, 10, 5);

    //キャラ顔画像用２
    rect(0, 40, 80, 82, 5);

    //メッセージボックス
    rect(0, (winHeight / 4) * 2.5 + 20, winWidth, winHeight, 15);

    //文字系の装飾
    textSize(12);
    textAlign(LEFT, TOP);
    for (int i = 0; i < 3; i++) {
      text("CASE:01", 20, 26);
    }
    textSize(12);
    textAlign(CENTER, CENTER2);
    for (int i = 0; i < 3; i++) {
      text("CLASSROOM TRIALS", winWidth / 2, 10);
    }

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
    text(name, 10, (winHeight / 3) * 2 - 3);
  } else {
    counterSet++;
    if (counterSet < 100) {
      //メッセージボックス
      if (counterSet > 10) {
        fill(10, 200);
        int height = (counterSet - 10 < 20) ? counterSet - 10 : 20;
        rect(0, 0, winWidth, height);
        fill(255, 200);
        textSize(12);
        textAlign(CENTER, CENTER2);
        for (int i = 0; i < 3; i++) {
          text("CLASSROOM TRIALS", winWidth / 2, -10 + height);
        }
      }
      if (counterSet > 15) {
        int height =
            ((counterSet - 15) * 15 < 100) ? (counterSet - 15) * 15 : 100;
        fill(10, 200);
        //キャラ顔画像用
        rect(-15, 25 + 100 / 2 - height / 2, 100, height, 5);
        height = ((counterSet - 15) * 15 < 82) ? (counterSet - 15) * 15 : 82;
        fill(255, 200);
        rect(0, 40 + 82 / 2 - height / 2, 80, height, 5);
        if ((counterSet - 15) * 15 > 100) {
          textSize(12);
          textAlign(LEFT, TOP);
          for (int i = 0; i < 3; i++) {
            text("CASE:01", 20, 26);
          }
        }
      }
      if (counterSet > 20) {
        int alpha =
            (counterSet - 20 < 10) ? ((counterSet % 2 == 0) ? 0 : 200) : 200;
        fill(10, alpha);
        rect(0, winHeight / 2 + 25, winWidth, winHeight);
        fill(255, alpha);
        rect(0, (winHeight / 4) * 2.5 + 20, winWidth, winHeight, 15);
      }
      if (counterSet > 30) {
        int x = ((counterSet - 30) * 20 < 150) ? (counterSet - 30) * 20 : 150;
        fill(10, 200);
        // HPゲージ
        rect(200 + 150 - x, 22, 150, 14, 5);
        if (counterSet > 50) {
          x = ((counterSet - 50) * 15 < 150) ? (counterSet - 50) * 15 : 150;
          // HPゲージ（HP反映分）
          imageMode(LEFT, TOP);
          image(ImgHP, 202 + 150 - x, 24);
          if (counterSet > 55) {
            x = ((counterSet - 55) * 10 < 105) ? (counterSet - 55) * 10 : 105;
            fill(255, 200);
            rect(214 + 105 - x, 24, 105 * HP, 10, 5);
          }
        }
      }
      if (counterSet > 90) {
        counterSet = 0;
        isSetting = false;
      }
    }
  }
}

void CTrial::sceneChange() {
  if (isNormal && !isNonStop) {
    if (counterSceneChg < 220) {
      int Speed = 5;
      if (counterSceneChg * Speed < winHeight / 2) {
        fill(10, (counterSceneChg * 10 < 255) ? counterSceneChg * 10 : 255);
        rect(0, 0, winWidth, ((counterSceneChg * Speed < winHeight / 2)
                                  ? counterSceneChg * Speed
                                  : winHeight / 2));
        rect(0, winHeight - ((counterSceneChg * Speed < winHeight / 2)
                                 ? counterSceneChg * Speed
                                 : winHeight / 2),
             winWidth, ((counterSceneChg * Speed < winHeight / 2)
                            ? counterSceneChg * Speed
                            : winHeight / 2));
      } else if (counterSceneChg < 180) {
        fill(10, 255);
        rect(0, 0, winWidth, winHeight);
        textAlign(CENTER, CENTER2);
        textSize(12);
        fill(255, 255);
        rect(0, winHeight / 2 - 20, winWidth, 40);
      } else {
        fill(10, 255);
        rect(0, 0, winWidth, winHeight);

        fill(255, 255);
        rect(0,
             winHeight / 2 - 20 +
                 ((counterSceneChg - 180 < 20) ? (counterSceneChg - 180) : 20),
             winWidth,
             40 -
                 ((counterSceneChg - 180 < 20) ? (counterSceneChg - 180) : 20) *
                     2);
        fill(255, (((counterSceneChg - 180) * 10 < 255)
                       ? (counterSceneChg - 180) * 10
                       : 255));
        rect(0, 0, winWidth, winHeight);
      }
      counterSceneChg++;

    } else {
      fill(255, 255);
      rect(0, 0, winWidth, winHeight);
      counterSceneChg = 0;
      isNonStop = true;
      isSceneChange = false;
      isNormal = false;
    }
  } else if (isNonStop) {
    isNormal = true;
    counterSceneChg++;
    if (counterSceneChg < 5) {
      fill(10,
           255 - ((counterSceneChg * 51 < 255) ? counterSceneChg * 51 : 255));
      rect(0, 0, winWidth, winHeight);
    } else {
      isNonStop = false;
      initNonStop();
      counterSceneChg = 0;
      isSceneChange = false;
    }
  }
}

void CTrial::drawChara() {
  imageMode(CENTER, CENTER2);

  if (!isNonStop) {
    if (!Pause) {
      counterDraw = frameCount;
      tSpeed = (isFocus) ? 0 : rotaSpeed;
      monoFPS = (isMonoFocus && isFocus) ? 50 : 0;
      mPos = (720 / Chara.size()) * (0 - charaPointNum);
      charaPointNum = (isMonoFocus) ? 0 : charaPointNum;
      rad = (PI / 360) * (mPos + counterDraw * tSpeed);
    }

    /*
     image(MonokumaImage, winWidth / 2 + 200 * 1.5 * sin(rad),
     winHeight - 30 + monoFPS - (winHeight / 1.5) * cos(rad),
     MonokumaImage.width
     * abs(cos(rad)), MonokumaImage.height);
     */

    int i = 0;
    auto size = Chara.size();
    float cPos = 0;
    for (auto x : Chara) {
      rad = (PI / 360) *
            (cPos + ((!isFocus) ? (counterDraw * tSpeed)
                                : ((size - charaPointNum) * (720 / size))));
      image(x->normalImage(), winWidth / 2 + 200 * sin(rad),
            winHeight - 30 + monoFPS - (winHeight / 3.5) * cos(rad) - 10,
            x->normalImage()->w * abs(cos(rad)), x->normalImage()->h);
      cPos += (720 / size);

      fill(10, 255);
      text(to_string(i), winWidth / 2 + 200 * sin(rad),
           winHeight - 30 + monoFPS - (winHeight / 3.5) * cos(rad));
      i++;
    }

  } else if (isNonStop) {
    counterCharaDraw++;

    int i = 0;
    int xi;

    drawCharaNumNowNStop =
        ((nowNonStop != NULL) ? nowNonStop->getCharaNum() : 0);

    if (!isFocusNStop)
      drawCharaXNStop = counterCharaDraw;

    if (isMBoxNonStop) {
      if (isNotRonpa) {
        drawCharaNumNowNStop = missCharaNum;
        if (missSerifuChange != 0)
          drawCharaNumNowNStop = 0;
      } else
        drawCharaNumNowNStop = 0;
    }

    int focusChara =
        ((int)Chara.size() - drawCharaNumNowNStop) * (winWidth / 2) - 80;

    if (isMBoxNonStop || alphaNStop > 0)
      focusChara += 80;

    if (!isFocusNStop) {
      xi = counterCharaDraw % ((winWidth / 2) * Chara.size());

    } else {
      if (drawCharaXNStop != focusChara) {
        int speedMove = 50;
        drawCharaMoveX = 0;
        if (abs(drawCharaXNStop - focusChara) <= speedMove) {
          drawCharaXNStop = focusChara;
          drawCharaNumOldNStop = drawCharaNumNowNStop;
        } else if (drawCharaXNStop > focusChara) {
          drawCharaXNStop -= speedMove;
        } else if (drawCharaXNStop < focusChara) {
          drawCharaXNStop += speedMove;
        }

      } else {
        if (isMBoxNonStop)
          drawCharaMoveX = 0;
        if (drawCharaMoveX < 100 && !isMBoxNonStop)
          if (counterCharaDraw % 2 == 0)
            drawCharaMoveX++;
      }
      xi = (drawCharaXNStop) % ((winWidth / 2) * Chara.size());
    }

    for (auto x : Chara) {

      xi += (winWidth / 2);
      imageMode(CENTER, CENTER2);
      int xl = xi;

      if (xl - Chara[i]->normalImage()->w / 2 > winWidth) {

        xl = -(winWidth / 2) * ((int)Chara.size() - (i + 1)) +
             drawCharaXNStop % ((winWidth / 2) * Chara.size());
      }

      image(x->normalImage(), xl + drawCharaMoveX, winHeight / 2 + 40 - 30,
            x->normalImage()->w * 1.75, x->normalImage()->h * 1.75);
      fill(10, 255);

      i++;
    }
  }
}

void CTrial::nextMes() {
  mesPos = 0;
  mesBoxGo.clear();
  for (int i = 0; i < 3; i++) {
    mesBoxGo.push_back(String(""));
  }
  serifuPos++;
  linePos = 0;
  Skip = false;
}

void CTrial::Trial(CStory *story) {
  drawChara();
  if (isNormal) {

    drawMBox(story->trialStory);
  } else if (isNonStop) {

    nonStop(
        kotoDama,
        String(
            "あの証拠はあの発言と矛盾していないか？？\n少し気にになるぞ...!"));
  }
  if (isSceneChange)
    sceneChange();
}

void CTrial::nonStop(vector<string> kotoDama, String hint) {
  if (!Pause) {
  }
  if (!isMBoxNonStop) {
    if (alphaNStop > 0 && counterMissNStop == 30) {
      alphaNStop = (alphaNStop < 0) ? 0 : alphaNStop - 100;
      if (alphaNStop < 0) {
        counterMissNStop = 0;
        alphaNStop = 0;
      }
    }

    int firstCCalc = 0;
    for (int i = 0; i < kotoDama.size(); i++) {
      textSize(12);
      firstCCalc += textRect(kotoDama[i]).w;
    }

    if (counterFirstNStop > 250 + firstCCalc + 100) {
      isFocusNStop = true;
      if (nowNonStop != NULL) {
        if (!isWeakPAlive) {
          nowNonStop = nowNonStop->sNext();
        }
      } else if (!isTamaGoing) {
        alphaNStop += 20;
        if (alphaNStop > 255) {
          alphaNStop = 0;
          nowNonStop = nonStopW;
          isMBoxNonStop = true;
        }
      }

      if (!IsTamaChange && !isTamaGoing) {
        if (keyUP) {
          IsTamaChange = true;
          nowKotoDamaPos++;
          if (nowKotoDamaPos >= kotoDama.size()) {
            nowKotoDamaPos = 0;
          }
        }
        if (keyDOWN) {
          IsTamaChange = true;
          nowKotoDamaPos--;
          if (nowKotoDamaPos < 0) {
            nowKotoDamaPos = (int)kotoDama.size() - 1;
          }
        }
        if (mouseLeft && alphaNStop == 0 && !mouseLeftTime) {
          isTamaGoing = true;
          tamaToX = mouseX;
          tamaToY = mouseY;
          tamaX = -40;
          tamaY = mouseY;
        }

      } else if (IsTamaChange && !isTamaGoing) {

      } else if (isTamaGoing) {
        if (!(tamaToX > tamaX)) {
          if (!isJudged) {
            for (auto i = nowNonStop; i != NULL; i = i->sSub()) {
              if (i->getIsAlive()) {
                if (i->getIsWeak()) {
                  if (i->isInAttack(tamaToX, tamaToY)) {
                    if (i->getIsCorrect() &&
                        nowKotoDamaPos == i->getCKotoDamaNum()) {
                      isRonpa = true;
                      i->ronpaAttack();
                    } else {
                      missCharaNum = i->getCharaNum();
                      isNotRonpa = true;
                    }
                    break;
                  }
                }
              }
            }
          }
          isJudged = true;
          if (isJudged) {
            if (isRonpa) {
              counterRonpa++;
              if (isEndNStop) {
                initNonStop();
                isNormal = true;
                isNonStop = true;
                nextMes();
                isSceneChange = true;
                isSetting = true;
                return;
              }
            } else if (isNotRonpa) {
              counterNRonpa++;
              if (isEndNStop) {
                if (nowNonStop != NULL)
                  nowNonStop->initMoment();
                nowNonStop = NULL;
                isTamaGoing = false;
                isEndNStop = false;
              }
            } else {
              if (((counterTama * counterTama) * 2 - 300) > winWidth &&
                  (tamaX > winWidth) && counterTama > 60) {
                counterTama = 0;
                isTamaGoing = false;
                isJudged = false;
              }
            }
          }
        }
      }
    } else {
      counterFirstNStop++;
    }
  } else {
    if (alphaNStop < 255)
      alphaNStop += 20;
    if (counterMissNStop == 0) {
      counterTama = 0;
      if (alphaNStop >= 255) {
        if (isNotRonpa) {
          counterNRonpa = 0;
        }
      }
    } else {
      counterMissNStop++;
      if (counterMissNStop == 30) {
        isMBoxNonStop = false;
      }
    }
  }

  /*----------------------------------------------------------------

   描画

   ----------------------------------------------------------------*/

  if (!isMBoxNonStop) {
    rotate(0);
    int y = (alphaNStop > 0) ? ((alphaNStop < 30) ? alphaNStop : 30) : 0;
    if (alphaNStop > 0 && counterMissNStop == 30) {
      y = 0;
    }
    for (int i = 0; i < 25; i++) {
      fill(100, 255);

      line(0, 170 + ((i < 10) ? i : 10) - y, winWidth, 150 + i - y);

      if (i < 10) {
        fill(100, 255 - ((alphaNStop < 255) ? alphaNStop : 255));
        line(275, 0, 290 + i, winHeight);
        line(150, 0, winWidth, 60 + i);
        line(0, 30 + i, winWidth / 2, 0);
        if (i < 5)
          line(260 + i, 0, winWidth, 100);
      }
    }

    fill(10, 255 - ((alphaNStop < 255) ? alphaNStop : 255));
    rect(200, 22, 150, 14, 5);
    rect(230, 37, 200, 25, 5);

    fill(255, 200 - ((alphaNStop < 200) ? alphaNStop : 200));
    rect(214, 24, 105 * HP, 10, 5);

    for (int i = 0; i < 2; i++) {
      line(240, 55 + i, 315, 55 + i);

      line(240 + i, 54, 240 + i, 50);
      line(314 + i, 54, 314 + i, 50);
    }

    int firstCCalc = 0;
    for (int i = 0; i < kotoDama.size(); i++) {
      textSize(12);
      firstCCalc += textRect(kotoDama[i]).w;
    }

    if (nowNonStop != NULL) {
      for (int i = 0; i < 7; i++) {
        line(240 +
                 75 * ((counterFirstNStop < 250 + firstCCalc + 100)
                           ? 0
                           : (double)(nowNonStop->getOrder() + 1) /
                                 (double)nonStopW->getLength()),
             48 + 3 * sin(radians(frameCount) * 4),
             237 + i +
                 75 * ((counterFirstNStop < 250 + firstCCalc + 100)
                           ? 0
                           : (double)(nowNonStop->getOrder() + 1) /
                                 (double)nonStopW->getLength()),
             42 + 3 * sin(radians(frameCount) * 4));
      }
    }

    imageMode(LEFT, TOP);
    image(ImgHP, 202, 24);

    fill(255, 255 - ((alphaNStop < 255) ? alphaNStop : 255));
    textAlign(CENTER, TOP);
    textSize(12);
    imageMode(CENTER, CENTER2);

    for (int i = 0; i < 3; i++) {
      if ((counterFirstNStop > 200) && (counterFirstNStop - 250 < firstCCalc)) {
        double tmpCount = 0;
        textSize(12);

        int widthTemp = 0;
        for (int i = 0; i < kotoDama.size(); i += 1) {
          widthTemp += textRect(kotoDama[i]).w;
          if (widthTemp > counterFirstNStop - 250) {
            tmpCount = (double)(widthTemp - (counterFirstNStop - 250)) /
                       (((double)textRect(kotoDama[i]).w));

            if (tmpCount > 1)
              tmpCount = 1;
            tmpCount = 1 - tmpCount;
            break;
          }
        }
        rotate(60 * i + ((tmpCount * 60 * 5 >= 60) ? 60 : (tmpCount * 60 * 5)));

      } else {
        if (!IsTamaChange) {
          rotate(60 * i);
        } else {
          rotate(60 * i +
                 60 * ((double)tamaChgWidth /
                       (double)textRect(kotoDama[nowKotoDamaPos]).w));
        }
      }
      image(Rb, 15, 180, Rb->w * 3, Rb->h * 3);
    }

    if (counterFirstNStop > 250 + firstCCalc + 100) {
      if (nowNonStop != NULL)
        isWeakPAlive = nowNonStop->drawText();
      fill(255, 255 - ((alphaNStop < 255) ? alphaNStop : 255));
      textAlign(CENTER, TOP);
      textSize(12);
      rotate(0);
      if (nowNonStop != NULL) {
        String nameTmp(*(Chara[nowNonStop->getCharaNum()]->getName()));
        for (int i = 0; i < nameTmp.length(); i++) {
          text(nameTmp[i], winWidth / 2 + 13 * i, 162 - 1 * i / 2);
        }
      }

      textSize(12);
      int y = 145;
      if (!IsTamaChange && !isTamaGoing) {
        int x = textRect(kotoDama[nowKotoDamaPos]).w + 30;

        imageMode(LEFT, TOP);
        image(Dangan1, x, y);
        imageMode(RIGHT, TOP);
        image(Dangan2, x, y, textRect(kotoDama[nowKotoDamaPos]).w, Dangan2->h);
        image(Dangan3, x - textRect(kotoDama[nowKotoDamaPos]).w, y);
        fill(10, 255 - ((alphaNStop < 255) ? alphaNStop : 255));
        textAlign(RIGHT, TOP);
        text(kotoDama[nowKotoDamaPos], x, y + 1);

      } else if (IsTamaChange && !isTamaGoing) {
        int x = tamaChgWidth + 30;
        tamaChgWidth += 5;
        imageMode(LEFT, TOP);
        image(Dangan1, x, y);
        imageMode(RIGHT, TOP);
        image(Dangan2, x, y, tamaChgWidth, Dangan2->h);
        image(Dangan3, x - tamaChgWidth, y);
        fill(10, 255 - ((alphaNStop < 255) ? alphaNStop : 255));
        if (tamaChgWidth > textRect(kotoDama[nowKotoDamaPos]).w) {
          tamaChgWidth = 0;
          IsTamaChange = false;
        }

      } else if (isTamaGoing) {
        counterTama++;
        int x = textRect(kotoDama[nowKotoDamaPos]).w + 30 +
                (counterTama * counterTama) * 2;
        imageMode(LEFT, TOP);
        image(Dangan1, x, y);
        imageMode(RIGHT, TOP);
        image(Dangan2, x, y, textRect(kotoDama[nowKotoDamaPos]).w, Dangan2->h);
        image(Dangan3, x - textRect(kotoDama[nowKotoDamaPos]).w, y);
        fill(10, 255 - ((alphaNStop < 255) ? alphaNStop : 255));
        textAlign(RIGHT, TOP);
        text(kotoDama[nowKotoDamaPos], x, y + 1);

        int Speed = 50;
        if ((tamaToX > tamaX)) {
          tamaX = (tamaToX <= tamaX) ? tamaToX : tamaX + 1 * Speed;
          imageMode(CENTER, CENTER2);
          image(danganAll, tamaX, tamaY);
        } else {
          if (isJudged) {
            if (isRonpa) {
              if (counterRonpa < 60) {
              } else if (counterRonpa < 100) {
                int counterTmp = (counterRonpa - 60);
                fill(10, ((counterTmp * 20 < 255) ? counterTmp * 20 : 255));
                rect(0, 0, winWidth,
                     ((counterTmp * 10 > winHeight / 2) ? winHeight / 2
                                                        : counterTmp * 10));
                fill(10, ((counterTmp * 20 < 255) ? counterTmp * 20 : 255));
                rect(0, winHeight - ((counterTmp * 10 > winHeight / 2)
                                         ? winHeight / 2
                                         : counterTmp * 10),
                     winWidth,
                     ((counterRonpa * 10 > winHeight / 2) ? winHeight / 2

                                                          : counterTmp * 10));

              } else if (((counterRonpa - 100) * 40 < winWidth + 100)) {
                fill(10, 255);
                rect(0, 0, winWidth, winHeight);
                fill(255, 255);
                for (int i = 0;
                     i < 100 * ((counterRonpa - 100) * 40) / (winWidth + 100);
                     i++) {
                  line(winWidth + 100, winHeight / 2,
                       -(((counterRonpa - 100) * 40 < winWidth + 100)
                             ? (counterRonpa - 100) * 40
                             : winWidth + 100) +
                           winWidth + 100,
                       winHeight / 2 + i);
                  line(winWidth + 100, winHeight / 2,
                       -(((counterRonpa - 100) * 40 < winWidth + 100)
                             ? (counterRonpa - 100) * 40
                             : winWidth + 100) +
                           winWidth + 100,
                       winHeight / 2 - i);
                }
              } else if (counterRonpa < 250) {
                fill(255, 255);
                rect(0, 0, winWidth, winHeight);

                fill(10, 255);
                for (int i = 0; i < 500; i++) {
                  line(winWidth + 100, winHeight / 2, 0,
                       winHeight / 2 + 100 + i);
                  line(winWidth + 100, winHeight / 2, 0,
                       winHeight / 2 - 100 - i);
                }

                fill(10, 255);
                textSize(45);
                textAlign(CENTER, CENTER2);
                rotate(-10);
                double x =
                    ((counterRonpa - ((winWidth + 100) / 40 + 100)) * 100 < 200)
                        ? (counterRonpa - ((winWidth + 100) / 40 + 100)) * 100
                        : 200;
                if (x == 200) {
                  x += (counterRonpa - ((winWidth + 100) / 40 + 100)) / 10;
                }
                textSize(90);
                text("論", winWidth - x - 60, winHeight / 2 - 40);
                textSize(80);
                text("破", winWidth - x + 10, winHeight / 2 + 30 + 5);
                rotate(0);

                if (counterRonpa > 220) {
                  int alpha = ((counterRonpa - 220) * 50 < 255)
                                  ? (counterRonpa - 220) * 50
                                  : 255;
                  fill(10, alpha);
                  int height = ((counterRonpa - 220) * 30 < winHeight)
                                   ? (counterRonpa - 220) * 30
                                   : winHeight;
                  rect(0, winHeight / 2 - height / 2, winWidth, height);
                }
              } else if (counterRonpa < 500) {
                fill(10, 255);
                rect(0, 0, winWidth, winHeight);
                fill(255, 255);
                if (counterRonpa > 270 && counterRonpa < 320) {
                  if (counterRonpa % 10 < 6)
                    fill(0, 255);
                }
                textAlign(CENTER, CENTER2);
                textSize(24);
                if (counterRonpa > 400) {
                  textSize(24 + (double)((counterRonpa - 400) * 5));
                  fill(255, 255 - ((((counterRonpa - 400) * 30) < 255)
                                       ? ((counterRonpa - 400) * 30)
                                       : 255));
                  // textSize(40 + 15 + (counterRonpa - 250));
                }
                text("BREAK!!", winWidth / 2, winHeight / 2);
              } else {
                fill(10, 255);
                rect(0, 0, winWidth, winHeight);
                isEndNStop = true;
              }

            } else if (isNotRonpa) {
              tamaX = tamaX + 1 * 5;
              tamaY = tamaY + 1 * 5;
              imageMode(CENTER, CENTER2);
              rotate(counterTama * 50);
              image(danganAll, tamaX, tamaY);
              rotate(0);
              if (counterNRonpa < 20) {
                fill(255, 255 * sin(radians((double)((counterNRonpa * 20 < 180)
                                                         ? counterNRonpa * 20
                                                         : 180))));
                rect(0, 0, winWidth, winHeight);
              } else if (counterNRonpa >= 100) {
                isEndNStop = true;
              }
            } else {
              tamaX = tamaX + 1 * Speed;
              imageMode(CENTER, CENTER2);
              image(danganAll, tamaX, tamaY);
            }
          }
        }
      }

    } else {
      if (counterFirstNStop < 200) {
        rotate(0);
        fill(10, 255);
        rect(0, winHeight / 2 - 7.5,
             (counterFirstNStop * 20 < winWidth) ? counterFirstNStop * 20
                                                 : winWidth,
             15);
        if (counterFirstNStop * 20 > winWidth) {
          textAlign(CENTER, CENTER2);
          textSize(12);
          fill(255, 255);
          text("ノンストップ議論開始！", winWidth / 2, winHeight / 2);
        }
      } else if (counterFirstNStop < 250) {
        fill(10, 255);
        rect(0, winHeight / 2 - (((15 - (counterFirstNStop - 200)) / 2 > 0)
                                     ? (15 - (counterFirstNStop - 200)) / 2
                                     : 0),
             winWidth, ((15 - (counterFirstNStop - 200)) > 0)
                           ? (15 - (counterFirstNStop - 200))
                           : 0);
      } else {
        textAlign(RIGHT, TOP);
        fill(10, 255);
        textSize(12);
        rotate(0);

        int counterRonpaeset = counterFirstNStop - 250;
        int wKeep = 0;
        int hKeep = 0;
        for (int i = 0; i < kotoDama.size(); i++) {
          hKeep += textRect(kotoDama[i]).h + 10;
        }
        hKeep = (winHeight - hKeep) / 2;
        int vanishX = -((counterFirstNStop > (250 + firstCCalc + 50))
                            ? counterFirstNStop - (250 + firstCCalc + 50)
                            : 0) *
                      10;

        for (int i = 0; i < kotoDama.size(); i++) {
          int lag = counterRonpaeset - wKeep;
          int x = ((textRect(kotoDama[i]).w + 10 > 10 * (lag))
                       ? 10 * (lag)
                       : textRect(kotoDama[i]).w + 10) +
                  vanishX;

          imageMode(LEFT, TOP);
          image(Dangan1, x, hKeep - 1);
          imageMode(RIGHT, TOP);
          image(Dangan2, x, hKeep - 1, textRect(kotoDama[i]).w, Dangan2->h);

          image(Dangan3, x - textRect(kotoDama[i]).w, hKeep - 1);

          text(kotoDama[i], x, hKeep);

          if ((textRect(kotoDama[i]).w + 10 > 10 * (lag)))
            break;
          else {
            hKeep += textRect(kotoDama[i]).h + 10;
            wKeep += textRect(kotoDama[i]).w;
          }
        }
      }
    }
    imageMode(CENTER, CENTER2);
    rotate(frameCount);
    if (counterFirstNStop > 250 && alphaNStop < 255 && !isRonpa &&
        !isNotRonpa) {
      if (!isTamaGoing) {
        image(Cursor, mouseX, mouseY);
      } else {
        int expand = (counterTama * 20 < 180) ? counterTama * 20 : 0;
        image(Cursor, mouseX, mouseY,
              Cursor->w + Cursor->w * sin(radians(expand)),
              Cursor->h + Cursor->h * sin(radians(expand)));
      }
    }
  } else {

    fill(255, 255);
    rect(0, 145 + (((255 - alphaNStop) > 0) ? (255 - alphaNStop) : 0) +
                counterMissNStop * 2,
         winWidth, 180);

    rotate(0);
    fill(100, 255);
    for (int i = 0; i < 25; i++) {
      fill(100, 255);
      line(0, 170 + ((i < 10) ? i : 10) - 30 +
                  ((counterMissNStop * 2 > 30) ? 30 : counterMissNStop * 2),
           winWidth,
           150 + i - 30 +
               ((counterMissNStop * 2 > 30) ? 30 : counterMissNStop * 2));
    }

    if (counterMissNStop == 0) {
      textAlign(LEFT, TOP);
      textSize(12);
      fill(255);
      String nameTmp = String(*(
          Chara[(isNotRonpa) ? ((missSerifuChange == 0) ? missCharaNum : 0) : 0]
              ->getName()));
      for (int i = 0; i < nameTmp.length(); i++) {
        text(nameTmp[i], winWidth / 2 + 13 * i, 162 - 1 * i / 2 - 30);
      }

      if (alphaNStop >= 255) {
        if (isNotRonpa) {
          //
          if (missSerifuChange == 0) {
            String missSerifu = String(*(Chara[missCharaNum]->getMissSerifu()));
            if (mesPosNStop < missSerifu.length()) {
              if (missSerifu[mesPosNStop] == "\n") {
                linePosNonStop++;
                mesPosNStop++;
              }
              mesBoxGoNStop[linePosNonStop] += missSerifu[mesPosNStop];
              mesPosNStop++;
            } else {
              if (mouseLeft) {
                missSerifuChange++;
                linePosNonStop = 0;
                mesPosNStop = 0;
                mesBoxGoNStop.clear();
                for (int i = 0; i < 3; i++) {
                  mesBoxGoNStop.push_back(move(String("")));
                }
              }
            }
          } else {
            String missSerifu =
                String("しまった！\nみんなの印象を悪くしてしまった...");
            if (mesPosNStop < missSerifu.length()) {
              if (missSerifu[mesPosNStop] == "\n") {
                linePosNonStop++;
                mesPosNStop++;
              }
              mesBoxGoNStop[linePosNonStop] += missSerifu[mesPosNStop];
              mesPosNStop++;

            } else {
              if (mouseLeft) {
                isNotRonpa = false;
                missSerifuChange = 0;
                counterMissNStop++;
                mesPosNStop = 0;
                linePosNonStop = 0;
                mesBoxGoNStop.clear();
                isJudged = false;
                for (int i = 0; i < 3; i++) {
                  mesBoxGoNStop.push_back(move(String("")));
                }
              }
            }
          }

          counterNRonpa = 0;

          //
        } else {
          if (mesPosNStop < hint.length()) {
            if (hint[mesPosNStop] == "\n") {
              linePosNonStop++;
              mesPosNStop++;
            }
            mesBoxGoNStop[linePosNonStop] += hint[mesPosNStop];
            mesPosNStop++;
          } else {
            if (mouseLeft) {
              counterMissNStop++;
              mesPosNStop = 0;
              linePosNonStop = 0;
              mesBoxGoNStop.clear();
              for (int i = 0; i < 3; i++) {
                mesBoxGoNStop.push_back(move(String("")));
              }
            }
          }
        }

        fill(10, ((alphaNStop < 255) ? alphaNStop : 255));
        for (int i = 0; i < mesBoxGoNStop.size(); i++) {
          text(mesBoxGoNStop[i], 10,
               (winHeight / 4) * 3 + 2 + 14 * i - 15 + 15);
        }
      }
    }
  }
}
