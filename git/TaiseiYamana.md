# 演習１

## リポジトリー作成

```
git init myproj
cd myproj
```
## コミット作業
```
$ echo foobar > foo
$ git add foo
$ git commit -m "fist commit"
[master (root-commit) e2da8e7] fist commit
 Committer: 山名泰生
Your name and email address were configured automatically based
on your username and hostname. Please check that they are accurate.
You can suppress this message by setting them explicitly:

    git config --global user.name "Your Name"
    git config --global user.email you@example.com

After doing this, you may fix the identity used for this commit with:

    git commit --amend --reset-author

 1 file changed, 1 insertion(+)
 create mode 100644 foo
 
```
### ２回目以降のコミット
```
$ echo foobar2 > foo
$ git add foo
$ git commit -m "second commit"
$ echo foobar3 > foo
$ git add foo
$ git commit -m "third commit"
```
## コミット履歴表示
```
$ git log --graph --all
* commit f8123525f01c7a5193e1bc402f4543edcd4d7188 (HEAD -> master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 20:51:00 2020 +0900
| 
|     third commit
| 
* commit 818ffa21dc651d6bbdbae1255ca3f3ef32fe3a1d
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 20:50:22 2020 +0900
| 
|     second commit
| 
* commit e2da8e7632e1a3195f2236a0e68311dc0855e08f
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Fri Oct 23 20:49:40 2020 +0900
  
      fist commit
```

ここで自動的に新しくコミットされたところがmasterブランチに切り替わっていることがわかる。

# 演習２
先ほどのgit logからコミットIDを取得し、`git diff`でコミット間の差分を確認する。

## コミット1とコミット2の差
```
$ git diff e2da8e7632e1a3195f2236a0e68311dc0855e08f 818ffa21dc651d6bbdbae1255ca3f3ef32fe3a1d
diff --git a/foo b/foo
index 323fae0..231796c 100644
--- a/foo
+++ b/foo
@@ -1 +1 @@
-foobar
+foobar2
```

## コミット2とコミット3の差
```
$ git diff 818ffa21dc651d6bbdbae1255ca3f3ef32fe3a1d f8123525f01c7a5193e1bc402f4543edcd4d7188
diff --git a/foo b/foo
index 231796c..329b32c 100644
--- a/foo
+++ b/foo
@@ -1 +1 @@
-foobar2
+foobar3
```

## コミット1とコミット3の差
```
$ git diff e2da8e7632e1a3195f2236a0e68311dc0855e08f f8123525f01c7a5193e1bc402f4543edcd4d7188
diff --git a/foo b/foo
index 323fae0..329b32c 100644
--- a/foo
+++ b/foo
@@ -1 +1 @@
-foobar
+foobar3
```

