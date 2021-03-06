## ProcessingToSDL(Ver.Pre-α)
### 内容
- Processingの一部関数をSDLで使えるようにしたもの。
- まだ１０個程度しか作ってませんが僕のゲームづくり中に需要があり次第増えていきます。

### 使い方
- System.cppとSystem.hppを使いたいSDL2のプロジェクトに入れて下さい。
- 必要に応じてインクルードパスを変更して下さい。
  - #include < SDL2/{SDL関係} >が初期パスです。
- 使う前にInitLPSystem(SDL_Render*,SDL_Window*)関数を呼び出して下さい
- プログラム終了時にはdeleteLPSystem()関数を呼び出して下さい。

### 使用した時の比較
SDL2のみだと画像一枚を表示するだけで１３行も書かないといけないが、ラッパーを利用すると２行のみで簡単に描画可能に！
#### SDL2のみ
```cpp
//SDL2のみ
auto img = SDL_RWFromFile("hoge.png", "r");
auto imageR = IMG_LoadPNG_RW(img);
auto imgTxr = SDL_CreateTextureFromSurface(imageR, img);
src.x = 0;
src.y = 0;
src.w = img->w;
src.h = img->h;
dst.x = 10;
dst.y = 10;
dst.w = img->w;
dst.h = img->h;
SDL_RenderCopyEx(render, imgTxr, &src, &dst, 0 , NULL, SDL_FLIP_NONE);
SDL_DestroyTexture(imgTxr);
```
#### ProcessingToSDL使用時
```cpp
//ProcessingToSDL使用時
auto hoge = loadImage("hoge.png");
image(hoge, 10, 10);
```

### 利用について
- 自由に利用してかまいませんし、改変して再公開してもかまいません。

### 諸注意
- このソースコードを利用したことによる損害等には一切責任を持ちません。


### 連絡等々
- Twitter(@freddi_kit)までお知らせ下さい。

### 実装した型
- String型（文字を配列的に参照するときにバイト数じゃなくて文字数で参照する）

### 実装した変数
- frameCount

### 実装した関数
- void fill(int R,int G,int B,int Alpha);
- void fill(int C,int Alpha);
- void fill(int C);

- void rect(int x,int y,int width,int height);
- void rect(int x,int y,int width,int height,int r);

- void line(int x1,int y1,int x2,int y2);

- void imageMode(aPosition a);
- void imageMode(aPosition a,vPosition v);

- void image(PImage img,int x,int y);
- void image(PImage img,int x,int y,int width,int height);

- void textFont(PFont font);
- void textAlign(aPosition a);
- void textAlign(aPosition a,vPosition v);
- void text(string tx,int x,int y);
- void textSize(int size);

- double radians(int deg);
- PFont loadFont(string path);
- PImage loadImage(string path);
- void frameRate(fps)

#### aPosition型、vPosition型の仕様
```cpp
enum aPosition { LEFT, CENTER, RIGHT };
enum vPosition { TOP, CENTER2, BOTTOM };
```
