*This project has been created as part of the 42 curriculum by ymiyakos.*

# Libft

## Description

このプロジェクトは、自分専用の C ライブラリ `libft.a` を作る課題である。標準 C ライブラリ(libc)の関数を自分で実装してその仕組みを理解し、以降の42の課題で使える汎用関数群を用意することを目的とする。

ライブラリは次の3つで構成される。

- Part 1: libc の関数の再実装
- Part 2: libc にない、または異なる形で提供される追加関数
- Part 3: 連結リスト(`t_list`)の操作関数

### Library overview

#### Part 1 - Libc functions

| Function | Description |
| --- | --- |
| `ft_isalpha` | アルファベットであるかを判定する |
| `ft_isdigit` | 数字であるかを判定する |
| `ft_isalnum` | アルファベットまたは数字であるかを判定する |
| `ft_isascii` | ASCII であるかを判定する |
| `ft_isprint` | 表示できる文字であるかを判定する |
| `ft_strlen` | `s` の長さ(終端文字を含まない)を返す |
| `ft_memset` | `s` の先頭から `n` バイトを `c` で埋める |
| `ft_bzero` | `s` の先頭から `n` バイトを、値が 0 のバイトで埋める |
| `ft_memcpy` | `src` から `dst` へ `n` バイトをコピーする(領域の重なりは考慮しない) |
| `ft_memmove` | `memcpy` と同様にコピーするが、`dst` と `src` が重なっていても正しくコピーできる |
| `ft_strlcpy` | `src` を `dst` へ、終端文字を含めて `size` バイトに収まる範囲でコピーし、`src` の長さを返す |
| `ft_strlcat` | `dst` の末尾に `src` を、終端文字を含めて `size` バイトに収まる範囲で結合し、結合しようとした全長を返す(`size` が `dst` の長さより小さい場合は、`size` と `src` の長さの和を返す) |
| `ft_toupper` | アルファベットの小文字を大文字に変換する |
| `ft_tolower` | アルファベットの大文字を小文字に変換する |
| `ft_strchr` | `s` の中で `c` が最初に現れる位置を返す(`c` が `'\0'` のときは終端文字の位置を返す。見つからなければ NULL) |
| `ft_strrchr` | `s` の中で `c` が最後に現れる位置を返す(`c` が `'\0'` のときは終端文字の位置を返す。見つからなければ NULL) |
| `ft_strncmp` | `s1` と `s2` を先頭から最大 `n` 文字比較し、`s1` が小さければ負、等しければ0、大きければ正の値を返す |
| `ft_memchr` | `s` の先頭から `n` バイトの範囲で、`c` が最初に現れる位置を返す(見つからなければ NULL) |
| `ft_memcmp` | `s1` と `s2` を先頭から `n` バイト比較し、`s1` が小さければ負、等しければ0、大きければ正の値を返す |
| `ft_strnstr` | `big` の先頭から `len` 文字の範囲で `little` を探し、最初に見つかった位置を返す(見つからなければ NULL) |
| `ft_atoi` | 文字列の数字を `int` に変換する |
| `ft_calloc` | `size` バイトの要素 `nmemb` 個分のメモリ領域を確保し、値が 0 のバイトで埋める |
| `ft_strdup` | `s` の複製を `malloc` で作成する |

#### Part 2 - Additional functions

| Function | Description |
| --- | --- |
| `ft_substr` | `s` のインデックス `start` から最大 `len` 文字を抽出した文字列を作成する(確保に失敗したら NULL) |
| `ft_strjoin` | `s1` と `s2` を結合した文字列を作成する(確保に失敗したら NULL) |
| `ft_strtrim` | `set` に含まれる文字を `s1` の先頭と末尾から取り除いた文字列を作成する(確保に失敗したら NULL) |
| `ft_split` | `s` を `c` を区切り文字として分割し、分割した文字列を格納した NULL 終端の配列を返す(確保に失敗したら NULL) |
| `ft_itoa` | `n` を文字列に変換する(確保に失敗したら NULL) |
| `ft_strmapi` | `s` の各文字に関数 `f` を適用した文字列を作成する(確保に失敗したら NULL) |
| `ft_striteri` | `s` の各文字に関数 `f` を適用する(文字列は作らず、各文字のアドレスを `f` に渡すので、文字そのものを書き換えられる) |
| `ft_putchar_fd` | `c` をファイルディスクリプタ `fd` に出力する |
| `ft_putstr_fd` | `s` をファイルディスクリプタ `fd` に出力する |
| `ft_putendl_fd` | `s` をファイルディスクリプタ `fd` に出力し、続けて改行を出力する |
| `ft_putnbr_fd` | `n` をファイルディスクリプタ `fd` に出力する |

#### Part 3 - Linked list