# 演習3
この[qiitaのサイト](https://qiita.com/omu58n/items/7794f097b2c569a469bc)からクイックソートのサンプルコードをかりてハンクを追加してgit addした。

## 使用したコード

```
/quicksort.c
/ハンクしたい行
#include<stdio.h>

/* 値を入れ替える関数 */
void swap (int *x, int *y) {
  int temp;    // 値を一時保存する変数

  temp = *x;
  *x = *y;
  *y = temp;
}

〜〜〜〜〜〜〜〜〜〜〜〜省〜〜〜〜〜〜〜〜〜〜〜〜〜〜
〜〜〜〜〜〜〜〜〜〜〜〜略〜〜〜〜〜〜〜〜〜〜〜〜〜〜

  return 0;
}

```
ハンクをgit addする時に、二行目に「ハンクしたい行」とコメントアウトする。

## ハンクのgit add
最初にコメント文なしのバージョンのquicksort.cをコミットする。
```
$ git add quicksort.c
$ git commit -m "add quicksort.c"
```

次にコメント文を追加して、ハンクを選択的にaddする。
```
$ git add -p quicksort.c

diff --git a/quicksort.c b/quicksort.c
index 3803ffe..4fcebdf 100644
--- a/quicksort.c
+++ b/quicksort.c
@@ -1,5 +1,5 @@
 /quicksort.c
-
+/ハンクしたい行
 #include<stdio.h>
 
 /* 値を入れ替える関数 */
(1/1) Stage this hunk [y,n,q,a,d,e,?]? y
```

## 差分の確認
```
$ git diff --cached
diff --git a/quicksort.c b/quicksort.c
index 3803ffe..4fcebdf 100644
--- a/quicksort.c
+++ b/quicksort.c
@@ -1,5 +1,5 @@
 /quicksort.c
-
+/ハンクしたい行
 #include<stdio.h>
 
 /* 値を入れ替える関数 */
```

### コミット
```
$ git commit -m "ハンクのコミット"
```

# 演習4
## コミット履歴確認
```
$ git log --graph --all
* commit 6eb9d963d6dfccc996ded7b3f6e6ba3bd0a455b4 (HEAD -> master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:06:57 2020 +0900
| 
|     ハンクのコミット
| 
* commit 5ceaec2c094a0627bbff9971dabd5e9149893548
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:03:04 2020 +0900
| 
|     add quicksort.c
| 
* commit 3d705dc1207dbc16efa4e303151ad079d2f1d8da
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 14:52:22 2020 +0900
| 
|     second commit
| 
* commit ba729a992bbac000e9711e03127f4df514290ecf
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Fri Oct 23 14:36:44 2020 +0900
  
      message
```
現在のHeadの位置のディレクトリの内容を確認
```
$ ls
foo		quicksort.c
```
checkoutコマンドでHeadの場所をsecond commitの状態に変更
```
git checkout 3d705dc1207dbc16efa4e303151ad079d2f1d8da
```
## コミット履歴確認
(HEAD)の位置が変わっている(Detached HEAD)のを確認
```
$ git log --graph --all
* commit 6eb9d963d6dfccc996ded7b3f6e6ba3bd0a455b4 (master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:06:57 2020 +0900
| 
|     ハンクのコミット
| 
* commit 5ceaec2c094a0627bbff9971dabd5e9149893548
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:03:04 2020 +0900
| 
|     add quicksort.c
| 
* commit 3d705dc1207dbc16efa4e303151ad079d2f1d8da (HEAD)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 14:52:22 2020 +0900
| 
|     second commit
| 
* commit ba729a992bbac000e9711e03127f4df514290ecf
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Fri Oct 23 14:36:44 2020 +0900
  
      message
```

## 現在のHeadの位置のディレクトリの内容を確認
```
$ ls
foo
```
ディレクトリの中身が復元されていることを確認

### masterにHEADを戻す
```
$ git checkout master
```

# 演習5

## ブランチの作成
`git branch ブランチ名`でbr-aという名前のブランチを作成。
```
git branch br-a
```
コミット履歴を表示
```
$ git log --graph --all
* commit 6eb9d963d6dfccc996ded7b3f6e6ba3bd0a455b4 (HEAD -> master, br-a)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:06:57 2020 +0900
| 
|     ハンクのコミット
| 
* commit 5ceaec2c094a0627bbff9971dabd5e9149893548
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:03:04 2020 +0900
| 
|     add quicksort.c
| 
* commit 3d705dc1207dbc16efa4e303151ad079d2f1d8da
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 14:52:22 2020 +0900
| 
|     second commit
| 
* commit ba729a992bbac000e9711e03127f4df514290ecf
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Fri Oct 23 14:36:44 2020 +0900
  
      message
```
`(HEAD -> master, br-a)`とmasterの他にbr-aブランチができたことが確認。

## br-aにコミットを行う
br-aにHEADを移動
```
$ git checkout br-a
```

helloとプリントするhello.cを新たに作りコミット。

hello.c
```
#include <stdio.h>

int main(){
printf("hello\n");
}
```

hello.cをコミット
```
$ git add hello.c 
$ git commit -m "first new branch create"
```
## タグ名の登録
```
$ git tag tag-a
```
## コミット履歴の表示
```
* commit c8bfc8760eba7c9c371cb006a042954d77607f05 (HEAD -> br-a, tag: tag-a)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:39:49 2020 +0900
| 
|     first new branch create
| 
* commit 6eb9d963d6dfccc996ded7b3f6e6ba3bd0a455b4 (master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:06:57 2020 +0900
| 
|     ハンクのコミット
| 
* commit 5ceaec2c094a0627bbff9971dabd5e9149893548
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:03:04 2020 +0900
| 
|     add quicksort.c
| 
* commit 3d705dc1207dbc16efa4e303151ad079d2f1d8da
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 14:52:22 2020 +0900
| 
|     second commit
| 
* commit ba729a992bbac000e9711e03127f4df514290ecf
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Fri Oct 23 14:36:44 2020 +0900
  
      message
```

# 演習6
## br-aをmainにマージ
Fast-forwardはブランチのポインタをマージさせるブランチに移動させるマージのことである。
Fast-forwardマージのオプジョンは`--no-ff`を記述してマージする。
```
$ git merge --no-ff br-a
```
### マージ後のコミット履歴
```
*   commit 0baba47a2daaa81df6a8baf42a7d18e9dc37b204 (HEAD -> master)
|\  Merge: 6eb9d96 c8bfc87
| | Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| | Date:   Fri Oct 23 15:54:01 2020 +0900
| | 
| |     Merge branch 'br-a'
| | 
| * commit c8bfc8760eba7c9c371cb006a042954d77607f05 (tag: tag-a, br-a)
|/  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
|   Date:   Fri Oct 23 15:39:49 2020 +0900
|   
|       first new branch create
| 
* commit 6eb9d963d6dfccc996ded7b3f6e6ba3bd0a455b4 (tag: v_1.0.0)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:06:57 2020 +0900
| 
|     ハンクのコミット
```

## br-aとmasterに競合するコミットを加え、マージ
演習5で作成したhello.cにmasterブランチとbr-aブランチにそれぞれ異なる(競合が起きるように)変更を加てそれぞれコミットを行う。

### master側 hello.c
<img width="534" alt="スクリーンショット 2020-10-23 23 18 08" src="https://user-images.githubusercontent.com/54575368/97015635-c2076e80-1586-11eb-947b-cf48c16371bd.png">
### br-a側 hello.c
<img width="533" alt="スクリーンショット 2020-10-23 23 21 47" src="https://user-images.githubusercontent.com/54575368/97015453-8ff60c80-1586-11eb-8b34-4dfabb13fd9a.png">

### コミット後のコミット履歴
```
$ git log --graph --all
* commit 363c8d08aad7e0ea564eb64b0e40e12e66eb79b5 (HEAD -> br-a)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 16:00:53 2020 +0900
| 
|     For confilict at br-a
|   
| * commit cdf0baa660a5f424fdd65cb7a389748bcbb9521e (master)
| | Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| | Date:   Fri Oct 23 15:56:49 2020 +0900
| | 
| |     For confilict at main
| |   
| *   commit 0baba47a2daaa81df6a8baf42a7d18e9dc37b204
| |\  Merge: 6eb9d96 c8bfc87
| |/  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
|/|   Date:   Fri Oct 23 15:54:01 2020 +0900
| |   
| |       Merge branch 'br-a'
| | 
* | commit c8bfc8760eba7c9c371cb006a042954d77607f05 (tag: tag-a)
|/  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
|   Date:   Fri Oct 23 15:39:49 2020 +0900
|   
|       first new branch create
| 
* commit 6eb9d963d6dfccc996ded7b3f6e6ba3bd0a455b4
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 15:06:57 2020 +0900
| 
|     ハンクのコミット
| 
```
それぞれのブランチにコミットを確認

## 競合するマージを実施
masterにHEADを移動、br-aとマージ。するとhello.c内の競合が発生したというメッセージに表示される。
```
$ git checkout master
$ git merge br-a

Auto-merging hello.c
CONFLICT (content): Merge conflict in hello.c
Automatic merge failed; fix conflicts and then commit the result.
```
## masterブランチのhello.cの中身を確認。
<img width="578" alt="スクリーンショット 2020-10-23 16 08 29" src="https://user-images.githubusercontent.com/54575368/97017477-ecf2c200-1588-11eb-9dd4-feed25b22d47.png">
ファイルないに競合の状態が記録されている。

## hello.cの内容を次の様に書き換えコミットをおこなう。

### 変更後のhello.c
<img width="407" alt="スクリーンショット 2020-10-23 16 13 12" src="https://user-images.githubusercontent.com/54575368/97017712-38a56b80-1589-11eb-911a-ef41a08e1e08.png">

### コミットとマージ
```
$ git add hello.c
$ git commit -m "confilict merge br-a"
$ git merge --no-ff br-a
```

## コミット履歴を確認
```
*   commit 94c7735b8d7e18ec7533d1d787b9a980af4d67fa (HEAD -> master)
|\  Merge: cdf0baa 363c8d0
| | Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| | Date:   Fri Oct 23 16:10:09 2020 +0900
| | 
| |     Merge branch 'br-a'
| | 
| * commit 363c8d08aad7e0ea564eb64b0e40e12e66eb79b5 (br-a)
| | Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| | Date:   Fri Oct 23 16:00:53 2020 +0900
| | 
| |     For confilict at br-a
| | 
* | commit cdf0baa660a5f424fdd65cb7a389748bcbb9521e
| | Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| | Date:   Fri Oct 23 15:56:49 2020 +0900
| | 
| |     For confilict at main
| |   
* |   commit 0baba47a2daaa81df6a8baf42a7d18e9dc37b204
|\ \  Merge: 6eb9d96 c8bfc87
| |/  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| |   Date:   Fri Oct 23 15:54:01 2020 +0900
| |   
| |       Merge branch 'br-a'
| | 
| * commit c8bfc8760eba7c9c371cb006a042954d77607f05 (tag: tag-a)
|/  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
|   Date:   Fri Oct 23 15:39:49 2020 +0900
|   
|       first new branch create
| 
```

# 演習7
## br-bブランチの作成とコミット
### ブランチ作成
```
$ git branch br-b
$ git checkout br-b
```
### br-bにいくつかの変更を加えてコミット
br-b.textというファイルを加えてコミットをする。
```
$ touch br-b.text
$ git add br-b.text
$ $ git commit -m "rebase test"
```
２回目のコミット
```
$ vim br-b.text
$ git add br-b.text
$ git commit -m "br-b second commit"
```


### コミット履歴表示
```
* commit 36d5c5170f63a704153624b46c870e2177444ec8 (HEAD -> br-b)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 16:25:23 2020 +0900
| 
|     br-b second commit
| 
* commit 86d39ae7f48e4c857d24113d304a6f60425c9e75
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 16:24:07 2020 +0900
| 
|     rebase test
|   
*   commit 94c7735b8d7e18ec7533d1d787b9a980af4d67fa (master)
    Merge: cdf0baa 363c8d0
    Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
    Date:   Fri Oct 23 16:10:09 2020 +0900

     Merge branch 'br-a'
```
masterブランチの上にbr-bブランチが乗っかっている状態になる。

## masterブランチ側に変更を加えてコミット
```
$ git checkout master
$ touch master.text
$ git add master.text
$ git commit -m "rebase test"
```

### コミット履歴表示
```
* commit edcfbb1a16bd74f15b635f03f2e51d78406505ab (HEAD -> master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 16:27:30 2020 +0900
| 
|     rebase test
|   
| * commit 36d5c5170f63a704153624b46c870e2177444ec8 (br-b)
| | Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| | Date:   Fri Oct 23 16:25:23 2020 +0900
| | 
| |     br-b second commit
| | 
| * commit 86d39ae7f48e4c857d24113d304a6f60425c9e75
|/  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
|   Date:   Fri Oct 23 16:24:07 2020 +0900
|   
|       rebase test
|   
*   commit 94c7735b8d7e18ec7533d1d787b9a980af4d67fa (master)
    Merge: cdf0baa 363c8d0
    Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
    Date:   Fri Oct 23 16:10:09 2020 +0900

     Merge branch 'br-a'
```

## br-bを更新後のmaster上にrebaseする。
```
$ git checkout br-b
$ git rebase master
```

### コミット履歴表示
```
* commit 115ae16d84e36eb2e884f1c091a14490c949313e (HEAD -> br-b)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 16:25:23 2020 +0900
| 
|     br-b second commit
| 
* commit da7eca084950c23dfc203f9a6cef8badcd89f719
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 16:24:07 2020 +0900
| 
|     rebase test
| 
* commit edcfbb1a16bd74f15b635f03f2e51d78406505ab (master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Oct 23 16:27:30 2020 +0900
| 
|     rebase test
| 
*   commit 94c7735b8d7e18ec7533d1d787b9a980af4d67fa (master)
    Merge: cdf0baa 363c8d0
    Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
    Date:   Fri Oct 23 16:10:09 2020 +0900

     Merge branch 'br-a'
```
ディレクトリ中身確認
```
$ ls
br-b.text	foo		hello.c		master.text	quicksort.c
```
br-b.textとmaster.textの両方があることを確認した。


# 演習8
## 準備
```
echo "Hello World" > test1.txt
git add test1.txt
git commit -m "1st commit"

echo "Hello World" > test2.txt
git add test2.txt
git commit -m "2nd commit"

echo "AAAAA" >> test1.txt
git add test1.txt
git commit -m "3rd commit"

echo "BBBBB" >> test2.txt
git add test2.txt
git commit -m "4th commit"
```
### 変更前のコミット履歴
```
* commit bb6e1094ec93b9f71a41198c18ae623f8aded1bb (HEAD -> master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Sat Oct 24 02:42:25 2020 +0900
| 
|     4th commit
| 
* commit c079defe986472c06fa5f6961a82657000c982d4
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Sat Oct 24 02:42:11 2020 +0900
| 
|     3rd commit
| 
* commit da44d6b804746ab953788a9fd93c4196a80d8a5e
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Sat Oct 24 02:41:58 2020 +0900
| 
|     2nd commit
| 
* commit 1319f45b9383fa2a02f646f28b8f420413ddac18
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Sat Oct 24 02:41:43 2020 +0900
  
      1st commit

```

### コミットの順番を入れ替える
エディタが開くので入れ替えたいコミットの行を入れ替える。2nd commitと3rd commitを入れ替える。
```
$ git rebase -i 1319f45
Successfully rebased and updated refs/heads/master.
```

### 変更後のコミット履歴
```
* commit 056e12fd12c56dc97a37d24a145d7abec2963759 (HEAD -> master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Sat Oct 24 02:42:25 2020 +0900
| 
|     4th commit
| 
* commit 138db2c7d952eb6533f18d8c0e76a1574b2343af
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Sat Oct 24 02:41:58 2020 +0900
| 
|     2nd commit
| 
* commit 4c269588fe65dab80c8cabfdacf95f17f8fcdc0b
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Sat Oct 24 02:42:11 2020 +0900
| 
|     3rd commit
| 
* commit 1319f45b9383fa2a02f646f28b8f420413ddac18
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Sat Oct 24 02:41:43 2020 +0900
  
      1st commit

```
### ファイルの中身が変わってしまうコミットの入れ替えはCONFLICTのエラーが生じる
例えば、2ndと4thのcommitを入れ替えようとするとエラーメッセージが出力される。commitの入れ替えができるのは、この様に、confilictを避けなければならない。
```
CONFLICT (modify/delete): test2.txt deleted in HEAD and modified in 2b0a62a... 4th commit. Version 2b0a62a... 4th commit of test2.txt left in tree.
error: could not apply 2b0a62a... 4th commit
Resolve all conflicts manually, mark them as resolved with
"git add/rm <conflicted_files>", then run "git rebase --continue".
You can instead skip this commit: run "git rebase --skip".
To abort and get back to the state before "git rebase", run "git rebase --abort".
Could not apply 2b0a62a... 4th commit
```
## commitメッセージを変更
```
$ git commit --amend -m "4th commit : 2nd commitと3rd commitを入れ替えた"
```
### 変更後のコミット履歴
```
* commit 7c48eef7da715f9bf0efb526862eb274570c6179 (HEAD -> master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Sat Oct 24 02:42:25 2020 +0900
| 
|     4th commit : 2nd commitと3rd commitを入れ替えた
| 
* commit 138db2c7d952eb6533f18d8c0e76a1574b2343af
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Sat Oct 24 02:41:58 2020 +0900
| 
|     2nd commit
| 
* commit 4c269588fe65dab80c8cabfdacf95f17f8fcdc0b
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Sat Oct 24 02:42:11 2020 +0900
| 
|     3rd commit
| 
* commit 1319f45b9383fa2a02f646f28b8f420413ddac18
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Sat Oct 24 02:41:43 2020 +0900
  
      1st commit
```

# 演習9
fooをaddする。

```
git add foo
```
`git status`で確認
```
$ git status
On branch master
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	new file:   foo
```
`git reset HEAD ファイル名`でaddの取り消し
```
$ git reset HEAD foo
```
`git status`で確認
$ git status
On branch master
Untracked files:
  (use "git add <file>..." to include in what will be committed)
	foo
```
addを取り消すことができた。

# 演習10
- 良い例：
前提として、誰が見てもどういったコミットの内容かわかるメッセージがいい。  
[誰にとってもわかりやすいGitのコミットメッセージを考える ｜ Tips Note by TAM](https://www.tam-tam.co.jp/tipsnote/program/post16686.html)  

<img width="708" alt="スクリーンショット 2020-10-25 12 44 41" src="https://user-images.githubusercontent.com/54575368/97098403-ddc26000-16bf-11eb-854d-aa74ab650e17.png">

このサイトには上記の動詞から始めるのが、型とするのがいいと記されている。

githubでstarが高いリポジトリーを探した。openposeというディープラーニングモデルの公式リポジトリーを例にあげる。
<img width="910" alt="スクリーンショット 2020-10-25 12 48 32" src="https://user-images.githubusercontent.com/54575368/97098443-67722d80-16c0-11eb-8dee-b945590b0b86.png">

コミットメッセージは大体動詞からはじまってる。まずコミットをみて、なんのコミットを直近でしたのかが、文頭の動詞で判断できる。
- 悪い例:
# 演習11


