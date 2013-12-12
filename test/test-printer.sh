#!/bin/bash

export C4="$(pwd)/../build/default/c4";

PASSES=0

for path in $(find "resource/" -type d);
do
  oldcwd=$(pwd)
  cd "$path"

  for test in $(ls *.print.c)
  do
    echo "testing $path/${test}";

    testname=$(basename "${test}" .print.c);
    result=$(mktemp /tmp/"${testname}".XXXX);
    #expectedfile="$path/${test}"
    expected=$(mktemp /tmp/"${testname}".expected.XXXX);
    cp "${test}" "${expected}";

    $("${C4}" --print-ast "$(basename ${test})" > "${result}" 2>&1)

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
