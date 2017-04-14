//
//  Trial.hpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/10/02.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#ifndef Trial_hpp
#define Trial_hpp

#include "Data.hpp"

//ストーリークラス
class CStory;

//ノンストップ議論用ポイント構造体（ベース）
// ADT構造で管理
class nonStopBase {
public:
  //ウィークポイントでない時のコンストラクタ
  nonStopBase(string _serifu, int _charaNum);
  //ウィークポイント時のコンストラクタ
  nonStopBase(string _serifu, int _charaNum, int _weakPointPos,
              int _weakPointPosEnd, bool _isCorrect, int _cKotoDamaNum = 0);
  ~nonStopBase();

  bool getIsAlive();
  //次のポイントの追加
  void setNext(nonStopBase *_next);
  void setSub(nonStopBase *_sub, int _goTiming);
  //削除
  void deleteMe(nonStopBase *del);

  //次のポイントを返す
  nonStopBase *sNext();

  //サブを返す
  nonStopBase *sSub();
  //サブの出すタイミングを返す
  int getSubTiming();

  //現オーダーを返す
  int getOrder() const;

  //ポイントの長さを返す
  int getLength();

  //ウィークポイントかどうか
  bool getIsWeak();

  //ウィークポイントの文字目を返す
  int getWeakPointPos();
  int getWeakPointPosEnd();

  bool getIsCorrect();

  //キャラ番号を返す
  int getCharaNum();

  String getSerifu() const;

  virtual bool drawText() = 0;
  virtual SDL_Rect getRectOfWeak() = 0;

  int getCKotoDamaNum();
  void ronpaAttack();
  bool getIsAttacked();

  virtual void initMoment();
  virtual bool isInAttack(int x, int y) = 0;

protected:
  //次のポイントのアドレスを格納
  nonStopBase *next;

  int cKotoDamaNum;
  nonStopBase *sub;
  int goTiming;

  //セリフ
  String serifu;

  //ウィークポイントかどうか
  bool isWeak;

  //現在出現してるかどうか
  bool isAlive;

  //ウィークポイントの強調文字のはじめと終わり
  int weakPointPos;
  int weakPointPosEnd;

  //オーダー数
  int order;

  //オーダーを設定
  void setOrder(int _order);

  //キャラ
  int charaNum;

  //論破ポイント
  bool isCorrect;
  bool isAttacked;

  int alpha;

  int counterVanish;
};

//ノンストップ議論用ポイント構造体（横移動）
class nonStopA : public nonStopBase {
public:
  //継承元のコンストラクタ
  using nonStopBase::nonStopBase;
  //ウィークポイントでない時のコンストラクタ
  nonStopA(string _serifu, int _chara, double _x, double _y, double _speedX,
           double _speedY, int _stayCount);
  //ウィークポイント時のコンストラクタ
  nonStopA(string _serifu, int _chara, double _x, double _y, double _speedX,
           double _speedY, int _stayCount, int _weakPointPos,
           int _weakPointPosEnd, bool _isCorrect, int _cKotoDamaNum = 0);

  //描画
  bool drawText() override;
  SDL_Rect getRectOfWeak() override;

  void initMoment() override;
  bool isInAttack(int x, int y) override;

private:
  //始点
  double x = 0;
  double y = 0;

  //スピード
  double speedX;
  double speedY;

  //滞空時間
  int stayCount;
  int counter;

  //移動量
  double moveX;
  double moveY;
};

/*
//ノンストップ議論用ポイント構造体（回転）
class nonStopB : public nonStopBase{
    //中心座標
    int x = 0;
    int y = 0;
};

//ノンストップ議論用ポイント構造体（拡大）
class nonStopC : public nonStopBase{
    //中心座標
    int x = 0;
    int y = 0;
};
*/

//学級裁判用クラス
class CTrial {
private:
  //体力
  float HP;
  //♡画像
  PImage ImgHP;

  /***************************************
   ノンストップ議論関係
   ***************************************/
  //ノンストップ議論フラグ
  bool isNonStop;
  //現在のノンストップ議論ポイント構造体
  nonStopBase *nowNonStop;
  //ノンストップ議論用（デバック）
  nonStopBase *nonStopW;

  //最初の演出のときのカウンター
  int counterFirstNStop;
  //ミスした時のカウンター
  int counterMissNStop;

  //コトダマ(デバッグ)
  vector<string> kotoDama;

  //現在のコトダマ
  vector<string> nowKotoDama;
  //現在進行中のコトダマ位置
  int nowKotoDamaPos;

  //ダンガン画像
  PImage danganAll;
  PImage Dangan1;
  PImage Dangan2;
  PImage Dangan3;

  PImage Cursor;

  int alphaNStop;

  //メッセージフラグ
  bool isMBoxNonStop;

  int mesPosNStop;
  int linePosNonStop;
  //メッセージボックス描画用
  vector<String> mesBoxGoNStop;
  //玉チェンジ
  bool IsTamaChange;
  int tamaChgWidth;

  //玉を打ったか
  bool isTamaGoing;
  int counterTama;
  int tamaX;
  int tamaY;
  int tamaToX;
  int tamaToY;

  bool isJudged;
  bool isRonpa;
  bool isNotRonpa;
  int counterNRonpa;
  int counterRonpa;

  int missCharaNum;
  int missSerifuChange;

  bool isWeakPAlive;
  bool isEndNStop;

  int posNonStop;
  /***************************************
   通常画面関係
   ***************************************/
  bool isNormal;
  //メッセージの文字数
  int mesPos;
  //メッセージのスピード
  int mesSpeed;
  //何行目か
  int linePos;
  //名前
  String name = move(String(""));
  //メッセージスキップフラグ
  bool Skip;
  //描画用変数
  float tSpeed;
  float mPos;
  float rad;
  int counterDraw;

  //現在のセリフ用
  int serifuPos;
  //メッセージボックス描画
  void drawMBox(vector<String> mes);
  //キャラ描画
  void drawChara();

  //シーン切り替え
  bool isSceneChange;

  //
  int counterSceneChg;

  //回転スピード
  float rotaSpeed;
  //注目キャラ
  int charaPointNum;
  //キャラ注目フラグ
  bool isFocus;

  //モノクマフォーカスフラグ
  bool isMonoFocus;

  float monoFPS;

  //メッセージボックス描画用
  vector<String> mesBoxGo;

  bool isSetting;
  int counterSet;

  int counterCharaDraw;
  int drawCharaMoveX;
  bool isFocusNStop;
  int drawCharaNumNowNStop;
  int drawCharaNumOldNStop;
  int drawCharaXNStop;

public:
  CTrial();
  ~CTrial();

  //次に移る
  void nextMes();

  //学級裁判
  void Trial(CStory *story);
  //ノンストップ議論
  void nonStop(vector<string> kotoDama, String hint);
  void sceneChange();

  void initNonStop();

  //ノンストップ議論用
  vector<nonStopBase *> nonStopSerifu;
  vector<vector<string>> nonStopKotodama;

  //ノンストップ議論メッセージ
};

#endif /* Trial_hpp */
