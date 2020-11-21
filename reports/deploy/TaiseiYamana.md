# 演習１
## 適当なブランチの作成&foo.txtのコミット&リモートへプッシュ
```
$ git branch gitpage2
$ git checkout gitpage2

$ echo "hogehoge" > foo.txt
$ git add --all
$ git commit -m "Initial commit"

$ git push -u origin gitpage2
```

## github側のセッティング
Github pagesでリポジトリーのファイルをwebページとして表示するには、リポージトリーの設定でgithub pagesのソースを目的のリポジトリーにセッティングする。

ここではgitpage2というブランチを参照したいので、ソースをgitpage2に設定。

![スクリーンショット 2020-11-20 14 55 09](https://user-images.githubusercontent.com/54575368/99874563-456ebb00-2c2c-11eb-9cb0-23905a77d0fe.png)

## 表示方法と結果
そのあと、github pagesの設定に表示されているURLがリポジトリーのルートを参照している。`foo.txt`をURLに加えてブラウザで検索すると、リポジトリー内のfoo.txtが表示される。

![スクリーンショット 2020-11-20 14 55 03](https://user-images.githubusercontent.com/54575368/99874773-b367b200-2c2d-11eb-951f-473659923c79.png)

# 演習2
## `ssh key-gen`で秘密鍵、公開鍵を取得
```
$ ssh-keygen -m PEM -t rsa -C "mit.yamatai@gmail.com"

nter file in which to save the key (/Users/yamanataisei/.ssh/id_rsa): ./id_rsa
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in ./id_rsa.
Your public key has been saved in ./id_rsa.pub.
```
カレントディレクトリに秘密鍵`id_rsa`と公開鍵`id_rsa.pub`を生成

## 公開鍵をgithubに登録
目的のリポジトリの設定から`Deploy Keys`の項目を開き、先ほど作成した公開鍵を登録
<img width="982" alt="スクリーンショット 2020-11-21 19 29 47" src="https://user-images.githubusercontent.com/54575368/99875060-ef9c1200-2c2f-11eb-8e6c-25cbdc2d2160.png">

## 秘密鍵をCircle Ciに登録
[サイドメニュー]→[projects]→[目的のリポジトリの選択]→[project settings]→[SSH Keys]→[Additional SSH Keys]→[Add SHH key]

<img width="1015" alt="スクリーンショット 2020-11-21 19 52 07" src="https://user-images.githubusercontent.com/54575368/99875437-10199b80-2c33-11eb-9cba-fd637668f33d.png">

Fingerprintををコピーする。

## Fingerprintを.circleci/config.ymlに登録

# 演習3
# Pip installの操作
### 理由：
最新のバージョンのモジュールが入ってしまうため、タイミングによっては違うバージョンがインストールされる。

# Git clone 
### 理由：
Clone元が変わると変化してしまう。
