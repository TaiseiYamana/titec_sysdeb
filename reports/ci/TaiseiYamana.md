# 継続的インテグレーション
2020年11月13日（金）

## 演習1
### 1つめ URL:https://github.com/galek/galek.github.io/blob/master/.circleci/config.yml
docker imageのセットアップ`- image: circleci/node:10.0.0`
gcc のインストール `command: 'sudo apt install gcc'`

記述が違うだけでlinuxのコマンドが多い。それはdockerのimageによって異なるが、linuxのコマンドが実行できるimageのセットが操作しすそうである。

### 2つめ　URL:https://github.com/elmariachi111/openzeppelin-sdk/blob/master/.circleci/config.yml
java scriptの場合では`command: yarn`が実行されている。

## 演習2

公式の入門ガイド:https://circleci.com/docs/ja/2.0/getting-started/
を元に実行。

### .yml ファイルを追加
Githubのリポジトリの`[Create new file]`で次の内容で`.circleci/config.yml `を作成

入門ガイドの`echo "A first hello"`を`echo "hello , world"`に変更

```
 version: 2
 jobs:
   build:
     docker:
       - image: circleci/ruby:2.4.1
     steps:
       - checkout
       - run: echo "hello , world"
```
### CircleCI 準備
1. CircleCIの[登録ページ](https://circleci.com/ja/signup)でGitHubアカウントでログイン
2. リポジトリを CircleCI にセットアップ

### Github側でコミットを行う。
`.circleci/config.yml `をコミット

### CircleCI側のログを確認
<img width="1422" alt="スクリーンショット 2020-11-14 14 48 26" src="https://user-images.githubusercontent.com/54575368/99140822-76794980-2688-11eb-9790-37206c58ed25.png">

CircleCIのログに`"hello, world"`を表示させられた


## 演習3
前回作成したpythonのunittestを実施するコードをCircleCIで実施させる。CircleCIでpythonを動かすための`config.yml`の設定はhttps://qiita.com/noracorn92/items/e879827aa1cc72c370df を参考にした。

### リポジトリーにコードをアップロード
#### testut.py
```
import unittest
import numpy as np

a = np.array([1,2,4])
b = np.array([5,4,6])


def CROSS(A,B):
    C = np.array([0,0,0])
    C[0] = A[1]*B[2]-B[1]*A[2]
    C[1] = -1*(A[0]*B[2]-B[0]*A[2])
    C[2] = A[0]*B[1]-B[0]*A[1]
    return C
class TestCalc(unittest.TestCase):
  def test_cross(self):
      self.assertEqual(np.cross(a, b)[0],CROSS(a,b)[0])
      self.assertEqual(np.cross(a, b)[1],CROSS(a,b)[1])
      self.assertEqual(np.cross(a, b)[2],CROSS(a,b)[2])
```


### `circleci/config.yml `の作成
次の内容の`.circleci/config.yml `を作成

```
 version: 2
 jobs:
   build:
     docker:
       - image: python:3
     steps:
       - checkout
       - run:
           command: python -m unittest
```
実行するコードに合わせて`- image:`を変更する。

### CircleCI側のログを確認
テストを成功した場合と失敗した場合を比較

#### 成功した時
<img width="1409" alt="スクリーンショット 2020-11-14 15 18 29" src="https://user-images.githubusercontent.com/54575368/99141238-b7735d00-268c-11eb-842d-67229387ebf4.png">

#### 失敗した時
`self.assertEqual(np.cross(a, b)[1],CROSS(a,b)[1])`を`self.assertEqual(np.cross(a, b)[0],CROSS(a,b)[1])`として実行

<img width="1416" alt="スクリーンショット 2020-11-14 15 23 31" src="https://user-images.githubusercontent.com/54575368/99141292-5dbf6280-268d-11eb-83b3-9ebd2e036227.png">

<img width="1424" alt="スクリーンショット 2020-11-14 15 20 35" src="https://user-images.githubusercontent.com/54575368/99141256-f43f5400-268c-11eb-8170-5c2c102f9c87.png">
テストに失敗した場合、CircleCI側ではビルド失敗の扱いになるため、テスト失敗を確認しやすいようになっている。

## 演習4
[公式のガイド](https://circleci.com/docs/ja/2.0/artifacts/)を基に実行

### `HelloWorld.c`をリポジトリーにコミットする。

#### ``HelloWorld.c`
```
#include <stdio.h>

int main(int argc, char *args[])
{
    printf("Hello, world!\n");
    return 0;
}
```
### `circleci/config.yml `の設定
#### `circleci/config.yml`
```
version: 2
jobs:
  build:
    docker:
      - image: python:3
      - image: gcc:8.1.0
      
    steps:
      - checkout
      - run:
          command: pip install numpy
      - run: 
          command: python -m unittest
          
      - run: gcc -o HelloWorld HelloWorld.c
      - run:
          command: mkdir artifacts ; mv HelloWorld artifacts/
                    
      - store_artifacts:
          PATH: ./artifacts
          destination: artifact-file
```
`- run: gcc -o HelloWorld HelloWorld.c`を追加するとカレントディレクトリー上に`HelloWorld`が生成される。

アーティファクトを保存するには、`- store_artifacts`項を追加。

`PATH`はアーティファクトとしてアップロードするディレクトリのパスであるが、参照したディレクトリーのパス内にある全てのファイルがアップロードされてしまう。  
ビルド生成物のみをアーティファクトとして保存するには、アーティファクト用のディレクトリーを一時的に作成、ビルド生成物をそこに移動が必要である。  
ここで`command: mkdir artifacts ; mv HelloWorld artifacts/`追記。

そして`PAHT`に作成したディレクトリーのパスを入れる。

### 結果

<img width="1395" alt="スクリーンショット 2020-11-14 16 01 32" src="https://user-images.githubusercontent.com/54575368/99141863-ad545d00-2692-11eb-98ff-04e65360cd88.png">

<img width="1418" alt="スクリーンショット 2020-11-14 16 01 58" src="https://user-images.githubusercontent.com/54575368/99141872-bcd3a600-2692-11eb-8539-83f1b7f1d1c1.png">

artifactsがアップロードされたことを確認できた。
