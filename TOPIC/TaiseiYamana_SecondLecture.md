# 10/16 第二回システム開発プロジェクト応用第一課題レポート
## 演習環境

macOS Catalina 10.15.6

# 演習1
## 事前準備
clangのsanitizeはOS依存性があるので自分のPCにある既存のclangでは`-fsanitize=undefined`が使用できなかった。clangのインストールにオプションをつけて再インストールする必要があった。
`参照1.1`に記載されていた以下のコマンドでclangのインストールを行った。

```
brew install llvm38 --with-asan --with-lldb
```
### 使用したコード

配列のレンジ外アクセス用のコードを作成した。

```c++:array-out-of.cpp
//array-out-of.cpp
int main() {
    int a[100];
    for(int i = 0; i <= 100; i++) {
    a[i] = i;
  }
    return 0;
}
```
`int a[100]`で作成される配列aのインデックスは0~99である。よってforループのiの最後の値は100であるため、a[100]の呼び出しはレンジ外である。

## コンパイル

```
$ clang++  -fsanitize=undefined -o array-out-of  array-out-of.cpp
```
clangはsanitizeのオプションを加えないエラーがでないが、`-fsanitize=undefined`を使用すると以下のエラーが出てしまってコンパイルが完了できない。
`参照1.2`によるとc++のコードでは`clang++`でコンパイルする必要があると記されていた。よって、上記のコードで実行したらエラーがなくコンパイルができた。

## 実行

```
$ ./array-out-of 
array-out-of.cpp:4:5: runtime error: index 100 out of bounds for type 'int [100]'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior array-out-of.cpp:4:5 in 
```
インデックス100の呼び出しはレンジ外であるというメッセージが表示された。

[参照サイト]
- 1.1:[cormoran's note - clang のSanitizerについて](https://blog.cormoran-web.com/blog/clang-sanitizer/#undefinedbehaviorsanitizer)
- 1.2:[違いは何ですか？ clang ++ |打ち鳴らす私は誤ってリンクステップで失敗し、このコマンドを使用していた-std = C++ 11](https://stackoverrun.com/ja/q/5474526)

# 演習2

## macOSでgdbにはコード著名が必要
`参照2.1`によると
```Darwin カーネルがセキュリティリスクを回避するために，署名されていないソフトウェアによるデバッグを禁止しているためである． デバッグを可能にするには，手動で GDB にコード署名を行う必要がある．```
とのことであり、コード署名が必要となる。今回はその作業が時間かかるので中断し、`参照2.2`を元に`lldb`でのデバックを行った。

### 使用したコード

演習１のコードを使用した。

## コンパイル
```
$ clang++ -o array-out-of -g array-out-of.cpp
```
コンパイル時にgオプションが必要。

## デバックの開始
```
lldb array-out-of
```

## ブレークポイントの設定
実行コマンドは`b プログラムファイル:行数`
```
(lldb) b array-out-of.cpp:1
Breakpoint 1: where = array-out-of`main + 35 at array-out-of.cpp:3:13, address = 0x0000000100003f23
```

## 実行
実行コマンドは`run`
```
(lldb) run
Process 21320 launched: '/Users/yamanataisei/Documents/lectire/lec_2_1/array-out-of' (x86_64)
Process 21320 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x0000000100003f23 array-out-of`main at array-out-of.cpp:3:13
   1   	int main() {
   2   	    int a[100];
-> 3   	    for(int i = 0; i <= 100; i++) {
   4   	    a[i] = i;
   5   	  }
   6   	    return 0;
   7   	}
Target 0: (array-out-of) stopped.
```

## 変数の値を出力
実行コマンドは`po 変数名`
```
(lldb) po a[0]
1107296256
```
## ステップ実行
実行コマンドは`n`

nを何回か押してa[0]の値を再確認してみたところa[0]の値が変わってることが確認できる。
```
(lldb) po a[0]
0
```

[参照サイト]
- 2.1:[OS XでGDBを使う（ためにコード署名をする） - Qiita](https://qiita.com/takahashim/items/204ffa698afe09bd4e28)
- 2.2:[LLDBを使ってCのデバッグをする - Qiita](https://qiita.com/edo_m18/items/9b6be35907433e1c743e)


# 演習3
## 事前準備
mac OSのcoreファイルは`/cores`のディレクトリ下に置かれる。しかし、このディレクトリの権限に書き取り権限がないためデフォルトではこのディレクトリー内にcoreファイルが生成されない。`参照3.1`ではcoresの書き込み権限を与えることによって解決していた。

### 手順

まずcoresを含むディレクトリでデフォルトの権限を確認する。するとグループと全員の書き込みの権限がないことがわかる。
```
$ ls -l
drwxr-xr-x   2 root  wheel    64  2 29  2020 cores
```

ここで、chmodコマンドで書き込みの権限を与える。

```
$ sudo chmod 1777 cores
$ ls -l
drwxrwxrwt   2 root  wheel    64  2 29  2020 cores
```
`参照3.2`より`「1777」の先頭の1はファイルの持ち主以外が勝手に消す事はできなくなる`設定である。

[参照サイト]
- 3.1:[macos-MacCatalinaコアファイルの場所-スタックオーバーフロー](https://stackoverflow.com/questions/58844265/mac-catalina-corefile-locations)
- 3.2:[今さら聞きづらい「ファイルパーミッション」について (フェンリル | デベロッパーズブログ)](https://blog.fenrir-inc.com/jp/2012/02/file_permission.html)
