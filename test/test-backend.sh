#!/bin/bash

export C4="$(pwd)/../build/default/c4"

PASSES=0
TOTAL=0
SUFFIX=".backend"

# iterate over all paths in the resource/ directory
for TESTDIR in $(find "resource/" -type d)
do
  # store the pwd, and cd into the test path
  OLDPWD=$(pwd)
  cd "${TESTDIR}"

  # check whether we have a directory of files that should be linked
  if [[ $(basename "${TESTDIR}") == *"${SUFFIX}.d" ]]
  then
    # increment TOTAL
    TOTAL=$(echo ${TOTAL} +1 | bc)

    # run the test for a bunch of files, that should be linked together

    # create a variable that holds the names of all files that shall be linked
    # together
    TOLINK=

    # iterate over all files, compile them and add them to TOLINK
    for TESTFILE in $(find . -maxdepth 1 -iname "*.c" -type f)
    do
      # prune name
      TESTFILE=$(basename "${TESTFILE}")

      # get the name of the test file
      TESTNAME=$(basename "${TESTFILE}" "${SUFFIX}.c")

      # get a file for the LLVM output
      TESTLL=$(mktemp "/tmp/${TESTNAME}.XXXX.ll")

      echo -n "==> compiling '${TESTDIR}/${TESTFILE}' -> '${TESTLL}'   "

      # compile the file
      $("${C4}" "${TESTFILE}" > "${TESTLL}" 2>&1)

      # verify compiling was successful
      if [ $? -ne 0 ]
      then
        # print ERROR result
        echo "ERROR"

        # remove the current ll file
        rm "${TESTLL}"

        # remove ll files
        for TESTLL in ${TOLINK}
        do
          rm "${TESTLL}"
        done

        # empty the files to link
        TOLINK=""

        #exit the loop
        break
      fi

      # print SUCCESS
      echo "SUCCESS"

      # add the new ll file
      TOLINK="${TOLINK} ${TESTLL}"
    done

    # if compilation went wrong, skip this directory
    if [ "${TOLINK}" == "" ]
    then
      cd "${OLDPWD}"
      # insert newline after each test
      echo ""
      continue
    fi

    echo -n "==> ld${TOLINK}    "

    # let clang link the targets
    clang ${TOLINK}

    # remove ll files
    for TESTLL in ${TOLINK}
    do
      rm "${TESTLL}"
    done

    # if files could not be linked, print error message and skip this directory
    if [ $? -ne 0 ]
    then
      echo "ERROR"
      echo "==> linking failed, ABORT"
      # insert newline after each test
      echo ""
      cd "${OLDPWD}"
      continue
    fi

    echo "SUCCESS"

    if [ ! -e "result" ]
    then
      echo "==> no result specified, ABORT"
      echo "==> FAIL"
      echo ""
      cd "${OLDPWD}"
      continue
    fi

    RESULT=$(head -n 1 "result")

    ARGS=
    if [ -e "args" ]
    then
      ARGS=$(head -n 1 "args")
    fi

    # execute the binary
    ./a.out ${ARGS}
    RES=$?

    # verify the return value
    if [ ${RES} -ne ${RESULT} ]
    then
      echo "==> expected ${RESULT}, was ${RES}"
      echo "==> FAIL"
    else
      echo "==> PASS"
      PASSES=$(echo ${PASSES} +1 | bc)
    fi

    # remove the binary
    rm "a.out"

    # insert newline after each test
    echo ""
  else
    # regular directory, compile and link each file seperately
    for TESTFILE in $(find . -maxdepth 1 -iname "*${SUFFIX}.c" -type f)
    do
      # increment TOTAL
      TOTAL=$(echo ${TOTAL} +1 | bc)

      # prune name
      TESTFILE=$(basename "${TESTFILE}")

      # get the name of the test file
      TESTNAME=$(basename "${TESTFILE}" "${SUFFIX}.c")

      # get a file for the source
      TESTSRC=$(mktemp "/tmp/${TESTNAME}.XXXX.c")

      # get a file for the LLVM output
      TESTLL=$(mktemp "/tmp/${TESTNAME}.XXXX.ll")

      # fill the source file
      tail -n +4 "${TESTFILE}" > "${TESTSRC}"

      echo -n "==> compiling '${TESTDIR}/${TESTFILE}' -> '${TESTLL}'   "

      # compile the file
      $("${C4}" "${TESTSRC}" > "${TESTLL}" 2>&1)

      # verify compiling was successful
      if [ $? -ne 0 ]
      then
        # print ERROR result
        echo "ERROR"
        echo "==> FAIL"

        # remove the c and ll file
        rm "${TESTSRC}"
        rm "${TESTLL}"

        # skip this file and insert newline after test
        echo ""
        continue
      fi

      # print SUCCESS
      echo "SUCCESS"

      echo -n "==> ld ${TESTFILE}    "

      # let clang link the targets
      clang "${TESTLL}"

      # remove the c and ll file
      rm "${TESTSRC}"
      rm "${TESTLL}"

      # if files could not be linked, print error message and skip this
      # directory
      if [ $? -ne 0 ]
      then
        echo "ERROR"
        echo "==> FAIL"
        # insert newline after each test
        echo ""
        cd "${OLDPWD}"
        continue
      fi

      echo "SUCCESS"

      RESULT=$(head -n 1 "${TESTFILE}")

      ARGS=$(sed -n 2p "${TESTFILE}")

      # execute the binary
      ./a.out ${ARGS}
      RES=$?

      # verify the return value
      if [ ${RES} -ne ${RESULT} ]
      then
        echo "==> expected ${RESULT}, was ${RES}"
        echo "==> FAIL"
      else
        echo "==> PASS"
        PASSES=$(echo ${PASSES} +1 | bc)
      fi

      # remove the binary
      rm "a.out"

      # insert newline after each test
      echo ""
    done
  fi

  # cd back to the old pwd
  cd "${OLDPWD}"
done


echo "########################################"
echo "#                                      #"
echo "#   Backend-Tests: ${PASSES}/${TOTAL}"
echo "#                                      #"
echo "########################################"
