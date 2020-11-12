# GitHub & PUll Request 後編

## 演習5

### br-debコミットした状態を準備
```
$ git log --graph
* commit 4e381e1ced2b2fca9a169b49e97fb37152b0ce1c (HEAD -> br-dev)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Nov 6 14:42:30 2020 +0900
| 
|     2nt commit on br-dev
| 
* commit 1ce95cc14b45f487c66a170dd6cd23b0cf1dd0b5
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Nov 6 14:42:07 2020 +0900
| 
|     1st commit on br-dev
| 
* commit 01988db4c338e5cd0561ebe6a29a63bff2d8c20b (origin/master, master)
| Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
| Date:   Fri Nov 6 13:13:01 2020 +0900
| 
|     2nd commit from local
| 
* commit 6f1a67ee7da647baabf2a29b6e9e92f1987ce613
  Author: 山名泰生 <yamanataisei@yamanayasuonoMacBook-Pro.local>
  Date:   Fri Nov 6 13:11:50 2020 +0900
  
      1st commit from local
```

### remoteブランチへプッシュ
```
$ git push -u origin br-dev
```

Githubが以下のように更新される。

![image](https://user-images.githubusercontent.com/54575368/98982952-76cbf480-2563-11eb-8d31-aa3cae3c804b.png)


![image](https://user-images.githubusercontent.com/54575368/98982440-c100a600-2562-11eb-9b7e-23b5887f1ab1.png)

subbranchからプッシュしてリモートにプルリクエストを送信できた。

# 演習6 

### コードへのコメント

![image](https://user-images.githubusercontent.com/54575368/98986243-fe1b6700-2567-11eb-9c2a-8bc9f0b656ee.png)

## 演習7

### Danさんの講義リポジトリーをfork

<img width="465" alt="スクリーンショット 2020-11-13 4 27 57" src="https://user-images.githubusercontent.com/54575368/98986720-9e718b80-2568-11eb-8e42-fc9341811673.png">

### Forkしたリポジトリーをローカルにクローンする。
```
$ git clone https://github.com/TaiseiYamana/sysdev.myproj.git
```
### `git remote -v`を確認

```
$ git remote -v
origin  https://github.com/TaiseiYamana/sysdev.myproj.git (fetch)
origin  https://github.com/TaiseiYamana/sysdev.myproj.git (push)
```
フォークしたリポジトリー(TaiseiYamana/)にリモートが設定されているのを確認できる。


## 演習8

### 演習7でクローンしたリポジトリにex8.txtを作成し、コミットしてリモートにプッシュ
```
$ echo hogehoge > ex8.txt
$ git add ex8.txt
$ git commit -m "演習８のコミットです by Yamana"
$ git origin main
```

### 自分のフォークしたリポジトリーページからフォーク元へプルリクエストを行う
![スクリーンショット 2020-11-13 4 50 02](https://user-images.githubusercontent.com/54575368/98988989-d201e500-256b-11eb-9204-89fcfc4fa9ef.png)

### 追加コミットを促される

<img width="684" alt="スクリーンショット 2020-11-13 5 03 13" src="https://user-images.githubusercontent.com/54575368/98990310-a1bb4600-256d-11eb-9d18-ed4495c4ce4d.png">

### コードを変更して再びプルリクエスト & 承認

<img width="744" alt="スクリーンショット 2020-11-13 5 06 39" src="https://user-images.githubusercontent.com/54575368/98990618-09719100-256e-11eb-9c61-324f457e2d88.png">

