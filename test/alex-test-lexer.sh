#!/bin/bash

export C4="$(pwd)/../build/default/c4";

PASSES=0
SKIPPED=0
FAILED=0

for path in $(find resource/ -type d); do
    oldcwd=$(pwd)
    cd "$path"

    for test in *.c; do
        if [ "$test" = "*.c" ]; then
            continue
        fi
        
        echo -n "Testing $path/$test"
        #filter the tests we do not accept
	#floats
        $(grep -q -e '\.[0-9]' -e '[0-9]\.' "$test")
	skip=$?
	#hexadecimals
        $(grep -q -e '0[xX][0-9a-fA-F]' "$test")
        skip=$(echo "$skip * $?" | bc)
        #integer suffixes
        $(grep -q -e '[0-9][uUlL]' "$test")
        skip=$(echo "$skip * $?" | bc)
	#octal escape sequences
        $(grep -q -e '\\[1-7]' -e '\\[0-7]\{2,3\}' "$test")
        skip=$(echo "$skip * $?" | bc)
        #encoding prefixes
        $(grep -q -e '[(u8)uUL]"' "$test")
        skip=$(echo "$skip * $?" | bc)


        if [ $skip -eq 0 ]; then
            SKIPPED=$(echo "$SKIPPED + 1" | bc)
	    echo "-> skipped"
            continue
        fi
        #test is ok proceed testrun

        testname=$(basename "${test}" .c);
        result=$(mktemp /tmp/"${testname}".XXXX);
        expectedfile=$(dirname "${test}")/"${testname}"".tok"
        expected=$(mktemp /tmp/"${testname}".expected.XXXX);
        tail -n +2 "${expectedfile}" > "${expected}";

        $("${C4}" --tokenize "$(basename ${test})" > "${result}" 2>&1)
        RES=$?
        EXP=$(head -n 1 ${expectedfile})

        if [[ ( $EXP -ne 0 && $RES -eq 0 ) || ( $EXP -eq 0 && $RES -ne 0 ) ]]; then
            echo -e "-> FAILED: wrong return code\n\t\t\texpected: $EXP - actual $RES"
            FAILED=$(echo "$FAILED + 1" | bc)
        else
            diff -q "${expected}" "${result}" > /dev/null 2>&1
            if [ 0 -ne $? ]; then
                echo "-> FAILED"
                echo "Expected:                                                     |Actual:"
                diff --side-by-side --suppress-common-lines "${expected}" "${result}" | head
                FAILED=$(echo "$FAILED + 1" | bc)
            else
                echo "-> passed"
                PASSES=$(echo "$PASSES + 1" | bc )
            fi
        fi

        rm "${result}";
        rm "${expected}";
    done
    cd "$oldcwd"
done

echo -e "\nPassed tests: $PASSES\nFailed tests: $FAILED\nSkipped tests: $SKIPPED"
