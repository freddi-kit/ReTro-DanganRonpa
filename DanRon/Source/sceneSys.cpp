//
//  Scene.cpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/09/26.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#include "sceneSys.hpp"

bool isVanishTitle = false;
int titleVanishCounter = 0;

void gameMain() {
  if (isTitle) {
    Title();
    if (mouseLeft && !isVanishTitle) {
      isVanishTitle = true;
      Chapter[0]->isNowStory = true;
    }
  } else {
    isVanishTitle = false;
    titleVanishCounter = 0;
    for (int i = 0; i < Chapter.size(); i++) {
      if (Chapter[i]->isNowStory) {
        Chapter[i]->storyGo(i);
      }
      break;
    }
  }
}

void Title() {
  rotate(0);
  imageMode(CENTER);
  image(titleImage, winWidth / 2, winHeight / 2 - 25);
  textAlign(CENTER, CENTER2);
  textSize(12);
  fill(10);

  rect(0, winHeight / 2 + 40, winWidth, 20);

  fill(255);

  if ((!isVanishTitle) ? (frameCount % 300 > 25) : (frameCount % 10 >= 5))
    text("ｹﾞｰﾑ ｦ ﾊｼﾞﾒﾙ", winWidth / 2, winHeight / 2 + 50);

  fill(10, (titleVanishCounter * 10 > 255) ? 255 : titleVanishCounter * 10);
  rect(0, 0, winWidth, winHeight);
  if (titleVanishCounter * 10 > 255 + 100) {
    isTitle = false;
  }
  if (isVanishTitle)
    titleVanishCounter++;
}
