#!/bin/bash

export C4="/home/immanuel/Documents/University/Compiler Construction/c4/build/default/c4";

for test in $(find "resource/" -iname "*.c" -type f);
do
  echo "testing ${test}";
  oldcwd=$(pwd);
  cd $(dirname "${test}");
  testname=$(basename "${test}" .c);
  result=$(mktemp /tmp/"${testname}".XXXX);
  
  if ! $("${C4}" --tokenize "$(basename ${test})" > "${result}" 2>&1);
  then
    rm "${result}";
    cd "${oldcwd}";
    echo "-> error";
    continue;
  fi;
  
  cd "${oldcwd}";
  expectedfile=$(dirname "${test}")/"${testname}".expected

  if [ ! -e "${expectedfile}" ];
  then
    continue
  fi

  expected=$(mktemp /tmp/"${testname}".expected.XXXX);
  tail -n +2 "${expectedfile}" > "${expected}";

  $(diff -q "${result}" "${expected}")
  if [ 0 -ne $? ];
  then
    diff -y "${result}" "${expected}"
    echo "-> output differs";
    exit;
  else
    echo "-> passed";
  fi;
  
  rm "${result}";
  rm "${expected}";
done
