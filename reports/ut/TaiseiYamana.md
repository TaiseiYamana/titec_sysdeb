# 課題1
定義した関数
```
# ２次ベクトルの内積を求める関数
def DOT(a,b):
     return a[0]*b[0]+a[1]*b[1]
```
これが正常に動くかnp.dotと比較するユニットテストをおこなった。
<img width="752" alt="スクリーンショット 2020-11-13 8 33 10" src="https://user-images.githubusercontent.com/54575368/99009214-f4572b00-258a-11eb-88a9-e61a962330a5.png">

# 課題２
Pythonのユニットテストライブラリーunittestを用いて実行してみた。

code:
```
# 1.ファイル名は「test_対象のモジュール名.py」とする
import unittest
import calc

import numpy as np

a = np.array([1,2])
b = np.array([5,4])


def DOT(a,b):
    return a[0]*b[0]+a[1]*b[1]


class TestCalc(unittest.TestCase):
  def test_dot(self):
      self.assertEqual(np.dot(a,b),DOT(a,b))
      #self.assertEqual(12,DOT(a,b))
 ```
 比較として、間違えたバージョンも加えておこなった。間違えたものはコメントアウトしているもので、入れ替えて実行します。
 
## 実行結果

<img width="723" alt="スクリーンショット 2020-11-13 10 10 37" src="https://user-images.githubusercontent.com/54575368/99015503-81ed4780-2598-11eb-9467-155b8d2fe98c.png">
このように合っているときはTru、間違っている時はFalseを表示される。

参考：https://techacademy.jp/magazine/18783

