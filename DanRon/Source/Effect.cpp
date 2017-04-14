//
//  Effect.cpp
//  DanRon
//
//  Created by 秋勇紀 on 2016/09/26.
//  Copyright © 2016 秋勇紀. All rights reserved.
//

#include "Effect.hpp"

void likeRetro() {
  rotate(0);

  fill(60, 100, 40, 130);
  rect(0, 0, winWidth, winHeight);
  if (frameCount % 3 != 0) {
    fill(60, 100, 40, 130);
    for (int i = 0; i < winHeight; i += 5) {
      line(0, i, winWidth, i);
    }
  }
}
