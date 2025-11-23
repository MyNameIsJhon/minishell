#!/bin/bash

# ============================================================================ #
#                          ADVANCED TEST FUNCTIONS                             #
#                              Tests 18-27                                     #
# ============================================================================ #

test_heredoc_comprehensive() {
    print_section "TEST 18: Heredoc - Comprehensive Testing"
    echo "Test 18: Heredoc Comprehensive" >> "$REPORT_FILE"

    print_test_header "Testing heredoc with various scenarios..."

    # Basic heredoc
    cat > "$TMP_DIR/heredoc_test1.txt" << 'TESTSCRIPT'
cat << EOF
line 1
line 2
line 3
EOF
exit
TESTSCRIPT

    timeout 10 bash -c "cat '$TMP_DIR/heredoc_test1.txt' | $MINISHELL > $TMP_DIR/ms_heredoc1.txt 2>&1"
    echo -e "line 1\nline 2\nline 3" > "$TMP_DIR/expected_heredoc1.txt"

    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/ms_heredoc1.txt" | grep -v "^\$" > "$TMP_DIR/ms_clean.txt"
    if diff -q "$TMP_DIR/ms_clean.txt" "$TMP_DIR/expected_heredoc1.txt" > /dev/null 2>&1; then
        print_pass "Basic heredoc"
        echo "  ✓ basic heredoc" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Basic heredoc - Output mismatch"
        FAILED_TESTS+=("Basic heredoc")
        FAILED_DETAILS+=("Heredoc output doesn't match expected")
        echo "  ✗ basic heredoc" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Heredoc with variable expansion
    cat > "$TMP_DIR/heredoc_test2.txt" << 'TESTSCRIPT'
cat << EOF
HOME is $HOME
USER is $USER
EOF
exit
TESTSCRIPT

    timeout 10 bash -c "cat '$TMP_DIR/heredoc_test2.txt' | $MINISHELL > $TMP_DIR/ms_heredoc2.txt 2>&1"
    timeout 10 bash -c "cat '$TMP_DIR/heredoc_test2.txt' | bash --norc --noprofile > $TMP_DIR/bash_heredoc2.txt 2>&1"

    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/ms_heredoc2.txt" | grep -v "^\$" > "$TMP_DIR/ms_clean2.txt"
    if diff -q "$TMP_DIR/ms_clean2.txt" "$TMP_DIR/bash_heredoc2.txt" > /dev/null 2>&1; then
        print_pass "Heredoc with variable expansion"
        echo "  ✓ heredoc with variables" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Heredoc with variable expansion - Expansion issue"
        FAILED_TESTS+=("Heredoc with variables")
        FAILED_DETAILS+=("Variable expansion in heredoc failed")
        echo "  ✗ heredoc with variables" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Heredoc with quotes
    cat > "$TMP_DIR/heredoc_test3.txt" << 'TESTSCRIPT'
cat << 'EOF'
$HOME should not expand
'single quotes'
"double quotes"
EOF
exit
TESTSCRIPT

    timeout 10 bash -c "cat '$TMP_DIR/heredoc_test3.txt' | $MINISHELL > $TMP_DIR/ms_heredoc3.txt 2>&1"

    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/ms_heredoc3.txt" | grep -v "^\$" > "$TMP_DIR/ms_clean3.txt"
    if grep -q '\$HOME should not expand' "$TMP_DIR/ms_clean3.txt"; then
        print_pass "Heredoc with quoted delimiter (no expansion)"
        echo "  ✓ heredoc quoted delimiter" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Heredoc with quoted delimiter - Expansion occurred"
        FAILED_TESTS+=("Heredoc quoted delimiter")
        FAILED_DETAILS+=("Variables should not expand with quoted delimiter")
        echo "  ✗ heredoc quoted delimiter" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Multiple heredocs
    cat > "$TMP_DIR/heredoc_test4.txt" << 'TESTSCRIPT'
cat << EOF
first heredoc
EOF
cat << EOF
second heredoc
EOF
exit
TESTSCRIPT

    timeout 10 bash -c "cat '$TMP_DIR/heredoc_test4.txt' | $MINISHELL > $TMP_DIR/ms_heredoc4.txt 2>&1"

    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/ms_heredoc4.txt" | grep -v "^\$" > "$TMP_DIR/ms_clean4.txt"
    if grep -q "first heredoc" "$TMP_DIR/ms_clean4.txt" && grep -q "second heredoc" "$TMP_DIR/ms_clean4.txt"; then
        print_pass "Multiple heredocs in sequence"
        echo "  ✓ multiple heredocs" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Multiple heredocs - Not all heredocs processed"
        FAILED_TESTS+=("Multiple heredocs")
        FAILED_DETAILS+=("One or more heredocs failed")
        echo "  ✗ multiple heredocs" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Heredoc with special characters
    cat > "$TMP_DIR/heredoc_test5.txt" << 'TESTSCRIPT'
cat << EOF
special chars: !@#$%^&*()
brackets: []{}()<>
quotes: '"
EOF
exit
TESTSCRIPT

    timeout 10 bash -c "cat '$TMP_DIR/heredoc_test5.txt' | $MINISHELL > $TMP_DIR/ms_heredoc5.txt 2>&1"

    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/ms_heredoc5.txt" | grep -v "^\$" > "$TMP_DIR/ms_clean5.txt"
    if grep -q "special chars" "$TMP_DIR/ms_clean5.txt"; then
        print_pass "Heredoc with special characters"
        echo "  ✓ heredoc special chars" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Heredoc with special characters"
        FAILED_TESTS+=("Heredoc special chars")
        FAILED_DETAILS+=("Special characters not handled properly")
        echo "  ✗ heredoc special chars" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_exit_codes_ultra_strict() {
    print_section "TEST 19: Exit Codes - Ultra Strict Validation"
    echo "Test 19: Exit Codes Ultra Strict" >> "$REPORT_FILE"

    print_test_header "Testing exit codes for all commands and builtins..."

    # Test exit code 0 (success)
    echo -e "echo test\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/result.txt" | grep -v "^\$" | grep -v "^test" > "$TMP_DIR/clean.txt"
    if grep -q "^0$" "$TMP_DIR/clean.txt"; then
        print_pass "Exit code 0 after successful echo"
        echo "  ✓ exit code 0" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Exit code 0 - Expected 0, got: $(cat $TMP_DIR/clean.txt)"
        FAILED_TESTS+=("Exit code 0")
        FAILED_DETAILS+=("Exit code should be 0 after successful command")
        echo "  ✗ exit code 0" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test exit code after failed command
    echo -e "/bin/false\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/result.txt" | grep -v "^\$" | tail -1 > "$TMP_DIR/clean.txt"
    if grep -q "^1$" "$TMP_DIR/clean.txt"; then
        print_pass "Exit code 1 after /bin/false"
        echo "  ✓ exit code 1" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Exit code 1 - Expected 1, got: $(cat $TMP_DIR/clean.txt)"
        FAILED_TESTS+=("Exit code 1")
        FAILED_DETAILS+=("Exit code should be 1 after /bin/false")
        echo "  ✗ exit code 1" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test exit code 127 (command not found)
    echo -e "nonexistentcommand123456789\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/result.txt" | grep -v "^\$" | grep "^127$" > "$TMP_DIR/clean.txt"
    if [ -s "$TMP_DIR/clean.txt" ]; then
        print_pass "Exit code 127 for command not found"
        echo "  ✓ exit code 127" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Exit code 127 - Command not found should return 127"
        FAILED_TESTS+=("Exit code 127")
        FAILED_DETAILS+=("Command not found should set exit code to 127")
        echo "  ✗ exit code 127" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test exit code with cd builtin (success)
    echo -e "cd /tmp\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/result.txt" | grep -v "^\$" | grep "^0$" > "$TMP_DIR/clean.txt"
    if [ -s "$TMP_DIR/clean.txt" ]; then
        print_pass "Exit code 0 for successful cd"
        echo "  ✓ cd exit code 0" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Exit code for cd - Should be 0 after successful cd"
        FAILED_TESTS+=("cd exit code")
        FAILED_DETAILS+=("cd to valid directory should return 0")
        echo "  ✗ cd exit code 0" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test exit code with cd builtin (failure)
    echo -e "cd /nonexistent_dir_12345\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/result.txt" | grep -v "^\$" | grep -E "^[1-9][0-9]*$" > "$TMP_DIR/clean.txt"
    if [ -s "$TMP_DIR/clean.txt" ]; then
        print_pass "Exit code non-zero for failed cd"
        echo "  ✓ cd exit code non-zero" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Exit code for failed cd - Should be non-zero"
        FAILED_TESTS+=("cd failed exit code")
        FAILED_DETAILS+=("cd to invalid directory should return non-zero")
        echo "  ✗ cd exit code non-zero" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test exit with explicit code
    echo -e "exit 42" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    local exit_code=$?
    ((TESTS_TOTAL++))
    if [ $exit_code -eq 42 ]; then
        print_pass "Exit with code 42"
        echo "  ✓ exit 42" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Exit code 42 - Expected 42, got: $exit_code"
        FAILED_TESTS+=("Exit 42")
        FAILED_DETAILS+=("exit 42 should exit with code 42")
        echo "  ✗ exit 42" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test exit code propagation through pipe
    echo -e "/bin/false | echo test\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | bash --norc --noprofile > $TMP_DIR/bash_result.txt 2>&1"
    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/result.txt" | grep -v "^\$" | tail -1 > "$TMP_DIR/ms_exit.txt"
    tail -1 "$TMP_DIR/bash_result.txt" > "$TMP_DIR/bash_exit.txt"
    if diff -q "$TMP_DIR/ms_exit.txt" "$TMP_DIR/bash_exit.txt" > /dev/null 2>&1; then
        print_pass "Exit code propagation through pipe"
        echo "  ✓ pipe exit code" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Pipe exit code - Minishell: $(cat $TMP_DIR/ms_exit.txt) vs Bash: $(cat $TMP_DIR/bash_exit.txt)"
        FAILED_TESTS+=("Pipe exit code")
        FAILED_DETAILS+=("Exit code through pipe doesn't match bash")
        echo "  ✗ pipe exit code" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test export exit code
    echo -e "export TEST_VAR=value\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/result.txt" | grep -v "^\$" | grep "^0$" > "$TMP_DIR/clean.txt"
    if [ -s "$TMP_DIR/clean.txt" ]; then
        print_pass "Exit code 0 for export"
        echo "  ✓ export exit code" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Export exit code - Should be 0"
        FAILED_TESTS+=("export exit code")
        FAILED_DETAILS+=("export should return 0 on success")
        echo "  ✗ export exit code" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test unset exit code
    echo -e "unset PATH\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/result.txt" | grep -v "^\$" | grep "^0$" > "$TMP_DIR/clean.txt"
    if [ -s "$TMP_DIR/clean.txt" ]; then
        print_pass "Exit code 0 for unset"
        echo "  ✓ unset exit code" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Unset exit code - Should be 0"
        FAILED_TESTS+=("unset exit code")
        FAILED_DETAILS+=("unset should return 0")
        echo "  ✗ unset exit code" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test env exit code
    echo -e "env\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    ((TESTS_TOTAL++))
    grep -v "^minishell" "$TMP_DIR/result.txt" | grep -v "^\$" | grep "^0$" > "$TMP_DIR/clean.txt"
    if [ -s "$TMP_DIR/clean.txt" ]; then
        print_pass "Exit code 0 for env"
        echo "  ✓ env exit code" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Env exit code - Should be 0"
        FAILED_TESTS+=("env exit code")
        FAILED_DETAILS+=("env should return 0")
        echo "  ✗ env exit code" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_variable_expansion_advanced() {
    print_section "TEST 20: Variable Expansion - Advanced Edge Cases"
    echo "Test 20: Variable Expansion Advanced" >> "$REPORT_FILE"

    print_test_header "Testing advanced variable expansion scenarios..."

    # Variable expansion edge cases
    local expansion_tests=(
        "echo \$"
        "echo \$\$"
        "echo \$123"
        "echo \${HOME}"
        "echo \$HOME\$PATH"
        "echo \$HOME/\$USER"
        "echo prefix\$HOMEsuffix"
        "echo \$NONEXISTENT\$HOME"
        "echo \"\$HOME\""
        "echo '\$HOME'"
        "echo \$HOME'\$PATH'"
        "echo \"\$HOME'\$PATH'\""
        "echo \$?"
        "echo \$? \$? \$?"
        "/bin/false; echo \$?"
        "/bin/true; echo \$?"
        "echo test\$\$test"
        "echo \\\$HOME"
        "echo \"\\\$HOME\""
        "echo test > /dev/null; echo \$?"
    )

    for test_cmd in "${expansion_tests[@]}"; do
        run_and_compare "$test_cmd" "var expand: ${test_cmd:0:30}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_quotes_edge_cases() {
    print_section "TEST 21: Quote Handling - Edge Cases"
    echo "Test 21: Quote Edge Cases" >> "$REPORT_FILE"

    print_test_header "Testing quote edge cases and complex mixing..."

    local quote_tests=(
        "echo \"'hello'\""
        "echo '\"hello\"'"
        "echo \"'\"hello\"'\""
        "echo '\"'hello'\"'"
        "echo \"test\\\$HOME\""
        "echo 'test\\\$HOME'"
        "echo \"test'with'quotes\""
        "echo 'test\"with\"quotes'"
        "echo \"multiple  spaces   preserved\""
        "echo 'multiple  spaces   preserved'"
        "echo \"tab\t\there\""
        "echo 'tab\t\there'"
        "echo \"\""
        "echo ''"
        "echo \"\" \"\" \"\""
        "echo '' '' ''"
        "echo \"\\\"escaped quotes\\\"\""
        "echo 'can\\'t escape in single'"
        "echo \"mix 'single' in double\""
        "echo 'mix \"double\" in single'"
        "echo \"test\ntest\""
        "echo 'test\ntest'"
        "echo \"'\$HOME'\""
        "echo '\"\$HOME\"'"
        "echo \"\$HOME\"\$USER"
        "echo '\$HOME'\$USER"
    )

    for test_cmd in "${quote_tests[@]}"; do
        run_and_compare "$test_cmd" "quote: ${test_cmd:0:30}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_pipes_extreme() {
    print_section "TEST 22: Pipes - Extreme Multi-Pipe Testing"
    echo "Test 22: Pipes Extreme" >> "$REPORT_FILE"

    print_test_header "Testing extreme pipe scenarios (5-10 pipes)..."

    # Create test data
    seq 1 1000 > "$TMP_DIR/numbers.txt"

    local extreme_pipe_tests=(
        "echo test | cat | cat | cat | cat | cat"
        "echo test | cat | cat | cat | cat | cat | cat"
        "echo test | cat | cat | cat | cat | cat | cat | cat"
        "echo hello world | cat | cat | cat | cat | cat | cat | cat | cat"
        "echo test | cat | cat | cat | cat | cat | cat | cat | cat | cat"
        "cat $TMP_DIR/numbers.txt | head -100 | tail -50 | head -25 | tail -10"
        "cat $TMP_DIR/numbers.txt | grep 5 | grep 0 | wc -l"
        "echo a b c d e | cat | cat | cat | grep b | cat"
        "cat $TMP_DIR/numbers.txt | head -500 | tail -250 | grep 2 | head -10"
        "echo test | cat | grep test | cat | cat | cat"
    )

    for test_cmd in "${extreme_pipe_tests[@]}"; do
        run_and_compare "$test_cmd" "extreme pipe: ${test_cmd:0:25}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_redirections_advanced() {
    print_section "TEST 23: Redirections - Advanced Combinations"
    echo "Test 23: Redirections Advanced" >> "$REPORT_FILE"

    print_test_header "Testing advanced redirection combinations..."

    # Multiple redirections
    echo "test content" > "$TMP_DIR/input1.txt"
    echo "more content" > "$TMP_DIR/input2.txt"

    local redir_tests=(
        "cat < $TMP_DIR/input1.txt > $TMP_DIR/output1.txt"
        "cat < $TMP_DIR/input1.txt < $TMP_DIR/input2.txt"
        "echo test > $TMP_DIR/out.txt > $TMP_DIR/out2.txt"
        "echo line1 > $TMP_DIR/multi.txt; echo line2 >> $TMP_DIR/multi.txt"
        "cat < $TMP_DIR/input1.txt >> $TMP_DIR/append.txt"
        "echo test > $TMP_DIR/a.txt; cat < $TMP_DIR/a.txt"
        "echo test > $TMP_DIR/b.txt; echo test2 >> $TMP_DIR/b.txt; cat $TMP_DIR/b.txt"
    )

    for test_cmd in "${redir_tests[@]}"; do
        run_and_compare "$test_cmd" "redir advanced: ${test_cmd:0:25}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_pipes_and_redirections_combined() {
    print_section "TEST 24: Pipes + Redirections - Combined"
    echo "Test 24: Pipes + Redirections Combined" >> "$REPORT_FILE"

    print_test_header "Testing combinations of pipes and redirections..."

    echo "test data" > "$TMP_DIR/data.txt"

    local combined_tests=(
        "cat < $TMP_DIR/data.txt | cat"
        "echo test | cat > $TMP_DIR/pipe_out.txt"
        "cat $TMP_DIR/data.txt | cat | cat > $TMP_DIR/multi_pipe_out.txt"
        "echo test | cat | cat | cat > $TMP_DIR/final.txt"
        "cat < $TMP_DIR/data.txt | cat | cat > $TMP_DIR/result.txt"
        "echo line1 > $TMP_DIR/temp.txt; cat $TMP_DIR/temp.txt | cat"
        "echo test | cat | cat > $TMP_DIR/out.txt; cat $TMP_DIR/out.txt"
    )

    for test_cmd in "${combined_tests[@]}"; do
        run_and_compare "$test_cmd" "pipe+redir: ${test_cmd:0:25}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_builtins_edge_cases() {
    print_section "TEST 25: Builtins - Edge Cases"
    echo "Test 25: Builtins Edge Cases" >> "$REPORT_FILE"

    print_test_header "Testing builtin commands with edge cases..."

    # pwd edge cases
    run_and_compare "pwd" "pwd: basic"
    run_and_compare "pwd; cd /tmp; pwd" "pwd: after cd"
    run_and_compare "pwd; pwd; pwd" "pwd: multiple calls"

    # cd edge cases
    run_and_compare "cd" "cd: no argument (HOME)"
    run_and_compare "cd /" "cd: to root"
    run_and_compare "cd /tmp; pwd" "cd: verify with pwd"
    run_and_compare "cd /nonexistent" "cd: to nonexistent"
    run_and_compare "cd .." "cd: parent directory"
    run_and_compare "cd .; pwd" "cd: current directory"
    run_and_compare "cd -" "cd: previous directory"

    # echo edge cases (already covered but adding more)
    run_and_compare "echo" "echo: no arguments"
    run_and_compare "echo -n" "echo: -n only"
    run_and_compare "echo -n -n -n" "echo: multiple -n"
    run_and_compare "echo -nnn test" "echo: -nnn variant"

    # env edge cases
    run_and_compare "env" "env: basic"
    run_and_compare "env | grep PATH" "env: with pipe"

    # export edge cases
    run_and_compare "export" "export: no arguments"
    run_and_compare "export TEST=value" "export: new variable"
    run_and_compare "export TEST=value; echo \$TEST" "export: verify"
    run_and_compare "export EMPTY=" "export: empty value"
    run_and_compare "export SPACE=' '" "export: space value"
    run_and_compare "export MULTI='a b c'" "export: multiple words"

    # unset edge cases
    run_and_compare "unset" "unset: no arguments"
    run_and_compare "unset NONEXISTENT" "unset: nonexistent var"
    run_and_compare "export TEST=1; unset TEST; echo \$TEST" "unset: verify removal"

    # exit edge cases
    run_and_compare "exit 0" "exit: with 0"
    run_and_compare "exit 1" "exit: with 1"
    run_and_compare "exit 255" "exit: with 255"
    run_and_compare "exit 256" "exit: overflow 256"
    run_and_compare "exit -1" "exit: negative"
    run_and_compare "exit abc" "exit: non-numeric"

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_command_not_found() {
    print_section "TEST 26: Command Not Found Handling"
    echo "Test 26: Command Not Found" >> "$REPORT_FILE"

    print_test_header "Testing command not found scenarios..."

    local not_found_tests=(
        "nonexistentcommand"
        "cmddoesnotexist123"
        "./nonexistent_binary"
        "/nonexistent/path/command"
        "abc123xyz789"
        "test_fake_cmd"
        ""
    )

    for test_cmd in "${not_found_tests[@]}"; do
        if [ -n "$test_cmd" ]; then
            echo -e "$test_cmd\necho \$?\nexit" > "$TMP_DIR/test.txt"
            timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
            ((TESTS_TOTAL++))

            if grep -q "command not found\|not found\|127" "$TMP_DIR/result.txt"; then
                print_pass "Command not found: $test_cmd"
                echo "  ✓ not found: $test_cmd" >> "$REPORT_FILE"
                ((TESTS_PASSED++))
            else
                print_fail "Command not found handling: $test_cmd"
                FAILED_TESTS+=("Not found: $test_cmd")
                FAILED_DETAILS+=("Should show 'command not found' error")
                echo "  ✗ not found: $test_cmd" >> "$REPORT_FILE"
                ((TESTS_FAILED++))
            fi
        fi
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_paths_with_spaces() {
    print_section "TEST 27: Paths with Spaces and Special Characters"
    echo "Test 27: Paths with Spaces" >> "$REPORT_FILE"

    print_test_header "Testing paths with spaces and special characters..."

    # Create test directories and files with spaces
    mkdir -p "$TMP_DIR/dir with spaces"
    echo "content" > "$TMP_DIR/dir with spaces/file.txt"
    mkdir -p "$TMP_DIR/dir-with-dash"
    echo "dash content" > "$TMP_DIR/dir-with-dash/file.txt"
    mkdir -p "$TMP_DIR/dir_with_underscore"
    echo "underscore" > "$TMP_DIR/dir_with_underscore/file.txt"

    local space_tests=(
        "echo '$TMP_DIR/dir with spaces/file.txt'"
        "cat '$TMP_DIR/dir with spaces/file.txt'"
        "ls '$TMP_DIR/dir with spaces'"
        "echo \"$TMP_DIR/dir with spaces/file.txt\""
        "cat $TMP_DIR/dir-with-dash/file.txt"
        "cat $TMP_DIR/dir_with_underscore/file.txt"
        "echo test > '$TMP_DIR/dir with spaces/output.txt'"
        "ls '$TMP_DIR/dir with spaces' | cat"
    )

    for test_cmd in "${space_tests[@]}"; do
        run_and_compare "$test_cmd" "path spaces: ${test_cmd:0:25}"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}
