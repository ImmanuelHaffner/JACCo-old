#!/bin/sh

SRCS=$(find resource/ -iname '*.c')

for SRC in $SRCS;
do
  if [ ! -e "$SRC.out" ];
  then
    echo "$SRC: ERROR: missing output file"
    continue
  fi

  build/default/c4 --tokenize "$SRC" > "test/tmp" 2>&1
  diff "$SRC.out" "test/tmp" > /dev/null 2>&1 #> "test/tmp2" 2>&1
  RES=$?

  echo -n "$SRC: "

  if [ $RES -eq 0 ];
  then
    echo OK
  else
    echo FAILURE
    #echo -ne "\t"
    #cat "test/tmp"
  fi
done

rm -f "test/tmp"
rm -f "test/tmp2"
