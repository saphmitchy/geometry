# geometry

競技プログラミングのための幾何ライブラリ

## ファイル構成
- [src](src) -- ライブラリソースファイル
- [test](test) -- テストコード
- [AOJ](AOJ) -- Aizu Online Judge での verify 用提出コード
  - [expander.py](AOJ/expander.py) -- ライブラリを展開するスクリプト

## テストについて
[CMake](https://cmake.org) と [Google test](https://github.com/google/googletest)  を利用しています。
また、テストカバレッジのために [LCOV](https://github.com/linux-test-project/lcov) を利用しています。
テストには CMake と LCOV が必要なので、適宜インストールしてください。
```
./run_test
```
などで実行できます。
