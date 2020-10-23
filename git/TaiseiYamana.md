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

# 演習4
この[qiitaのサイト](https://qiita.com/omu58n/items/7794f097b2c569a469bc)からクイックソートのサンプルコードをかりて一部のハンクだけgit addした。

## 使用したコード

```
/quicksort.c
<span style="color: red; ">赤文字</span>
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

<span style="color: red; ">赤文字</span>
