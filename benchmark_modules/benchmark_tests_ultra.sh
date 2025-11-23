#!/bin/bash

# ============================================================================ #
#                            ULTRA TEST FUNCTIONS                              #
#                              Tests 28-37                                     #
# ============================================================================ #

test_echo_ultra_extended() {
    print_section "TEST 28: Echo - Ultra Extended (50+ tests)"
    echo "Test 28: Echo Ultra Extended" >> "$REPORT_FILE"

    print_test_header "Testing echo with 50+ additional scenarios..."

    local echo_tests=(
        "echo -n -n -n -n test"
        "echo -nnnn test"
        "echo -n-n-n test"
        "echo -- test"
        "echo --- test"
        "echo -e 'test'"
        "echo -E 'test'"
        "echo -ne test"
        "echo -nE test"
        "echo test1 test2 test3 test4 test5 test6 test7 test8 test9 test10"
        "echo 'test1' 'test2' 'test3' 'test4' 'test5'"
        "echo \"test1\" \"test2\" \"test3\" \"test4\""
        "echo a'b'c\"d\"e"
        "echo 'a\"b'\"c'd\""
        "echo \$HOME\$USER\$PWD"
        "echo '\$HOME\$USER\$PWD'"
        "echo \"\$HOME\$USER\$PWD\""
        "echo test | cat | cat | cat"
        "echo -n test | cat"
        "echo test > /dev/null"
        "echo test 2> /dev/null"
        "echo test > /dev/null 2>&1"
        "echo -n > /dev/null"
        "echo '' '' '' '' ''"
        "echo \"\" \"\" \"\" \"\""
        "echo test     with     spaces"
        "echo 'test     with     spaces'"
        "echo \"test     with     spaces\""
        "echo test\$"
        "echo test\$\$"
        "echo \$\$\$"
        "echo test\\\$test"
        "echo 'test\\ntest'"
        "echo \"test\\ntest\""
        "echo 'test\\ttest'"
        "echo \"test\\ttest\""
        "echo test\\test"
        "echo test\\\\test"
        "echo 'test\\\\test'"
        "echo a b c d e f g h i j k l m n o p q r s t u v w x y z 0 1 2 3 4 5 6 7 8 9"
        "echo !@#\$%^&*()_+-={}[]|:;'<>,.?/"
        "echo '!@#\$%^&*()_+-={}[]|:;\"<>,.?/'"
        "echo test && echo test2"
        "echo test || echo test2"
        "echo test; echo test2"
        "echo -n test; echo test2"
        "echo test | grep test | cat | cat"
        "echo -n -n test | cat | cat"
        "echo test test test test test"
        "echo 'test test test test test'"
    )

    for test_cmd in "${echo_tests[@]}"; do
        run_and_compare "$test_cmd" "echo ext: ${test_cmd:0:25}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_pipes_ultra() {
    print_section "TEST 29: Pipes - Ultra Comprehensive (50+ tests)"
    echo "Test 29: Pipes Ultra" >> "$REPORT_FILE"

    print_test_header "Testing pipes with 50+ scenarios..."

    seq 1 10000 > "$TMP_DIR/huge.txt"

    local pipe_tests=(
        "echo test | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
        "cat $TMP_DIR/huge.txt | head -1000 | tail -500 | head -100 | tail -50"
        "echo a | cat | cat | cat | cat | cat | grep a"
        "echo test | cat | grep test | cat | grep test | cat"
        "echo 'a b c' | cat | cat | cat"
        "ls | cat | cat | cat | wc -l"
        "echo test | cat | cat > /dev/null"
        "echo test | cat | cat 2> /dev/null"
        "cat $TMP_DIR/huge.txt | grep 1 | wc -l"
        "cat $TMP_DIR/huge.txt | grep 2 | wc -l"
        "cat $TMP_DIR/huge.txt | grep 3 | wc -l"
        "echo a | grep a | grep a | grep a"
        "echo test | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
        "ls | head -5 | tail -3"
        "ls | head -10 | cat"
        "echo test | wc -l"
        "echo -n test | wc -l"
        "cat /dev/null | cat"
        "echo '' | cat"
        "echo | cat | cat"
        "echo test | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
        "cat $TMP_DIR/huge.txt | head -5000 | tail -1000 | grep 4"
        "echo 1 | cat | cat | cat | cat | cat"
        "echo 2 | cat | cat | cat | cat | cat"
        "echo a b c | cat | grep b"
        "echo test test test | cat | cat"
        "ls -la | grep bench | cat"
        "ls | cat | cat | cat | cat | wc -l"
        "echo -n a | cat | cat"
        "echo -n | cat | cat"
        "cat $TMP_DIR/huge.txt | wc -l"
        "cat $TMP_DIR/huge.txt | head -1"
        "cat $TMP_DIR/huge.txt | tail -1"
        "echo 'pipe test' | cat | cat | cat | cat"
        "echo test | cat | cat | cat | cat | cat | cat | cat"
        "ls | cat | cat | cat | cat | cat | cat"
        "echo a | cat | cat | cat | cat | cat | cat | cat | cat"
        "cat $TMP_DIR/huge.txt | grep 5 | head -10"
        "cat $TMP_DIR/huge.txt | grep 6 | tail -10"
        "cat $TMP_DIR/huge.txt | head -100 | grep 7"
        "echo multiple words here | cat | cat | cat"
        "echo test1 test2 test3 | cat | grep test2"
        "ls | head -1 | cat | cat"
        "ls | tail -1 | cat | cat"
        "echo final | cat | cat | cat | cat | cat | cat | cat | cat | cat"
        "cat $TMP_DIR/huge.txt | head -50 | tail -25 | head -10 | tail -5"
        "echo 'complex | pipe' | cat"
        "echo test | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
        "cat $TMP_DIR/huge.txt | grep 8 | grep 8 | wc -l"
        "echo end | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
    )

    for test_cmd in "${pipe_tests[@]}"; do
        run_and_compare "$test_cmd" "pipe ultra: ${test_cmd:0:20}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_redirections_ultra() {
    print_section "TEST 30: Redirections - Ultra Complete (40+ tests)"
    echo "Test 30: Redirections Ultra" >> "$REPORT_FILE"

    print_test_header "Testing redirections with 40+ scenarios..."

    local redir_tests=(
        "echo test > $TMP_DIR/r1.txt; cat $TMP_DIR/r1.txt"
        "echo test >> $TMP_DIR/r2.txt; echo test2 >> $TMP_DIR/r2.txt; cat $TMP_DIR/r2.txt"
        "cat < /dev/null"
        "echo test > $TMP_DIR/r3.txt; cat < $TMP_DIR/r3.txt"
        "echo a > $TMP_DIR/r4.txt; echo b >> $TMP_DIR/r4.txt; cat $TMP_DIR/r4.txt"
        "echo test 2> $TMP_DIR/err.txt"
        "ls /nonexistent 2> $TMP_DIR/err2.txt"
        "echo test > $TMP_DIR/r5.txt 2>&1"
        "echo a > $TMP_DIR/r6.txt; echo b > $TMP_DIR/r6.txt; cat $TMP_DIR/r6.txt"
        "cat < /dev/null > $TMP_DIR/r7.txt"
        "echo test > /dev/null; echo \$?"
        "echo test >> /dev/null; echo \$?"
        "cat < /dev/null | cat"
        "echo test > $TMP_DIR/r8.txt; cat $TMP_DIR/r8.txt > $TMP_DIR/r9.txt; cat $TMP_DIR/r9.txt"
        "echo line1 > $TMP_DIR/r10.txt; echo line2 >> $TMP_DIR/r10.txt; echo line3 >> $TMP_DIR/r10.txt; wc -l < $TMP_DIR/r10.txt"
        "echo test > $TMP_DIR/r11.txt; cat $TMP_DIR/r11.txt | cat"
        "echo a > $TMP_DIR/r12.txt; cat $TMP_DIR/r12.txt | cat > $TMP_DIR/r13.txt"
        "echo test >> $TMP_DIR/r14.txt; cat $TMP_DIR/r14.txt"
        "cat < /dev/null > /dev/null"
        "echo test > $TMP_DIR/r15.txt 2> /dev/null"
        "ls > $TMP_DIR/r16.txt; cat $TMP_DIR/r16.txt | wc -l"
        "echo a > $TMP_DIR/r17.txt; echo b >> $TMP_DIR/r17.txt; echo c >> $TMP_DIR/r17.txt; cat $TMP_DIR/r17.txt"
        "echo test > $TMP_DIR/r18.txt; echo test2 > $TMP_DIR/r18.txt; cat $TMP_DIR/r18.txt"
        "cat /dev/null > $TMP_DIR/r19.txt; cat $TMP_DIR/r19.txt"
        "echo -n test > $TMP_DIR/r20.txt; cat $TMP_DIR/r20.txt"
        "echo test > $TMP_DIR/r21.txt; cat < $TMP_DIR/r21.txt > $TMP_DIR/r22.txt; cat $TMP_DIR/r22.txt"
        "echo a b c > $TMP_DIR/r23.txt; cat $TMP_DIR/r23.txt"
        "ls | cat > $TMP_DIR/r24.txt; cat $TMP_DIR/r24.txt | wc -l"
        "echo test | cat > $TMP_DIR/r25.txt; cat $TMP_DIR/r25.txt"
        "cat < /dev/null | cat > $TMP_DIR/r26.txt"
        "echo test > $TMP_DIR/r27.txt; cat $TMP_DIR/r27.txt > $TMP_DIR/r28.txt; cat $TMP_DIR/r28.txt > $TMP_DIR/r29.txt"
        "echo a > $TMP_DIR/r30.txt; echo b > $TMP_DIR/r30.txt; echo c > $TMP_DIR/r30.txt; cat $TMP_DIR/r30.txt"
        "echo test >> $TMP_DIR/r31.txt; echo test >> $TMP_DIR/r31.txt; cat $TMP_DIR/r31.txt"
        "cat < /dev/null > $TMP_DIR/r32.txt; cat $TMP_DIR/r32.txt | wc -l"
        "echo multi word test > $TMP_DIR/r33.txt; cat $TMP_DIR/r33.txt"
        "echo -n > $TMP_DIR/r34.txt; cat $TMP_DIR/r34.txt"
        "ls > $TMP_DIR/r35.txt 2>&1; cat $TMP_DIR/r35.txt | head -3"
        "echo test > $TMP_DIR/r36.txt; cat $TMP_DIR/r36.txt; rm $TMP_DIR/r36.txt"
        "echo a >> $TMP_DIR/r37.txt; echo b >> $TMP_DIR/r37.txt; cat $TMP_DIR/r37.txt | wc -l"
        "cat /dev/null > $TMP_DIR/r38.txt; cat < $TMP_DIR/r38.txt"
    )

    for test_cmd in "${redir_tests[@]}"; do
        run_and_compare "$test_cmd" "redir ultra: ${test_cmd:0:20}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_variables_ultra() {
    print_section "TEST 31: Variables - Ultra Extended (60+ tests)"
    echo "Test 31: Variables Ultra" >> "$REPORT_FILE"

    print_test_header "Testing variables with 60+ scenarios..."

    local var_tests=(
        "echo \$HOME | cat"
        "echo \$PATH | wc -l"
        "echo \$USER | cat"
        "echo \$PWD | cat"
        "echo \$SHELL | cat"
        "echo \$HOME\$USER"
        "echo \$HOME:\$USER"
        "echo \$HOME/\$USER"
        "echo \$HOME-\$USER"
        "echo prefix\$HOMEsuffix"
        "echo \$HOME\$HOME\$HOME"
        "echo '\$HOME'"
        "echo \"\$HOME\""
        "echo '\$HOME\$USER'"
        "echo \"\$HOME\$USER\""
        "echo \$NONEXIST"
        "echo prefix\$NONEXISTsuffix"
        "echo \$NONEXIST\$HOME"
        "echo \$HOME\$NONEXIST"
        "echo \$?"
        "echo \$? \$?"
        "/bin/true; echo \$?"
        "/bin/false; echo \$?"
        "echo test; echo \$?"
        "ls /nonexistent 2>/dev/null; echo \$?"
        "echo \$\$"
        "echo \$\$ \$\$"
        "echo prefix\$\$suffix"
        "echo \$1"
        "echo \$2"
        "echo \$0"
        "echo \$@"
        "echo \$*"
        "echo \$#"
        "echo \$-"
        "echo \$!"
        "echo \${HOME}"
        "echo \${USER}"
        "echo \${PATH}"
        "echo \${NONEXIST}"
        "echo \$HOME/test"
        "echo \$HOME/test/file"
        "echo /home/\$USER"
        "echo test=\$HOME"
        "echo \$HOME=test"
        "export TEST_VAR=value; echo \$TEST_VAR"
        "export TEST_VAR=value; echo prefix\$TEST_VARsuffix"
        "export TEST_VAR='a b c'; echo \$TEST_VAR"
        "export TEST_VAR=''; echo \$TEST_VAR"
        "export TEST_VAR=' '; echo \$TEST_VAR"
        "export TEST_VAR=\$HOME; echo \$TEST_VAR"
        "export VAR1=a VAR2=b; echo \$VAR1 \$VAR2"
        "unset HOME; echo \$HOME"
        "export TEST=123; echo \$TEST"
        "export TEST=abc; echo \"\$TEST\""
        "export TEST=xyz; echo '\$TEST'"
        "echo \$HOME | grep home"
        "echo \$PATH | grep /"
        "echo \$USER | cat | cat"
        "echo \$HOME\$PATH\$USER | wc -c"
        "echo test\$HOMEtest | cat"
    )

    for test_cmd in "${var_tests[@]}"; do
        run_and_compare "$test_cmd" "var ultra: ${test_cmd:0:25}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_builtins_ultra() {
    print_section "TEST 32: Builtins - Ultra Comprehensive (70+ tests)"
    echo "Test 32: Builtins Ultra" >> "$REPORT_FILE"

    print_test_header "Testing builtins with 70+ scenarios..."

    # pwd tests
    run_and_compare "pwd" "builtin: pwd"
    run_and_compare "pwd | cat" "builtin: pwd pipe"
    run_and_compare "pwd; pwd; pwd" "builtin: pwd triple"
    run_and_compare "pwd > /dev/null" "builtin: pwd redirect"
    run_and_compare "pwd 2>&1" "builtin: pwd stderr"

    # cd tests
    run_and_compare "cd; pwd" "builtin: cd home"
    run_and_compare "cd /; pwd" "builtin: cd root"
    run_and_compare "cd /tmp; pwd" "builtin: cd tmp"
    run_and_compare "cd ..; pwd" "builtin: cd parent"
    run_and_compare "cd .; pwd" "builtin: cd current"
    run_and_compare "cd /nonexistent; echo \$?" "builtin: cd fail"
    run_and_compare "cd /tmp; cd ..; pwd" "builtin: cd chain"
    run_and_compare "cd; cd /tmp; pwd" "builtin: cd home tmp"
    run_and_compare "cd /; cd; pwd" "builtin: cd root home"

    # echo tests
    run_and_compare "echo" "builtin: echo empty"
    run_and_compare "echo ''" "builtin: echo empty str"
    run_and_compare "echo -n" "builtin: echo -n only"
    run_and_compare "echo -n ''" "builtin: echo -n empty"
    run_and_compare "echo -n test" "builtin: echo -n test"
    run_and_compare "echo -n -n test" "builtin: echo -n -n"
    run_and_compare "echo -n -n -n test" "builtin: echo -n x3"
    run_and_compare "echo test; echo test2" "builtin: echo multi"
    run_and_compare "echo a b c d e" "builtin: echo multi args"
    run_and_compare "echo 'a b c'" "builtin: echo quoted"

    # env tests
    run_and_compare "env | grep PATH" "builtin: env grep"
    run_and_compare "env | grep HOME" "builtin: env home"
    run_and_compare "env | grep USER" "builtin: env user"
    run_and_compare "env | wc -l" "builtin: env count"
    run_and_compare "env | cat | cat" "builtin: env pipe"

    # export tests
    run_and_compare "export TEST=1; echo \$TEST" "builtin: export num"
    run_and_compare "export TEST=abc; echo \$TEST" "builtin: export str"
    run_and_compare "export TEST='a b'; echo \$TEST" "builtin: export space"
    run_and_compare "export TEST=''; echo \$TEST" "builtin: export empty"
    run_and_compare "export TEST=\$HOME; echo \$TEST" "builtin: export var"
    run_and_compare "export A=1 B=2; echo \$A \$B" "builtin: export multi"
    run_and_compare "export TEST=1; export TEST=2; echo \$TEST" "builtin: export override"
    run_and_compare "export PATH=test; echo \$PATH" "builtin: export path"
    run_and_compare "export | grep TEST" "builtin: export list"
    run_and_compare "export TEST=123; unset TEST; echo \$TEST" "builtin: export unset"

    # unset tests
    run_and_compare "export TEST=1; unset TEST; echo \$TEST" "builtin: unset test"
    run_and_compare "unset PATH; echo \$PATH" "builtin: unset path"
    run_and_compare "unset NONEXIST" "builtin: unset nonexist"
    run_and_compare "export A=1 B=2; unset A; echo \$A \$B" "builtin: unset one"
    run_and_compare "unset HOME; unset USER; unset PWD" "builtin: unset multi"

    # exit tests
    run_and_compare "exit 0" "builtin: exit 0"
    run_and_compare "exit 1" "builtin: exit 1"
    run_and_compare "exit 42" "builtin: exit 42"
    run_and_compare "exit 255" "builtin: exit 255"
    run_and_compare "exit 256" "builtin: exit 256"
    run_and_compare "exit -1" "builtin: exit -1"
    run_and_compare "exit abc" "builtin: exit invalid"
    run_and_compare "exit 999" "builtin: exit large"

    # combinations
    run_and_compare "cd /tmp; pwd; cd; pwd" "builtin: cd pwd combo"
    run_and_compare "export TEST=val; echo \$TEST; unset TEST; echo \$TEST" "builtin: export echo unset"
    run_and_compare "pwd | cat | cat | cat" "builtin: pwd multi pipe"
    run_and_compare "echo test | cat; pwd | cat" "builtin: echo pwd pipe"
    run_and_compare "cd /; pwd; cd /tmp; pwd" "builtin: cd navigation"

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_quotes_ultra() {
    print_section "TEST 33: Quotes - Ultra Extended (50+ tests)"
    echo "Test 33: Quotes Ultra" >> "$REPORT_FILE"

    print_test_header "Testing quotes with 50+ scenarios..."

    local quote_tests=(
        "echo 'simple'"
        "echo \"simple\""
        "echo 'a b c'"
        "echo \"a b c\""
        "echo 'test\"test'"
        "echo \"test'test\""
        "echo 'it\\'s'"
        "echo \"it's\""
        "echo '\"'"
        "echo \"'\""
        "echo '\"\"\"'"
        "echo \"'''\""
        "echo '\$HOME'"
        "echo \"\$HOME\""
        "echo 'test\$HOME'"
        "echo \"test\$HOME\""
        "echo '\$HOME\$USER'"
        "echo \"\$HOME\$USER\""
        "echo '  spaces  '"
        "echo \"  spaces  \""
        "echo 'multiple  spaces'"
        "echo \"multiple  spaces\""
        "echo 'a'b'c'"
        "echo \"a\"b\"c\""
        "echo a'b'c"
        "echo a\"b\"c"
        "echo 'a\"b\"c'"
        "echo \"a'b'c\""
        "echo ''"
        "echo \"\""
        "echo '' ''"
        "echo \"\" \"\""
        "echo 'test' \"test\""
        "echo \"test\" 'test'"
        "echo 'a b' 'c d'"
        "echo \"a b\" \"c d\""
        "echo test'with'quotes"
        "echo test\"with\"quotes"
        "echo 'start' middle 'end'"
        "echo \"start\" middle \"end\""
        "echo '\\\$HOME'"
        "echo \"\\\$HOME\""
        "echo '\\n\\t'"
        "echo \"\\n\\t\""
        "echo 'special!@#\$%'"
        "echo \"special!@#\$%\""
        "echo '|><&;'"
        "echo \"|><&;\""
        "echo 'test | test'"
        "echo \"test | test\""
    )

    for test_cmd in "${quote_tests[@]}"; do
        run_and_compare "$test_cmd" "quote ultra: ${test_cmd:0:25}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_wildcards_ultra() {
    print_section "TEST 34: Wildcards - Ultra Complete (40+ tests)"
    echo "Test 34: Wildcards Ultra" >> "$REPORT_FILE"

    print_test_header "Testing wildcards with 40+ scenarios..."

    mkdir -p "$TMP_DIR/wildtest2"
    touch "$TMP_DIR/wildtest2/a.txt"
    touch "$TMP_DIR/wildtest2/b.txt"
    touch "$TMP_DIR/wildtest2/ab.txt"
    touch "$TMP_DIR/wildtest2/abc.txt"
    touch "$TMP_DIR/wildtest2/test.sh"
    touch "$TMP_DIR/wildtest2/test.c"
    touch "$TMP_DIR/wildtest2/file1"
    touch "$TMP_DIR/wildtest2/file2"
    touch "$TMP_DIR/wildtest2/file10"

    local wild_tests=(
        "ls $TMP_DIR/wildtest2/*.txt"
        "ls $TMP_DIR/wildtest2/*.sh"
        "ls $TMP_DIR/wildtest2/*.c"
        "ls $TMP_DIR/wildtest2/*"
        "ls $TMP_DIR/wildtest2/a*"
        "ls $TMP_DIR/wildtest2/b*"
        "ls $TMP_DIR/wildtest2/*a*"
        "ls $TMP_DIR/wildtest2/*b*"
        "ls $TMP_DIR/wildtest2/file*"
        "ls $TMP_DIR/wildtest2/file?"
        "ls $TMP_DIR/wildtest2/file??"
        "ls $TMP_DIR/wildtest2/???.txt"
        "ls $TMP_DIR/wildtest2/????.txt"
        "ls $TMP_DIR/wildtest2/test.*"
        "echo $TMP_DIR/wildtest2/*.txt"
        "echo $TMP_DIR/wildtest2/*"
        "cat $TMP_DIR/wildtest2/*.txt 2>/dev/null"
        "ls $TMP_DIR/wildtest2/*.* 2>&1 | wc -l"
        "ls $TMP_DIR/wildtest2/[ab]*.txt"
        "ls $TMP_DIR/wildtest2/[ab].txt"
        "ls $TMP_DIR/wildtest2/[a-z].txt"
        "ls $TMP_DIR/wildtest2/file[12]"
        "ls $TMP_DIR/wildtest2/file[0-9]"
        "ls $TMP_DIR/wildtest2/file[0-9]*"
        "echo '*.txt'"
        "echo \"*.txt\""
        "ls $TMP_DIR/wildtest2/* | wc -l"
        "ls $TMP_DIR/wildtest2/*.* | wc -l"
        "ls $TMP_DIR/wildtest2/a* | cat"
        "ls $TMP_DIR/wildtest2/b* | cat"
        "ls $TMP_DIR/wildtest2/* | grep txt"
        "ls $TMP_DIR/wildtest2/* | grep test"
        "echo $TMP_DIR/wildtest2/* | wc -w"
        "ls $TMP_DIR/wildtest2/*.txt | wc -l"
        "ls $TMP_DIR/wildtest2/file* | wc -l"
        "ls $TMP_DIR/wildtest2/test.* | wc -l"
        "ls $TMP_DIR/wildtest2/??? | wc -l"
        "ls $TMP_DIR/wildtest2/???? | wc -l"
        "ls $TMP_DIR/wildtest2/?????.* | wc -l"
        "echo $TMP_DIR/wildtest2/a*.txt"
    )

    for test_cmd in "${wild_tests[@]}"; do
        run_and_compare "$test_cmd" "wild ultra: ${test_cmd:0:20}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_error_handling() {
    print_section "TEST 35: Error Handling - Comprehensive (30+ tests)"
    echo "Test 35: Error Handling" >> "$REPORT_FILE"

    print_test_header "Testing error handling with 30+ scenarios..."

    local error_tests=(
        "ls /nonexistent 2>&1"
        "cat /nonexistent/file 2>&1"
        "cd /nonexistent/dir 2>&1; echo \$?"
        "mkdir /nonexistent/dir 2>&1"
        "rm /nonexistent/file 2>&1"
        "chmod 777 /nonexistent 2>&1"
        "chown user /nonexistent 2>&1"
        "./nonexistent_binary 2>&1"
        "/nonexistent/path/cmd 2>&1"
        "nonexistentcmd 2>&1"
        "cat < /nonexistent 2>&1"
        "echo test > /nonexistent/file 2>&1"
        "ls /root 2>&1"
        "cat /etc/shadow 2>&1"
        "cd /root 2>&1; echo \$?"
        "export 123INVALID=test 2>&1"
        "export =test 2>&1"
        "export TEST 2>&1"
        "unset 123INVALID 2>&1"
        "exit abc 2>&1"
        "exit 99999 2>&1"
        "cd 2>&1; echo \$?"
        "cd /tmp /home 2>&1"
        "pwd arg1 arg2 2>&1"
        "env arg1 arg2 2>&1"
        "ls -invalid_flag 2>&1"
        "cat -invalid_flag file 2>&1"
        "echo test | nonexistent 2>&1"
        "nonexistent | echo test 2>&1"
        "ls | nonexistent | cat 2>&1"
    )

    for test_cmd in "${error_tests[@]}"; do
        ((TESTS_TOTAL++))
        echo -e "$test_cmd\nexit" > "$TMP_DIR/test.txt"
        timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"

        if [ $? -ne 124 ]; then
            print_pass "Error handling: ${test_cmd:0:30}"
            echo "  ✓ error: $test_cmd" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_fail "Error handling timeout: ${test_cmd:0:30}"
            FAILED_TESTS+=("Error: $test_cmd")
            FAILED_DETAILS+=("Command timed out on error")
            echo "  ✗ error: $test_cmd" >> "$REPORT_FILE"
            ((TESTS_FAILED++))
        fi
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_mixed_complex() {
    print_section "TEST 36: Mixed Complex Commands (40+ tests)"
    echo "Test 36: Mixed Complex" >> "$REPORT_FILE"

    print_test_header "Testing complex mixed scenarios..."

    local complex_tests=(
        "export VAR=test; echo \$VAR | cat"
        "cd /tmp; pwd | cat; cd"
        "echo \$HOME | cat | cat | cat"
        "ls | grep test | cat | wc -l"
        "echo test > $TMP_DIR/f.txt; cat $TMP_DIR/f.txt | cat"
        "export A=1; export B=2; echo \$A \$B | cat"
        "pwd; cd /tmp; pwd; cd; pwd"
        "echo a | cat; echo b | cat; echo c | cat"
        "ls | head -5 | cat | wc -l"
        "echo \$PATH | cat | grep /"
        "export TEST=val; unset TEST; echo \$TEST"
        "echo test | cat > $TMP_DIR/x.txt; cat $TMP_DIR/x.txt"
        "ls | cat | cat | cat | wc -l"
        "echo \$HOME\$USER | cat | cat"
        "pwd | cat; ls | cat | head -3"
        "export X=1 Y=2; echo \$X; echo \$Y"
        "echo 'test' | cat | cat | grep test"
        "cat /dev/null | cat | cat"
        "echo -n test | cat | cat"
        "ls > $TMP_DIR/ls.txt; cat $TMP_DIR/ls.txt | wc -l"
        "echo a; echo b; echo c"
        "pwd; pwd; pwd"
        "echo \$HOME | cat | cat | cat | cat"
        "export VAR=\$HOME; echo \$VAR"
        "cd /; pwd; cd /tmp; pwd; cd"
        "echo test test test | cat | grep test | wc -l"
        "ls | cat > $TMP_DIR/out.txt; cat $TMP_DIR/out.txt | head -1"
        "echo 'a b c' | cat | cat | cat"
        "export A=a B=b C=c; echo \$A \$B \$C"
        "pwd | cat | cat | cat | cat | cat"
        "echo \$PATH\$HOME | cat"
        "ls | head -10 | tail -5 | cat"
        "echo test | cat | cat | cat | cat | cat | cat"
        "export TEST=123; echo \$TEST | cat"
        "cd /tmp; ls | wc -l; cd"
        "echo a > $TMP_DIR/a.txt; echo b >> $TMP_DIR/a.txt; cat $TMP_DIR/a.txt"
        "pwd; cd /; pwd; cd /tmp; pwd"
        "echo 'test string' | cat | cat | cat"
        "export VAR='a b c'; echo \$VAR | cat"
        "ls | cat | cat | cat | cat | wc -l"
    )

    for test_cmd in "${complex_tests[@]}"; do
        run_and_compare "$test_cmd" "complex: ${test_cmd:0:20}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_stress_extended() {
    print_section "TEST 37: Stress Testing Extended (20+ tests)"
    echo "Test 37: Stress Extended" >> "$REPORT_FILE"

    print_test_header "Testing stress scenarios..."

    # Create large file
    seq 1 50000 > "$TMP_DIR/huge2.txt"

    local stress_tests=(
        "cat $TMP_DIR/huge2.txt | wc -l"
        "cat $TMP_DIR/huge2.txt | head -10000 | wc -l"
        "cat $TMP_DIR/huge2.txt | tail -10000 | wc -l"
        "cat $TMP_DIR/huge2.txt | grep 1 | wc -l"
        "cat $TMP_DIR/huge2.txt | head -25000 | tail -1000 | wc -l"
        "seq 1 1000 | cat | cat | cat | cat | cat"
        "seq 1 5000 | grep 1 | wc -l"
        "seq 1 10000 | head -5000 | tail -2500 | wc -l"
        "cat $TMP_DIR/huge2.txt | cat | cat | wc -l"
        "cat $TMP_DIR/huge2.txt | grep 2 | grep 2 | wc -l"
        "seq 1 100 | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
        "cat $TMP_DIR/huge2.txt | head -1"
        "cat $TMP_DIR/huge2.txt | tail -1"
        "cat $TMP_DIR/huge2.txt | head -100 | grep 5"
        "seq 1 10000 | wc -l"
        "seq 1 20000 | head -10000 | wc -l"
        "cat $TMP_DIR/huge2.txt | grep 3 | head -100 | wc -l"
        "seq 1 1000 | cat | cat | cat | wc -l"
        "cat $TMP_DIR/huge2.txt | head -30000 | tail -20000 | wc -l"
        "seq 1 5000 | cat | wc -l"
    )

    for test_cmd in "${stress_tests[@]}"; do
        run_and_compare "$test_cmd" "stress: ${test_cmd:0:20}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}