| Function | Description |
| --- | --- |
| `ft_lstnew` | `content` を保持し、`next` が NULL のノードを作成する(確保に失敗したら NULL) |
| `ft_lstadd_front` | `lst` の先頭に `new` を追加する |
| `ft_lstsize` | `lst` のノードの数を返す |
| `ft_lstlast` | `lst` の末尾のノードを返す |
| `ft_lstadd_back` | `lst` の末尾に `new` を追加する |
| `ft_lstdelone` | `lst` の `content` に関数 `del` を適用し、ノード自身も解放する(次のノードは解放しない) |
| `ft_lstclear` | `lst` 以降の全てのノードについて、`del` で `content` を解放し、ノード自身も解放して、最後に `*lst` を NULL にする |
| `ft_lstiter` | `lst` の各ノードの `content` に関数 `f` を適用する |
| `ft_lstmap` | `lst` の各ノードの `content` に関数 `f` を適用した新しいリストを作成する(確保に失敗したら、必要に応じて `del` で解放して NULL) |

## Instructions

### Compilation

リポジトリのルートで `make` を実行すると、静的ライブラリ `libft.a` が作られる。

```sh
make          # libft.a を作成
make clean    # オブジェクトファイル(*.o)を削除
make fclean   # オブジェクトファイルと libft.a を削除
make re       # fclean してから再ビルド
```

コンパイラは `cc`、フラグは `-Wall -Wextra -Werror`。

### Installation

自分のプログラムで使うときは、`libft.h` を include して `libft.a` をリンクする。

```c
#include "libft.h"

int	main(void)
{
	ft_putendl_fd("Hello, libft!", 1);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror -I<path/to/libft> main.c -L<path/to/libft> -lft -o a.out
```

### Execution

```sh
./a.out
```

テストは `test/` ディレクトリで実行する(AddressSanitizer と `libbsd` を使用するため、Linux 環境を想定)。

```sh
cd test
make run
```

## Resources

### References

- [const ＝定数(読み込み専用)と思い込むのはもうやめよう](https://qiita.com/mizcii/items/35df2bceac67a75f75dd)
- [AddressSanitizer (google/sanitizers wiki)](https://github.com/google/sanitizers/wiki/AddressSanitizer)
- [単体テストでの expected / actual などの意味について📝](https://zenn.dev/manase/scraps/066f21a5779439)
- [【C言語入門】memcpyとmemmoveの使い方｜メモリをコピーする方法【2026年版】](https://mogachan.net/clangmemcpy/)
- [汎用ポインタ型との相互の型変換](https://c.perlzemi.com/blog/20210223131724.html)
- [Linux man-pages (man7.org)](https://man7.org/linux/man-pages/) : Part 1 の各関数の仕様(`man 3 <関数名>`)
- [ISO/IEC 9899:2011 (C11) 公開ドラフト N1570](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) : 未定義動作の根拠

### Use of AI

#### Part 1, 2, 3

- 実装方針の相談
- エッジケースの指摘(直接的な答えを教わらず、気づきを促す形で)

#### `test/`

- テストケースの相談
- テスト用関数の作成(全て確認済み)

#### README

- README の雛形づくり
- 関数名の一覧づくり
- 説明文の誤字・表記・曖昧さの指摘と修正
- Technical choices 節の下書きと、C11 の引用

## Technical choices

### Part 1 - man page に忠実に実装する

Part 1 は libc の再実装であり、subject は挙動を man page に従うよう求めている。

> Your version will have the same prototypes and behaviors as the originals, adhering strictly to their definitions in the man page.
>
> — Subject, IV.2 Part 1 - Libc functions

一方で、subject は関数が予期せず終了することを禁じているが、未定義動作はその例外としている。

> Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc.) except for undefined behavior.
>
> — Subject, II Common Instructions

そのため Part 1 では、man page に定義された挙動はそのとおりに実装する。man page や C 規格で未定義とされている入力については、本家の挙動を再現することを目的としていない。

#### 再現していない未定義動作の例

- `ft_atoi`: `int` で表せない値になる入力(例: `"2147483648"`, `"99999999999999999999"`)。
  C 規格では未定義動作であり、本家(glibc)の戻り値は実装の副産物にすぎない。

  > If the value of the result cannot be represented, the behavior is undefined.
  >
  > — ISO/IEC 9899:2011 (C11) §7.22.1 p1

- `ft_is*`, `ft_toupper`, `ft_tolower`: `unsigned char` で表せず、`EOF` でもない値(例: `100000`)。
  規格上は未定義動作であり、本家は実装によってはクラッシュしうる。
  こちらは範囲を比較するだけで、範囲外の値でもクラッシュせず、`0` または入力そのままを返す。

  > In all cases the argument is an int, the value of which shall be representable as an unsigned char or shall equal the value of the macro EOF. If the argument has any other value, the behavior is undefined.
  >
  > — ISO/IEC 9899:2011 (C11) §7.4 p1

いずれも subject の「`except for undefined behavior`」の範囲内であり、再現しなくても要件を満たすと判断した。

### Part 2, 3 - クラッシュさせない

Part 2, 3 は libc に存在しない(または異なる形の)42独自要件の関数で、参照できる man page がない。このため「未定義動作」を理由にクラッシュすることは認めず、上記の Common Instructions に従って、想定外の入力でも予期せず終了しないように実装する。

