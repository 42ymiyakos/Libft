*This project has been created as part of the 42 curriculum by <login>.*

# Libft

## Description

このプロジェクトでは、プログラムで使用するための汎用関数を含むCライブラリをコーディングする。

### Library overview

<!-- Libft課題の要件: 作成したライブラリの詳細な説明 -->

#### Part 1 - Libc functions

| Function | Description |
| --- | --- |
| `ft_isalpha` | アルファベットであるかを判定する |
| `ft_isdigit` | 数字であるかを判定する |
| `ft_isalnum` | アルファベットまたは数字であるかを判定する |
| `ft_isascii` | ASCIIであるかを判定する |
| `ft_isprint` | 表示できる文字であるかを判定する |
| `ft_strlen` | `s` の長さ(終端文字を含まない)を返す |
| `ft_memset` | `s` の先頭から `n` バイトを `c` で埋める |
| `ft_bzero` | `s` の先頭から `n` バイトを0バイトで埋める |
| `ft_memcpy` | `src` から `dst` へ `n` バイトをコピーする(領域の重なりは考慮しない) |
| `ft_memmove` | `memcpy` と同様にコピーするが、`dst` と `src` が重なっていても正しくコピーできる |
| `ft_strlcpy` | `src` を `dst` へ、終端文字を含めて `size` バイトに収まる範囲でコピーし、`src` の長さを返す |
| `ft_strlcat` | `dst` の末尾に `src` を、終端文字を含めて `size` バイトに収まる範囲で結合し、結合しようとした全長を返す(`size` が `dst` の長さより小さい場合は、`size` と `src` の長さの和を返す) |
| `ft_toupper` | アルファベットの小文字を大文字に変換する |
| `ft_tolower` | アルファベットの大文字を小文字に変換する |
| `ft_strchr` | `s` の中で `c` が最初に現れる位置を返す(`c` が `'\0'` のときは終端文字の位置を返す。見つからなければNULL) |
| `ft_strrchr` | `s` の中で `c` が最後に現れる位置を返す(`c` が `'\0'` のときは終端文字の位置を返す。見つからなければNULL) |
| `ft_strncmp` | `s1` と `s2` を先頭から最大 `n` 文字比較し、`s1` が小さければ負、等しければ0、大きければ正の値を返す |
| `ft_memchr` | `s` の先頭から `n` バイトの範囲で、`c` が最初に現れる位置を返す(見つからなければNULL) |
| `ft_memcmp` | `s1` と `s2` を先頭から `n` バイト比較し、`s1` が小さければ負、等しければ0、大きければ正の値を返す |
| `ft_strnstr` | `big` の先頭から `len` 文字の範囲で `little` を探し、最初に見つかった位置を返す(見つからなければNULL) |
| `ft_atoi` | 文字列の数字をint型に変換する |
| `ft_calloc` | `size` バイトの要素 `nmemb` 個分のメモリ領域を確保し、0バイトで埋める |
| `ft_strdup` | `s` の複製を `malloc` で作る |

#### Part 2 - Additional functions

| Function | Description |
| --- | --- |
| `ft_substr` | `s` のインデックス `start` から最大 `len` 文字を抽出した文字列を作成する(確保に失敗したらNULL) |
| `ft_strjoin` | `s1` と `s2` を結合した文字列を作成する(確保に失敗したらNULL) |
| `ft_strtrim` | `set` に含まれる文字を `s1` の先頭と末尾から取り除いた文字列を作成する(確保に失敗したらNULL) |
| `ft_split` | `s` を `c` を区切り文字として分割し、分割した文字列を格納したNULL終端の配列を返す(確保に失敗したらNULL) |
| `ft_itoa` | `n` を文字列に変換する(確保に失敗したらNULL) |
| `ft_strmapi` | `s` の各文字に関数 `f` を適用した文字列を作成する(確保に失敗したらNULL) |
| `ft_striteri` | `s` の各文字に関数 `f` を適用する(文字列は作らず、各文字のアドレスを `f` に渡すので、文字そのものを書き換えられる) |
| `ft_putchar_fd` | `c` をファイルディスクリプタ `fd` に出力する |
| `ft_putstr_fd` | `s` をファイルディスクリプタ `fd` に出力する |
| `ft_putendl_fd` | `s` をファイルディスクリプタ `fd` に出力し、続けて改行を出力する |
| `ft_putnbr_fd` | `n` をファイルディスクリプタ `fd` に出力する |

#### Part 3 - Linked list

| Function | Description |
| --- | --- |
| `ft_lstnew` | 新たにノードを作成する |
| `ft_lstadd_front` | リストの先頭にノードを繋げる |
| `ft_lstsize` | リストの長さを返す |
| `ft_lstlast` | リストの最後のノードを返す |
| `ft_lstadd_back` | リストの最後にノードを繋げる |
| `ft_lstdelone` | 引数として渡されたノードの `content` に関数 `del` を適用し、ノードも開放する |
| `ft_lstclear` | リストを削除する |
| `ft_lstiter` | 引数として渡されたリストの各ノードに関数 `f` を適用する |
| `ft_lstmap` | 引数として渡されたリストの各ノードに関数 `f` を適用した新しいリストを作成する |

## Instructions

### Compilation

### Installation

### Execution

## Resources

### References

-

### Use of AI

<!-- どのタスク・どの部分でAIを使ったか -->

<!-- 任意の追加セクション(必要なら): Usage examples / Technical choices / Testing など -->
