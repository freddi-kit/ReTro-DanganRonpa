## ReTro-DanganRonpa
レトロゲーム風ダンガンロンパ For MacOS(製作中)
一部ゲーム機能のみ実装。

### 必要なもの
以下に示すライブラリを導入してください。
- SDL2
 - https://www.libsdl.org/download-2.0.php
- SDL2_ttf
 - https://www.libsdl.org/projects/SDL_ttf/
- SDL2_image
 - https://www.libsdl.org/projects/SDL_image/
- SDL2_mixer
 - https://www.libsdl.org/projects/SDL_mixer/

### キッティング
1. 項目「必要なもの」に示しているライブラリ群をインストールしてください。
1. [Xcode](https://blog.codecamp.jp/xcode_install )をインストールしてください。
1. DanRon.xcodeprojをXcodeから開き、左側のファイル一覧から一番上のDanRonという項目を開いてください。
   ![1](md.photos/1.png "1")

1. Targetsの中にあるDanRonを選択して、General -> Linked FrameWorks and Librariesに以下のファイルを追加してください。
    - SDL2.a
    - SDL2_ttf.a
    - SDL2_image.a
    - SDL2_mixer.a
   ![2](md.photos/2.png "2")

1. Build Settings -> Search Paths -> Header Search Pathsに、SDL関係のヘッダーファイルが入っているディレクトリのパスを入れてください。
  ![3](md.photos/3.png "3")

1. 左上の三角形のボタンでコンパイルとビルドができます。

### スクリーンショット
![4](md.photos/4.png "Screen Shot")

![7](md.photos/7.png "Screen Shot")

![8](md.photos/8.png "Screen Shot")

![10](md.photos/10.png "Screen Shot")

![11](md.photos/11.png "Screen Shot")

### おまけ
 -  このゲームはSDL2をProcessing風に扱えるようにする自作ラッパーで制作しました。
  - [こちら](DanRon/Source/SDL2ToProcessing)です。

### TODO
 - 最低限のゲームシステムを整備
  - 日常会話と、ノンストップ議論のみ

 - ストーリを作ろう
  - 現在カスタマイズできるようにxmlで管理できるようにはなっている。
  
 - レトロ感の増加
 - メモリ周りの効率をよくする
