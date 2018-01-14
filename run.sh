#clean
rm -f src/*.cm*
sortedFiles=$(ocamldep -pp "refmt --print binary" -sort -ml-synonym .re src/*.re)
argsForOcaml=$(echo "$sortedFiles" | sed "s/src\//-impl src\//g")
ocamlc str.cma -g -bin-annot -pp "refmt --print binary" -o ./out -I src/ $argsForOcaml
./out
