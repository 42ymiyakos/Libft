## `ft_atoi` のオーバーフローについて

<details>
<summary><b>結論: <code>int</code> の範囲外の入力に対する動作は C 規格上未定義(UB)であり、本家と結果が異なっても規格違反ではない</b></summary>

- `int` の範囲外の入力に対する `atoi` の動作は **未定義動作**(C11 §7.22.1 p1)。
- `ft_atoi` は `int` の範囲内の入力に対して、内部で一度も UB を起こさない(LP64 前提)。
- glibc の `atoi` が返す `-1` / `0` は実装の副産物であり、仕様ではない。

</details>

<details>
<summary><b>C 規格の該当箇所</b></summary>

条文番号は C11(公開ドラフト N1570)。C17 も同じ番号、C99 では §7.20.1.x。

### §7.22.1.2 — atoi は strtol と等価(エラー時を除く)

> Except for the behavior on error, they are equivalent to
> `atoi: (int)strtol(nptr, (char **)NULL, 10)`

### §7.22.1 p1 — 範囲外は UB

> The functions atof, atoi, atol, and atoll need not affect the value of the integer expression errno on an error. **If the value of the result cannot be represented, the behavior is undefined.**

`strtol` のような `LONG_MAX` へのクランプや `errno = ERANGE` の設定は、`atoi` には**要求されていない**。

### §7.22.1.4 — 正常系の手順(strtol)

1. 先頭の空白を読み飛ばす(`isspace`。"C" ロケールでは `' '` `\t` `\n` `\v` `\f` `\r` の 6 文字、§7.4.1.10)
2. 符号 `+` / `-` を **1 つだけ** 任意で受け付ける
3. 数字が続く限り読み、最初の数字でない文字で止まる
4. 数字が 1 つもなければ `0`

### §6.5 p5 — 符号付き整数のオーバーフローは UB

> If an exceptional condition occurs during the evaluation of an expression (that is, if the result is not mathematically defined or not in the range of representable values for its type), the behavior is undefined.

### §6.3.1.3 — 符号付き整数型への変換

- **p1**: 値が新しい型で表現**できる**なら、値は変わらない
- **p3**: 新しい型が符号付きで、値を表現**できない**なら、結果は **実装定義**(または実装定義のシグナルが発生する)

### 用語

| 用語 | 意味 | 例 |
|---|---|---|
| undefined behavior | 規格は何も要求しない | `atoi` の範囲外入力、符号付きオーバーフロー |
| implementation-defined | 処理系が選び、**文書化する義務**がある(§3.4.1) | 範囲外の値の符号付き型への変換 |
| unspecified | 複数の選択肢のいずれか。文書化の義務はない | 関数引数の評価順 |

</details>

<details>
<summary><b>ft_atoi の内部で何が起きるか</b></summary>

| 箇所 | 範囲内の入力 | 範囲外の入力 |
|---|---|---|
| `result = result * 10 + ...`(`long`) | オーバーフローしない | **UB が起こりうる**(§6.5 p5) |
| `return (result * sign)`(`long` → `int` の変換) | 値はそのまま(§6.3.1.3 p1) | UB ではなく **実装定義**(§6.3.1.3 p3) |

- `long` を使う理由: `INT_MAX` は `2147483647`、`INT_MIN` は `-2147483648` と非対称。符号を分けて絶対値を積み上げると、`2147483648` が `int` に収まらない。
- **LP64 前提**: 規格が `long` に保証するのは 32 ビット以上のみ。Linux / macOS (LP64) では 64 ビットだが、Windows (LLP64) では 32 ビット。
- 明示的な `(int)` キャストを付けても動作は変わらない(同じ §6.3.1.3 が適用される)。意図の表明と `-Wconversion` 対策にはなる。

</details>

<details>
<summary><b>glibc の atoi が -1 / 0 を返す理由</b></summary>

glibc の `stdlib/atoi.c` の中身は実質 1 行:

```c
return (int) strtol (nptr, (char **) NULL, 10);
```

1. `strtol` が範囲外の値を `LONG_MAX` / `LONG_MIN` にクランプする(strtol の規格どおり)
2. `(int)` への変換は実装定義。GCC / Clang は「2^N を法として変換」と文書化しているため、下位 32 ビットが残る
   - `LONG_MAX` = `0x7FFFFFFFFFFFFFFF` → 下位 32 ビットはすべて 1 → `-1`
   - `LONG_MIN` = `0x8000000000000000` → 下位 32 ビットはすべて 0 → `0`

Ubuntu / glibc 2.35 での実測:

| 入力 | `atoi` | `strtol` |
|---|---|---|
| `"2147483648"` | `-2147483648` | `2147483648` |
| `"4294967296"` | `0` | `4294967296` |
| `"9223372036854775807"` | `-1` | `LONG_MAX` |
| `"99999999999999999999"` | `-1` | `LONG_MAX` |
| `"-99999999999999999999"` | `0` | `LONG_MIN` |

他の libc(macOS など)で同じ結果になる保証はない。

</details>

<details>
<summary><b>具体例</b></summary>

| 入力 | 結果 | 理由 |
|---|---|---|
| `"  +-42"` | `0` | 2 つ目の `-` は数字ではないので停止。数字を 1 つも読んでいない |
| `"\v\f42"` | `42` | `\v` `\f` は空白として読み飛ばす |
| `"42abc"` | `42` | `a` で停止 |
| `"   "` | `0` | 数字がない |

</details>

<details>
<summary><b>根拠を確認するコマンド</b></summary>

```sh
# man(atoi の BUGS 節、strtol のクランプ、isspace の 6 文字)
man 3 atoi | col -b | grep -n -A4 -i "BUGS"
man 3 strtol | col -b | grep -n -B2 -A4 "LONG_MAX"
man 3 isspace

# C 規格(N1570 公開ドラフト)
curl -sLO https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
pdftotext -layout n1570.pdf n1570.txt
grep -n "If the value of the result cannot be represented" n1570.txt   # §7.22.1 p1
grep -n -A6 "^ *6.3.1.3" n1570.txt                                     # 符号付き変換
grep -n -B2 -A4 "exceptional condition occurs" n1570.txt               # §6.5 p5

# long のサイズ(LP64 の確認)
echo | cc -dM -E - | grep -E "__LP64__|__SIZEOF_LONG__|__SIZEOF_INT__"
```

- glibc `atoi.c`: https://sourceware.org/git/?p=glibc.git;a=blob;f=stdlib/atoi.c
- GCC 実装定義(整数): https://gcc.gnu.org/onlinedocs/gcc/Integers-implementation.html

</details>
