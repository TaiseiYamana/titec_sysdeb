# 演習1
35

ASCIIコード表を調べてctr+Fで「#」を調べた。

man ascii でも可能。

# 演習2
tar -zcvf abc.tar.gz abcls

[参考にしたサイト](https://qiita.com/supersaiakujin/items/c6b54e9add21d375161f)

tar --help

で他のoptionが確認ができる

# 演習3
[作業記録]
- コンパイラ環境を即席で用意した。https://paiza.io/projects/j5V0v-U8Mac-QIZuKINPcg?language=cpp
ここのサイトのブラウザで動く実装環境を使用する。

- 試しにcolattz(5)で実行したところ結果が１になる。

- Compiler Explorer　を使用してもいいことがわかった。



# 演習４

作成したいOSS概要

- 内容:

ボタンを押すと設定した音がなるcppベースのピアノみたいなGUIの制作
目的：とりあえずCppで何かしらのOSSを作成したいと思った。既出しているネタであるとは承知している。

情報収集

~- [MFC](https://brain.cc.kogakuin.ac.jp/~kanamaru/lecture/prog1/03-intro01.html)~

~まずcppでGUIプログラミングをおこなうためには、Visual Studioで使えるMFCパッケージが必要らしい。 つまり事前にVSのインストールが必須。~  

使用するPCがmacであるためwindowsアプリ向けのMFCが使用できなかった。macでFLTKというライブラリでできそうである。

- [FLTK](https://k1mny.hatenablog.com/entry/2017/10/12/125220)  
[公式ドキュメント](https://www.fltk.org/doc-1.3/classFl__Button.html)


-- FLTKのインストール
```
brew install fltk 
```

ボタンを押すことで事前にセッティングしたオーディオファイルを流すような仕組みが必要となる。

C++でwavファイルを再生するAPIを調べた。

https://stackoverflow.com/questions/9981087/simple-c-sound-api

- [PlaySound API](http://yamatyuu.net/computer/program/sdk/other/playsound/index.html)

他にも使用できそうなAPI  
- [mciSendString](http://www.sm.rim.or.jp/~shishido/pmidi.html)  

結果的に使用したAPIはSDL−Mixer  
https://srad.jp/~fslasht/journal/217044/

wavファイルなどの音声メディアファイルをダウンロードするためのサイト
- [フリーWave,MP3](http://www.ne.jp/asahi/music/myuu/wave/wave.htm)
- [ピアノ音階](https://maoudamashii.jokersounds.com/list/se12.html)


実装コードをアップロードしました。実装コード名はC4.cppです。音階のC４の効果音を鳴らすプログラムとなります。

- ボトルネック

ライブラリーのリンク設定がうまくいかず、SDL-Mixerのincludeができなかったので最後までコンパイルがうまくできなかった。来週までにはできる状態にします。
