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

#　演習3

## 作りたい関数：3次ベクトルの外積
### 第一回ユニットテスト
```
import unittest
import calc

import numpy as np

a = np.array([1,2,4])
b = np.array([5,4,6])


def CROSS(A,B):
    return (A[2]*B[3]+A[3]*B[2])-(A[1]*B[3]+A[3]*B[1])+(A[1]*B[2]+A[2]*B[1])

class TestCalc(unittest.TestCase):
  def test_cross(self):
      self.assertEqual(np.cross(a, b),CROSS(a,b))
```

テスト実行

```
$ Python -m unittest
```

結果
```
======================================================================
ERROR: test_cross (testut.TestCalc)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "/Users/yamanataisei/Documents/jupyter-notebook/OSSproject/testut.py", line 18, in test_cross
    self.assertEqual(np.cross(a, b),CROSS(a,b))
  File "/Users/yamanataisei/Documents/jupyter-notebook/OSSproject/testut.py", line 12, in CROSS
    return (A[2]*B[3]+A[3]*B[2])-(A[1]*B[3]+A[3]*B[1])+(A[1]*B[2]+A[2]*B[1])
IndexError: index 3 is out of bounds for axis 0 with size 3

----------------------------------------------------------------------
Ran 1 test in 0.000s

FAILED (errors=1)
```
うまくいっていない。インデックス３が参照外であるというメッセージがでている。
np.arrayのインデックスの開始は0からであるので、すべてのインデックスを-1にしてもう一度テスト実行する。

## 第二回ユニットテスト
訂正後
```
def CROSS(A,B):
    return (A[1]*B[2]+A[2]*B[1])-(A[0]*B[2]+A[2]*B[0])+(A[0]*B[1]+A[1]*B[0])
```

テスト結果

```
======================================================================
ERROR: test_cross (testut.TestCalc)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "/Users/yamanataisei/Documents/jupyter-notebook/OSSproject/testut.py", line 16, in test_cross
    self.assertEqual(np.cross(a, b),CROSS(a,b))
  File "/Users/yamanataisei/.pyenv/versions/3.9.0/lib/python3.9/unittest/case.py", line 831, in assertEqual
    assertion_func(first, second, msg=msg)
  File "/Users/yamanataisei/.pyenv/versions/3.9.0/lib/python3.9/unittest/case.py", line 821, in _baseAssertEqual
    if not first == second:
ValueError: The truth value of an array with more than one element is ambiguous. Use a.any() or a.all()

----------------------------------------------------------------------
Ran 1 test in 0.003s

FAILED (errors=1)
```

## 第３回ユニットテスト
訂正後
```
def CROSS(A,B):
    C = np.array([0,0,0])
    C[0] = A[1]*B[2]-B[1]*A[2]
    C[1] = -1*(A[0]*B[2]-B[0]*A[2])
    C[2] = A[0]*B[1]-B[0]*A[1]
    return C
```

テスト結果

```
F
======================================================================
FAIL: test_cross (testut.TestCalc)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "/Users/yamanataisei/Documents/jupyter-notebook/OSSproject/testut.py", line 19, in test_cross
    self.assertEqual(np.cross(a, b).all,CROSS(a,b).all)
AssertionError: <built-in method all of numpy.ndarray object at 0x117b166c0> != <built-in method all of numpy.ndarray object at 0x117b168f0>

----------------------------------------------------------------------
Ran 1 test in 0.000s
```

jupyter notebookで確認したが、値が同じだったがエラーが生じてしまった。調べてみるとこれは多次元配列の比較がうまくいかないらしい。
今回の様な小さい配列だと要素を取り出して、比較できるのでそちらを行う。実践的に考えると大きい行列の比較をすると思うので、実践向きではない、解決策を考えなければいけない。

##　第４回ユニットテスト

訂正後　テストコード側
```
import unittest
import calc

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

結果
```
(testenv) yamanayasuonoMacBook-Pro:OSSproject yamanataisei$ Python -m unittest
.
----------------------------------------------------------------------
Ran 1 test in 0.000s

OK
```
となり、うまく関数ができていた。
