#!/bin/bash

export C4="$(pwd)/../build/default/c4";

FILTER=$1

PASSES=0
TOTAL=0

for path in $(find "resource/" -type d);
do
  oldcwd=$(pwd)
  cd "$path"

  for test in $(find . -maxdepth 1 -iname "*.tok" -type f);
  do
    test=$(basename $test) #remove ./
    base=$(basename "$test" .tok)
    if [ ! -e "${base}.c" ];
    then
      echo "missing source file for ${base}.tok"
      continue
    fi

    TOTAL=$(echo $TOTAL +1 | bc )
    #echo "testing $path/${test}";

    # contains floating point
    if [ $FILTER ];
    then
      $(grep -e '\.[0-9]' -e '[0-9]\.' -e '[0-9]\+\(u\|U\|l\|L\)' \
        -e '0\(x\|X\)' -e " L'" "${base}.c" > /dev/null)
      if [ $? -eq 0 ];
      then
        rm "${base}.c"
        continue
      fi
    fi

    testname=$base
    result=$(mktemp /tmp/"${testname}".XXXX);
    expectedfile="$test"
    expected=$(mktemp /tmp/"${testname}".expected.XXXX);
    tail -n +2 "${expectedfile}" > "${expected}";

    $("${C4}" --tokenize "${base}.c" > "${result}" 2>&1)
    RES=$?
    EXP=$(head -n 1 ${expectedfile})

    if [[ ( $EXP -ne 0 && $RES -eq 0 ) || ( $EXP -eq 0 && $RES -ne 0 ) ]];
    then
      rm "${result}";
      echo "-> wrong return code: ${path}/${test}";
      echo -e "          expected: $EXP - actual $RES\n"
      continue;
    fi;

    diff -q "${expected}" "${result}" > /dev/null 2>&1
    if [ 0 -ne $? ];
    then
			echo "expected                                                           \
              -      actual"
			echo "--------                                                           \
                     ------"
      colordiff -y --width=180 "${expected}" "${result}"
      echo -e "-> output differs: ${path}/${test}\n";
      echo
      #echo Tests passed: $PASSES
      #exit 1;
    else
      #echo "-> passed";
      PASSES=$(echo $PASSES +1 | bc )
    fi;

    rm "${result}";
    rm "${expected}";
  done
  cd "$oldcwd"
done

echo "\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#"
echo "\#                                  \#"
echo "\#   Lexer-Tests: ${PASSES}/${TOTAL}"
echo "\#                                  \#"
echo "\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#"
