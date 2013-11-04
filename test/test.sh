#!/bin/bash

export C4="/home/immanuel/Documents/University/Compiler Construction/c4/build/default/c4";

for test in $(find "resource/" -iname "*.c" -type f);
do
  echo "testing ${test}";
  oldcwd=$(pwd);

  testname=$(basename "${test}" .c);
  result=$(mktemp /tmp/"${testname}".XXXX);
  expectedfile=$(dirname "${test}")/"${testname}".expected
  expected=$(mktemp /tmp/"${testname}".expected.XXXX);
  tail -n +2 "${expectedfile}" > "${expected}";
  
  cd $(dirname "${test}");
  $("${C4}" --tokenize "$(basename ${test})" > "${result}" 2>&1)
  RES=$?
  cd "${oldcwd}";

  EXP=$(head -n 1 ${expectedfile})
  if [ $EXP -ne 0 ]
  then
    if [ $RES -ne 0 ]
    then
      echo "-> passed";
      continue;
    fi
    rm "${result}";
    cd "${oldcwd}";
    echo "-> error";
    continue;
  fi;

  $(diff -q "${result}" "${expected}" > /dev/null 2>&1)
  if [ 0 -ne $? ];
  then
    diff -y "${result}" "${expected}"
    echo "-> output differs: ${test}";
    exit 1;
  else
    echo "-> passed";
  fi;
  
  rm "${result}";
  rm "${expected}";
done
