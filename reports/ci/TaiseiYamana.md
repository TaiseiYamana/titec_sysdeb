# 継続的インテグレーション
2020年11月13日（金）

## 演習1

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
### CircleCI でビルドを準備
#### 1. CircleCIの[登録ページ](https://circleci.com/ja/signup)でGitHubアカウントでログイン
#### 2. 作成したリポジトリを CircleCI の新しいプロジェクトとして追加
## 演習3
