# kata-machine (JS/TS + C++ + Rust)

Fork of [ThePrimeagen/kata-machine](https://github.com/ThePrimeagen/kata-machine), the companion repo for the
[Frontend Masters algorithms course](https://frontendmasters.com/courses/algorithms/). Same katas and same
tests, in three languages:

| Language | Folder | Tooling |
| --- | --- | --- |
| TypeScript | `kata-js/` | [bun](https://bun.sh) (`bun test`) |
| C++23 | `kata-cpp/` | meson + ninja + clang++, with AddressSanitizer/UBSan enabled |
| Rust | `kata-rust/` | cargo (no dependencies) |

## Requirements

[`just`](https://github.com/casey/just), `bun`, `meson`, `ninja`, `clang++` (C++23) and `cargo`.

```bash
just install    # bun install inside kata-js/ (types for the editor + typecheck)
```

Tab completion for kata names and languages (`just test js Line<TAB>`): add to `~/.bashrc`

```bash
source ~/repos/algo/kata-machine/completions/just.bash
```

## Daily flow

1. Edit `katas.txt` (one kata per line, `#` comments it out). `just katas` lists every available kata.
2. Generate the day:

    ```bash
    just generate             # js, cpp and rust
    just generate cpp rust    # only those languages
    ```

    This creates `kata-js/src/dayN/`, `kata-cpp/src/dayN/` and `kata-rust/src/dayN/` with empty stubs (same N in
    every language), points the `@code/*` alias in `kata-js/tsconfig.json` at the new day and updates
    `kata-rust/src/lib.rs`.

3. Solve them and run the tests (only the katas present in the latest day run):

    ```bash
    just test                  # js (bun test)
    just test cpp              # C++  (meson test)
    just test rust             # Rust (cargo test)
    just test cpp LRU MinHeap  # only some katas
    just test-all              # all three, with a summary at the end
    ```

Stuck? Reference solutions live in `kata-js/src/golden/` (Prim's only, from upstream), `kata-cpp/golden/` and
`kata-rust/golden/` (all 29). Try first, compare after. `just test-golden` runs the C++/Rust tests against them.

Other recipes: `just clear [lang...]` deletes the `dayN` folders, `just stats` shows how many times you've
practiced each kata (from `history.log`), `just typecheck` and `just fmt`. Run `just` to list them.

## Layout

```
justfile                 every command
katas.txt                katas of the day

kata-js/
  package.json, bun.lock   dev dependencies only (typescript, @types/bun, prettier)
  tsconfig.json            the `@code/*` alias points at the current day
  scripts/                 TS stub generator + dsa.ts (signatures)
  src/__tests__/           TS tests (upstream)
  src/golden/              reference solutions
  src/dayN/                your TS solutions

kata-cpp/
  include/kata/types.hpp   Point, BinaryNode, GraphEdge, List concept...
  templates/<Kata>.hpp     stubs that generate copies
  golden/<Kata>.hpp        reference solutions
  tests/<Kata>.cpp         tests (fixtures in tests/fixtures)
  src/dayN/<Kata>.hpp      your solutions

kata-rust/
  src/types.rs             Point, BinaryNode, GraphEdge, List trait...
  src/lib.rs               generated: `code` = the current day
  templates/<kata>.rs      stubs
  golden/<kata>.rs         reference solutions
  tests/<kata>.rs          tests (fixtures in tests/common)
  src/dayN/<kata>.rs       your solutions
```

## Conventions between languages

- C++ and Rust use `snake_case`: `removeAt` → `remove_at`, `insertAt` → `insert_at`, `length` → `length()` / `len()`.
- C++: `delete` is a keyword, so `delete` methods are called `remove` (`MinHeap::remove`, `Map::remove`,
  `Trie::remove`). Rust keeps `delete`.
- "Maybe there's nothing" values: `undefined`/`null`/`-1` in TS → `std::optional` in C++ → `Option` in Rust
  (for example, `two_crystal_balls` returns `std::nullopt` / `None` instead of `-1`).
- Rust: getters (`get`, `peek`) return `Option<T>` with `T: Clone`, so you can implement lists with
  `Option<Box<Node>>`, `Rc<RefCell<..>>` or raw pointers + `unsafe`.
- C++: the build uses ASan + UBSan, so leaks, use-after-free and out-of-bounds accesses in your linked lists fail the
  test. `kata-cpp/.clangd` points clangd at `build/compile_commands.json` (run `just test cpp` once).
