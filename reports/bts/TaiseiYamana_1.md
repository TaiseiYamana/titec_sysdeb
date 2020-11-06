# 演習１

私は研究の作業中にUbuntuOSのログインループバグを発生させてしまったのでその際に調べたものを確認した。

多くの場合公式のサイトより、解決策を別の掲示板のせて投稿するものをよく見た。


次にtensorflowのバグについて調べたところOSSがGithubに公開されているのでBTSはGithub Issuesを使用していた

URL: https://github.com/tensorflow

# 演習2
## 良い例：
URL: https://github.com/tensorflow/tensorflow/issues/44386  
この様にシステムインフォメーションとして環境やエラーログの詳細を載せてバグを説明している。その時の再現が可能な説明をするように報告ができていると良いバグ報告であると思われる。  
それに加えてバグ報告見えやすくするのも必要である。Github Issue はMark Down形式であるのでログなどは埋め込みコードなどでまとめる工夫が必要である。


## 悪い例：
URL: https://github.com/tensorflow/tensorflow/issues/44339  
悪い例を考えるとすると、良い例とは別にシステムインフォメーションやエラーログの記述が不十分で再現が難しい報告が悪い例であると思われる。  
Github Issue はMark Down形式などでログなどは埋め込みコードなどでまとめる

# 演習3
## 準備：
簡単なOSS　test.txt　を作成

![image](https://user-images.githubusercontent.com/54575368/98326300-4270a980-2034-11eb-93a0-a5febf8b7f37.png)

## Issueの投稿

![image](https://user-images.githubusercontent.com/54575368/98326364-69c77680-2034-11eb-8ef3-6c45fc2f54dc.png)

Issueの番号が36と割り当てられる。

## バグに対してのコミット
![image](https://user-images.githubusercontent.com/54575368/98326556-e195a100-2034-11eb-8640-815f5de4a592.png)

![image](https://user-images.githubusercontent.com/54575368/98326389-7c41b000-2034-11eb-8d3d-08ab6e92ff16.png)

## 自動的にクローズ
![image](https://user-images.githubusercontent.com/54575368/98326638-038f2380-2035-11eb-9b01-c7b2fc9bee2e.png)

今回自動的にクローズができなかった。
https://qiita.com/gotohiro55/items/aac51b2b3b0a8b37cebb によると　　
masterにマージされないと自動的にクローズされないらしいです。今回は授業用のリポジトリ内で実行したため、自分のアカウントの持つリポジトリーでないとできないということがわかりました。
maseterをアクティベートしている自分のアカウントのリポジトリーで時間があったら後で実行してみます。

