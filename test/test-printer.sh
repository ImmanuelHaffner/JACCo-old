#!/bin/bash

export C4="$(pwd)/../build/default/c4";

PASSES=0
TOTAL=0

for path in $(find "resource/" -type d);
do
  oldcwd=$(pwd)
  cd "$path"

  for test in $(find . -maxdepth 1 -iname "*.print.c" -type f);
  do
    test=$(basename $test)
    TOTAL=$(echo $TOTAL +1 | bc )
    #echo "testing $path/${test}";

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
			echo "--------                                                           \
                     ------"
      colordiff -y --width=180 "${expected}" "${result}"
      echo -e "-> output differs: ${path}/${test}\n";
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

echo "########################################"
echo "#                                      #"
echo "#   Printer-Tests: ${PASSES}/${TOTAL}"
echo "#                                      #"
echo "########################################"
