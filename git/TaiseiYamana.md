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
タグ名の登録
```
$ git tag tag-a
```
コミット履歴の表示
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

















