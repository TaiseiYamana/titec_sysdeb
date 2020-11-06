# 演習１

リモートの準備

```
$ git init alice
$ cd alice
$ touch sampleA.txt
$ echo hogehoge > sampleA.txt 
$ git add sampleA.txt 
$ git commit -m "first commit"

$ ls
sampleA.txt
```

ローカルにリモートの複製をする。
```
$ cd ..
$ git clone alice dev
$ ls  #リモート、ローカルリポジトリーを作成
alice	dev

$ cd dev
$ ls
sampleA.txt
```
aliceにあるファイルがdevで確認できた。

git remote -vでリモートリポジトリを確認
```
$ git remote -v
origin	/Users/yamanataisei/Documents/lecture/PullPush/alice (fetch)
origin	/Users/yamanataisei/Documents/lecture/PullPush/alice (push)
```

# 演習２
## pullの準備

リモート側(allice)でcommit
```
$ echo hogehoge > sampleB.txt 
$ $ git add sampleB.txt 
$ git commite -m "second commit"

$ git log --graph
* commit ee7e86c3 
$ ls
sampleA.txt	sampleB.txt
```

second commitにorigin/masterが移動してる。ファイルの確認できた。

## push
ローカル側(dev)でコミット
```
$ echo hogehoge > sampleC.txt 
$ git add sampleC.txt 
$ git commit -m "third commit from local"
```

確認
```
$ git log --graph
* commit 94aac0e608150521dbe760cd02818b156bcd4782 (HEAD -> master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Nov 6 11:28:10 2020 +0900
| 
|     third commit from local
| 
* commit ee7e86c31308d3c90a19111a26ebdf7ee5b1bf4e (origin/master, origin/HEAD)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Nov 6 11:22:11 2020 +0900
| 
|     second commit
| 
* commit 7b7971a614ae67ed6e3a24a45f365d2249889d94
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Fri Nov 6 11:11:40 2020 +0900
  
      first commit
```
origin/masterの上に作成される。

pushの実行
```
$ git push
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 12 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (2/2), 285 bytes | 285.00 KiB/s, done.
Total 2 (delta 0), reused 0 (delta 0)
remote: error: refusing to update checked out branch: refs/heads/master
remote: error: By default, updating the current branch in a non-bare repository
remote: is denied, because it will make the index and work tree inconsistent
remote: with what you pushed, and will require 'git reset --hard' to match
remote: the work tree to HEAD.
remote: 
remote: You can set the 'receive.denyCurrentBranch' configuration variable
remote: to 'ignore' or 'warn' in the remote repository to allow pushing into
remote: its current branch; however, this is not recommended unless you
remote: arranged to update its work tree to match what you pushed in some
remote: other way.
remote: 
remote: To squelch this message and still keep the default behaviour, set
remote: 'receive.denyCurrentBranch' configuration variable to 'refuse'.
To /Users/yamanataisei/Documents/lecture/PullPush/alice
 ! [remote rejected] master -> master (branch is currently checked out)
error: failed to push some refs to '/Users/yamanataisei/Documents/lecture/PullPush/alice'
```
実行エラーが起きる。  
[解決手法](https://www.xmisao.com/2014/06/29/git-push-failure-refusing-to-update-checked-out-branch.html)  
リモート側で次のコマンドを実行  
カレントブランチへのpushを受け付けるようにreceive.denyCurrentBranchオプションをignoreに設定する。
```
git config --add receive.denyCurrentBranch ignore
```
再度git pushを実行

リモート側の確認
```
i$ git log --graph
* commit 94aac0e608150521dbe760cd02818b156bcd4782 (HEAD -> master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Nov 6 11:28:10 2020 +0900
| 
|     third commit from local
| 
* commit ee7e86c31308d3c90a19111a26ebdf7ee5b1bf4e
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Nov 6 11:22:11 2020 +0900
| 
|     second commit
| 
* commit 7b7971a614ae67ed6e3a24a45f365d2249889d94
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Fri Nov 6 11:11:40 2020 +0900
  
      first commit
```
commitのログは適応されるがローカルでコミットされたファイルが適応されなかった。
リモート側のファイルの書き込み権限をフリーにしたり、sudoコマンドをしたがファイルの追加ができなかった。

正常にコミットしたのにもかかわらず、
git diffをしたところ、何も出力はされず
ローカル側でgit stetusをしてみたところ`nothing to commit, working tree clean`になってしまっている。時間的に解決することができなかった。
(https://teratail.com/questions/99731)

# 演習３

# 演習４
リポジトリーの作成
![スクリーンショット 2020-11-06 13 05 37](https://user-images.githubusercontent.com/54575368/98325076-4949ed00-2031-11eb-8dc5-53db32706e78.png)
アカウント名:TaiseiYamana
リポジトリー名：myproj

ローカルの準備：
```
$ mkdir local_myproj
$ cd local_myproj
$ git init

$ git remote add origin https://github.com/TaiseiYamana/myproj.git
```

リモートとのリンクを確認
```
$ git remote -v
origin  https://github.com/TaiseiYamana/myproj.git (fetch)
origin  https://github.com/TaiseiYamana/myproj.git (push)
```
localリポジトリに２回コミット
```
$ echo hogehoge > testA.txt
$ git add testA.txt 
$ git commit -m "1st commit from local"
$ echo hogehoge > testB.txt
$ git add testB.txt 
$ git commit -m "2nd commit from local"
```

githubのリモートリポジトリーにpushを実行
```
$ git push -u origin master
Username for 'https://github.com': TaiseiYamana
Password for 'https://TaiseiYamana@github.com': 
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (5/5), 447 bytes | 447.00 KiB/s, done.
Total 5 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), done.
To https://github.com/TaiseiYamana/myproj.git
 * [new branch]      master -> master
Branch 'master' set up to track remote branch 'master' from 'origin'.
yamanayasuonoMacBook-Pro:local_myproj yamanataisei$ 
```
自分のPCではmainではなくmasterで実行できた。

github確認
![スクリーンショット 2020-11-06 13 18 06](https://user-images.githubusercontent.com/54575368/98325611-8c589000-2032-11eb-9d88-1f85adca9d8e.png)

## Githubに表示されるコマンドの意味の理解
```
git remote add origin git@...
git branch -M main
git push -u origin main
```
一行目はローカル作成のコマンド、二行目はブランチ名を変更するコマンド、三行目はpushするコマンド

option -uの意味
```
set upstream for git pull/status
```



