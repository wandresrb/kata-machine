set shell := ["bash", "-euo", "pipefail", "-c"]

# languages used when none are given
langs := "js cpp rust"
cxx := env("CXX", "clang++")

# show the recipes
default:
    @just --list --unsorted

# install the js dependencies (bun, only needed for the editor/typecheck)
install:
    cd kata-js && bun install

# create the next dayN with the katas in katas.txt: `just generate` or `just generate cpp rust`
generate *only:
    #!/usr/bin/env bash
    set -euo pipefail
    day="day$(just _next-day)"
    katas=$(just _katas)
    [[ -n $katas ]] || { echo "katas.txt is empty"; exit 1; }
    for k in $katas; do
        [[ -f kata-cpp/templates/$k.hpp ]] || { echo "unknown kata: $k (see: just katas)"; exit 1; }
    done
    for lang in {{ if only == "" { langs } else { only } }}; do
        case $lang in
            js)
                (cd kata-js && bun scripts/generate.ts "$day" $katas) ;;
            cpp)
                mkdir -p "kata-cpp/src/$day"
                for k in $katas; do cp "kata-cpp/templates/$k.hpp" "kata-cpp/src/$day/"; done ;;
            rust)
                mkdir -p "kata-rust/src/$day"
                : > "kata-rust/src/$day/mod.rs"
                for k in $katas; do
                    s=$(just _snake "$k")
                    cp "kata-rust/templates/$s.rs" "kata-rust/src/$day/"
                    echo "pub mod $s;" >> "kata-rust/src/$day/mod.rs"
                done
                just _rust-day "$day" ;;
            *)
                echo "unknown language: $lang (js, cpp, rust)"; exit 1 ;;
        esac
        echo "$lang -> kata-$lang/src/$day"
    done
    for k in $katas; do echo "$(date +%F) $day $k" >> history.log; done

# run the tests of the latest day: `just test`, `just test cpp`, `just test rust LRU MinHeap`
test lang="js" *only:
    #!/usr/bin/env bash
    set -euo pipefail
    case {{lang}} in
        js) ext=.ts ;; cpp) ext=.hpp ;; rust) ext=.rs ;;
        *) echo "unknown language: {{lang}} (js, cpp, rust)"; exit 1 ;;
    esac
    n=$(just _latest-day {{lang}})
    [[ -n $n ]] || { echo "[{{lang}}] no day yet, run: just generate {{lang}}"; exit 1; }
    day="day$n"

    names=()
    for f in kata-{{lang}}/src/$day/*$ext; do
        k=$(basename "$f" $ext)
        [[ $k == mod ]] || names+=("$k")
    done
    if [[ -n "{{only}}" ]]; then
        wanted=" "
        for o in {{only}}; do
            [[ {{lang}} == rust ]] && o=$(just _snake "$o")
            wanted+="$o "
        done
        filtered=()
        for k in "${names[@]}"; do [[ $wanted == *" $k "* ]] && filtered+=("$k"); done
        names=("${filtered[@]}")
    fi
    (( ${#names[@]} )) || { echo "[{{lang}}] nothing to test"; exit 1; }
    echo "[{{lang}}] $day: ${names[*]}"

    case {{lang}} in
        js)
            args=()
            for k in "${names[@]}"; do args+=("./src/__tests__/$k.ts"); done
            cd kata-js && bun test "${args[@]}" ;;
        cpp)
            cd kata-cpp
            katas=$(IFS=,; echo "${names[*]}")
            if [[ -f build/build.ninja ]]; then
                meson configure build -Dday="$day" -Dkatas="$katas"
            else
                CXX={{cxx}} meson setup build -Dday="$day" -Dkatas="$katas"
            fi
            meson test -C build --print-errorlogs ;;
        rust)
            just _rust-day "$day"
            args=()
            for k in "${names[@]}"; do args+=(--test "$k"); done
            cd kata-rust && cargo test "${args[@]}" ;;
    esac

# run js, cpp and rust and print a summary
test-all *only:
    #!/usr/bin/env bash
    status=0
    summary=""
    for lang in {{langs}}; do
        if just test "$lang" {{only}}; then summary+="  $lang\tpass\n"; else summary+="  $lang\tFAIL\n"; status=1; fi
    done
    printf "\nsummary:\n$summary"
    exit $status

# delete every dayN (all languages, or only the ones given)
clear *only:
    #!/usr/bin/env bash
    set -euo pipefail
    for lang in {{ if only == "" { langs } else { only } }}; do
        for d in kata-$lang/src/day[0-9]*; do
            [[ -d $d && $d != */day0 ]] || continue
            echo "deleting $d"
            rm -rf "$d"
        done
        if [[ $lang == rust ]]; then just _rust-day day0; fi
    done

# list every available kata
katas:
    @ls kata-cpp/templates | sed 's/\.hpp$//'

# how many times you've practiced each kata
stats:
    @[ -f history.log ] && awk '{print $3}' history.log | sort | uniq -c | sort -rn || echo "no history yet"

# typecheck the js katas
typecheck:
    cd kata-js && bunx tsc --noEmit

# format js (prettier) and rust (cargo fmt)
fmt:
    cd kata-js && bunx prettier --write src scripts
    cd kata-rust && cargo fmt

[private]
_katas:
    @grep -vE '^[[:space:]]*(#|$)' katas.txt | awk '!seen[$1]++ {print $1}' | xargs

[private]
_next-day:
    @{ ls -d kata-*/src/day[0-9]* 2>/dev/null || true; } | awk -F/day '$NF + 0 > m {m = $NF + 0} END {print m + 1}'

[private]
_latest-day lang:
    @{ ls -d kata-{{lang}}/src/day[0-9]* 2>/dev/null || true; } | awk -F/day '$NF + 0 > m {m = $NF + 0} END {if (m) print m}'

# "DFSOnBST" -> "dfs_on_bst", "BTBFS" -> "bt_bfs"
[private]
_snake name:
    @echo {{name}} | sed -E 's/^BTBFS$/BT_BFS/; s/([A-Z]+)([A-Z][a-z])/\1_\2/g; s/([a-z0-9])([A-Z])/\1_\2/g' | tr '[:upper:]' '[:lower:]'

# point kata-rust/src/lib.rs at a day
[private]
_rust-day day:
    @printf '%s\n' 'pub mod types;' '' '#[path = "{{day}}/mod.rs"]' '#[allow(unused_variables, unused_mut, dead_code, unused_imports, clippy::new_without_default)]' 'pub mod code;' > kata-rust/src/lib.rs
