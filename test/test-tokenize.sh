#!/bin/bash

export C4="$(pwd)/../build/default/c4";

FILTER=$1

PASSES=0

for path in $(find "resource/" -type d);
do
  oldcwd=$(pwd)
  cd "$path"

  for test in $(ls *.c)
  do
    echo "testing $path/${test}";

    # contains floating point
    if [ $FILTER ];
    then
      $(grep -e '\.[0-9]' -e '[0-9]\.' -e '[0-9]\+\(u\|U\|l\|L\)' \
        -e '0\(x\|X\)' -e " L'" "$test" > /dev/null)
      if [ $? -eq 0 ];
      then
        rm "$test"
        continue
      fi
    fi

    testname=$(basename "${test}" .c);
    result=$(mktemp /tmp/"${testname}".XXXX);
    expectedfile=$(dirname "${test}")/"${testname}"".tok"
    expected=$(mktemp /tmp/"${testname}".expected.XXXX);
    tail -n +2 "${expectedfile}" > "${expected}";

    $("${C4}" --tokenize "$(basename ${test})" > "${result}" 2>&1)
    RES=$?
    EXP=$(head -n 1 ${expectedfile})

    if [[ ( $EXP -ne 0 && $RES -eq 0 ) || ( $EXP -eq 0 && $RES -ne 0 ) ]];
    then
      rm "${result}";
      echo "-> error: wrong return code";
			echo "          expected: $EXP - actual $RES"
      continue;
    fi;

    diff -q "${expected}" "${result}" > /dev/null 2>&1
    if [ 0 -ne $? ];
    then
			echo "expected                                                           \
              -      actual"
      colordiff -y --width=180 "${expected}" "${result}"
      echo "-> output differs: ${path}/${test}";
      echo Tests passed: $PASSES
      exit 1;
    else
      echo "-> passed";
      PASSES=$(echo $PASSES +1 | bc )
    fi;

    rm "${result}";
    rm "${expected}";
  done
  cd "$oldcwd"
done

echo Passed tests: $PASSES
