#!/bin/bash

export C4="$(pwd)/../build/default/c4";

PASSES=0
TOTAL=0

for path in $(find "resource/" -type d);
do
  oldcwd=$(pwd)
  cd "$path"

  for test in $(find . -maxdepth 1 -iname "*.sema.c" -type f);
  do
    test=$(basename $test)
    TOTAL=$(echo $TOTAL +1 | bc )

    expected=$(head -n 1 "$test")
    result=$(mktemp /tmp/"${test}".result.XXXX)
    input=$(mktemp /tmp/"${test}".input.XXXX);
    tail -n +2 "$test" > $input

    $("${C4}" --parse "${input}" > "${result}" 2>&1)

    if [ $expected -ne $? ];
    then
      # Input differs
      cat $result
      echo -e "-> output differs: ${path}/${test}\n";
    else
      PASSES=$(echo $PASSES +1 | bc )
    fi

    rm "${input}";
  done
  cd "$oldcwd"
done

echo "########################################"
echo "#                                      #"
echo "#   Sema-Tests: ${PASSES}/${TOTAL}"
echo "#                                      #"
echo "########################################"
