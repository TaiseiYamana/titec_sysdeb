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
mac OSのcoreファイルは`/cores`のディレクトリ下に置かれる。しかし、このディレクトリの権限に書き込み権限がないためデフォルトではこのディレクトリー内にcoreファイルが生成されない。`参照3.1`ではcoresの書き込み権限を与えることによって解決していた。

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

### 権限の戻し方
どこかの記事に、macではcoreファイルが自動的に生成されるとHDDの圧迫に繋がるらしいとのことで、実験の最後権限を戻す。

```
$ sudo chmod 755 /cores
```

### 使用したコード
参照3.3より、クイックソードの`quicksort.c`を借りて実行した。(coreファイルの出力の調査にかなり時間がかかったため)

## 実行

```
$ clang -O3 -g -o quicksort quicksort.c
$ ulimit -c unlimited
$ ./quicksort
Segmentation fault: 11 (core dumped)
```

### corefileの確認
```
$ ls /cores
core.26576
```
### coreファイルをロードしながらlldb起動
```
$ lldb quicksort -c /cores/core.26576
(lldb) target create "quicksort" --core "/cores/core.26576"
Core file '/cores/core.26576' (x86_64) was loaded.
```

### 結果
```
(lldb) r
There is a running process, kill it and restart?: [Y/n] y
Process 26909 launched: '/Users/yamanataisei/Documents/lectire/lec_2_1/quicksort' (x86_64)
Process 26909 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x7ffeefc00000)
    frame #0: 0x0000000100003de0 quicksort`quicksort(array=0x00007ffeefbff9a0, left_index=0, right_index=8) at quicksort.c:16:21
   13  	        while(array[left] < pivot)
   14  	            left++;
   15  	        //右側で基点より小さい点を探す
-> 16  	        while(pivot < array[right])
   17  	            right++;//ここが間違っている
   18  	
   19  	        if(right < left)
Target 0: (quicksort) stopped.
```
問題がある行で止まっていました。`right++;`が配列の範囲外を参照するとのことで`reason = EXC_BAD_ACCESScore`と表示されていました。しかしcoreファイルをロードした時の違いがあまりよくわかりません。

[参照サイト]
- 3.1:[macos-MacCatalinaコアファイルの場所-スタックオーバーフロー](https://stackoverflow.com/questions/58844265/mac-catalina-corefile-locations)
- 3.2:[今さら聞きづらい「ファイルパーミッション」について (フェンリル | デベロッパーズブログ)](https://blog.fenrir-inc.com/jp/2012/02/file_permission.html)
- 3.3:[gdbを使ってコアダンプの原因を解析 - それが僕には楽しかったんです。](https://rabbitfoot141.hatenablog.com/entry/2016/11/14/153101)

# 演習4
知識補完のために`参照4.1`を読んだ。

### 使用したコード
演習1で使用した`array-out-of.cpp`に`asm("int3");`を組み込んで使用。

## 実行結果

```
$ lldb array-out-of
(lldb) target create "array-out-of"
Current executable set to '/Users/yamanataisei/Documents/lectire/lec_2_1/array-out-of' (x86_64).
(lldb) r
Process 27515 launched: '/Users/yamanataisei/Documents/lectire/lec_2_1/array-out-of' (x86_64)
Process 27515 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BREAKPOINT (code=EXC_I386_BPT, subcode=0x0)
    frame #0: 0x0000000100003f63 array-out-of`main at array-out-of.cpp:8:5
   5   	    for(int i = 0; i <= 100; i++) {
   6   	    a[i] = i;
   7   	  }
-> 8   	    asm("int3");
   9   	    return 0;
   10  	}
Target 0: (array-out-of) stopped.
```

[参照サイト]
- 4.1:[__asm int 3でのブレイクポイントについて - OKWAVE](https://okwave.jp/qa/q6354980.html)

# 演習5
### 使用したコード
演習1で使用した`array-out-of.cpp`をそのまま使用

## 実行
watchpointを設定するために変数が定義される行までブレイクポイントを決めて実行する。
```
$ lldb array-out-of
(lldb) target create "array-out-of"
Current executable set to '/Users/yamanataisei/Documents/lectire/lec_2_1/array-out-of' (x86_64).
(lldb) b array-out-of.cpp:2
Breakpoint 1: where = array-out-of`main + 35 at array-out-of.cpp:5:13, address = 0x0000000100003f23
(lldb) r
```

### watchpointの設定
試しに定義される配列aのa[50]をwatchpointとして設定。
```
watchpoint set variable a[50]
Watchpoint created: Watchpoint 1: addr = 0x7ffeefbff8e8 size = 4 state = enabled type = w
    declare @ '/Users/yamanataisei/Documents/lectire/lec_2_1/array-out-of.cpp:4'
    watchpoint spec = 'a[50]'
    new value: 65536
```

### 再度実行
```
(lldb) c
Process 28331 resuming

Watchpoint 1 hit:
old value: 65536
new value: 50
Process 28331 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = watchpoint 1
    frame #0: 0x0000000100003f4e array-out-of`main at array-out-of.cpp:5:31
   2   	
   3   	int main() {
   4   	    int a[100];
-> 5   	    for(int i = 0; i <= 100; i++) {
   6   	    a[i] = i;
   7   	  }
   8   	    return 0;
Target 0: (array-out-of) stopped.
```
watchpointの変わったので止まった値が変化したことによって実行が変わった。初期化時の値は`65336`であったが、`50`になったと確認できる。

# 演習6
新しくOSSを作り直したい。OSSはpythonで書きたいので、デバック手法をまとめる。

## pdb
pythonではpdbを使ったでバック手法がある。

### 練習コード
```
#hello.py
msg = "Hello world"

def hello(txt):
    print(txt)

hello(msg)
print("Done.")
```

### 実行
<img width="534" alt="スクリーンショット 2020-10-23 3 06 01" src="https://user-images.githubusercontent.com/54575368/96912099-c70fe380-14dc-11eb-873a-fa2f86543c8c.png">


次にpythonでGUIアプリケーションを開発したいと思うので、GUIが作れるライブラリーを調べた。
## gui開発ライブラリー
### Tkinter
### Kivy
### PyQt
### wxPython
ここでTkinterはpython標準ライブラリらしいのでこのライブラリーを使用してみる。

[参照サイト]
- 6.1:[Pythonでpdbを使ったデバッグ - Qiita](https://qiita.com/patekawa/items/3e79fe58b3b2f14dbab5)
- 6.2:[PythonでGUIアプリを作成するのにオススメのライブラリとは？現役エンジニアが解説【初心者向け】 | TechAcademyマガジン](https://techacademy.jp/magazine/21805)
