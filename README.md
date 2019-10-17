# MieruEMB

## 開発環境(Windows10)
| ソフトウェア | バージョン |
| - | - |
| WSL(Ubuntu) | 18.04.2 LTS (Bionic Beaver) |
| gcc(Target: x86_64-linux-gnu) | 7.4.0 |
| make | 4.1 |
| mtools | 4.0.18 |
| QEMU | 3.1.50 |

## QEMUの使い方
- `make qemu`でビルド
- run.batを実行（環境により異なる）
- ウィンドウが立ち上がる
	- 画面（320*200）左上にLCD画面（128*128）が表示される
	- `Q`,`W`,`E`がMieruEmbのそれぞれのスイッチに対応している

## この環境の使い方
- 上記のソフトウェアをインストール
	- 環境によっては`i386-elf-gcc`等が必要
- 下の表のようにファイルの内容を変更

| ファイル | 箇所 | 変更内容 |
| - | - | - |
| qemu_programs/Makefile | PREFIX =  | クロスコンパイルを行う場合、右辺に適当な文字列を入力 |
|  | SRCS += | 必要なソースファイルの分だけ、この行を追加または削除 |
|  | TARGET = | 完成するイメージファイルのファイル名なので適当に変更 |
| 任意のファイル |  | `define.h`の4～12行目を（main.cなどに）追加 |
|  | `mylib_msleep()` | `mylib.c`の`mylib_msleep()`の内容に置き換える  |
|  | 任意の関数 | `128`を`LCD_WIDTH`に変更（`mylib.c`を参照） |


## 参考
### リンカに関する参考
- undefined reference
	- https://qiita.com/kazatsuyu/items/5c8d9f539cd925fda007
- http://hrb.osask.jp/wiki/?tools/nask
- http://tatsumack.hatenablog.com/entry/2017/03/24/225706
	- https://github.com/tatsumack/hikari-os/commit/ab4b5d483e32b52d04e40306acd4d44e71672fcf#diff-eb6a04b3ca5299b66b570245eaa58c18R67
- overlaps
	- https://github.com/tyfkda/haribote/issues/1 
### edimgに関する参考
- mtools
	- http://cyberbird.indiesj.com/x86%E3%80%80os%E8%87%AA%E4%BD%9C%E5%85%A5%E9%96%80/?pageNo=3
### アセンブラでnasmからGNUに変更する
- https://github.com/horie-t/Aomushi

