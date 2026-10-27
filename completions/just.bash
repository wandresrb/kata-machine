# Tab completion for kata names and languages in `just`, on top of just's own completion.
#   just test <TAB>           -> js cpp rust
#   just test js Line<TAB>    -> LinearSearchList
#   just generate <TAB>       -> js cpp rust
#
# Install: add this line to ~/.bashrc
#   source ~/repos/algo/kata-machine/completions/just.bash

# just's built-in (clap) completion, used for everything else
declare -F _clap_complete_just >/dev/null || eval "$(JUST_COMPLETE=bash just 2>/dev/null)"

_kata_just() {
    # find the kata-machine root (the dir with katas.txt) from the cwd upwards
    local root=$PWD
    while [[ $root && ! -f $root/katas.txt ]]; do root=${root%/*}; done

    local recipe=${COMP_WORDS[1]-} cur=${COMP_WORDS[COMP_CWORD]} langs="js cpp rust" katas=""
    if [[ $root && $COMP_CWORD -ge 2 ]]; then
        katas=$(ls "$root/kata-cpp/templates" 2>/dev/null | sed 's/\.hpp$//')
        case $recipe in
            test)
                if ((COMP_CWORD == 2)); then
                    mapfile -t COMPREPLY < <(compgen -W "$langs" -- "$cur")
                else
                    mapfile -t COMPREPLY < <(compgen -W "$katas" -- "$cur")
                fi
                return ;;
            test-all)
                mapfile -t COMPREPLY < <(compgen -W "$katas" -- "$cur")
                return ;;
            generate | clear)
                mapfile -t COMPREPLY < <(compgen -W "$langs" -- "$cur")
                return ;;
        esac
    fi

    declare -F _clap_complete_just >/dev/null && _clap_complete_just "$@"
}

complete -F _kata_just -o bashdefault -o default just
