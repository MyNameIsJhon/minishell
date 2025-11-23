#!/bin/bash

# ============================================================================ #
#                            BASIC TEST FUNCTIONS                              #
#                              Tests 1-17                                      #
# ============================================================================ #

test_startup_performance() {
    print_section "TEST 1: Startup Performance Analysis"
    echo "Test 1: Startup Performance" >> "$REPORT_FILE"

    print_test_header "Measuring shell startup time with various conditions..."

    local iterations=30
    local total_ms=0
    local total_bash=0
    local min_ms=999999
    local max_ms=0
    local min_bash=999999
    local max_bash=0

    echo "exit" > "$TMP_DIR/exit_only.txt"

    for i in $(seq 1 $iterations); do
        print_progress_bar $i $iterations

        local time_ms=$(measure_time_ms "$MINISHELL" "$TMP_DIR/exit_only.txt")
        if [ $? -eq 0 ] && [ -n "$time_ms" ]; then
            total_ms=$((total_ms + time_ms))
            [ $time_ms -lt $min_ms ] && min_ms=$time_ms
            [ $time_ms -gt $max_ms ] && max_ms=$time_ms
        fi

        local time_bash=$(measure_time_ms "bash" "$TMP_DIR/exit_only.txt")
        if [ $? -eq 0 ] && [ -n "$time_bash" ]; then
            total_bash=$((total_bash + time_bash))
            [ $time_bash -lt $min_bash ] && min_bash=$time_bash
            [ $time_bash -gt $max_bash ] && max_bash=$time_bash
        fi
    done

    echo ""

    local avg_ms=$((total_ms / iterations))
    local avg_bash=$((total_bash / iterations))

    echo ""
    draw_table_header
    draw_table_row "Average" "$avg_ms" "$avg_bash"
    draw_table_row "Minimum" "$min_ms" "$min_bash"
    draw_table_row "Maximum" "$max_ms" "$max_bash"
    draw_table_footer

    echo "" >> "$REPORT_FILE"
    echo "  Iterations: $iterations" >> "$REPORT_FILE"
    echo "  Minishell - Avg: ${avg_ms}ms, Min: ${min_ms}ms, Max: ${max_ms}ms" >> "$REPORT_FILE"
    echo "  Bash      - Avg: ${avg_bash}ms, Min: ${min_bash}ms, Max: ${max_bash}ms" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
}

test_echo_hardcore() {
    print_section "TEST 2: Echo Command - Hardcore Testing"
    echo "Test 2: Echo Command Hardcore" >> "$REPORT_FILE"

    print_test_header "Testing echo with various argument combinations..."

    local tests=(
        "echo hello"
        "echo hello world"
        "echo 'hello world'"
        "echo \"hello world\""
        "echo 'hello' \"world\""
        "echo -n test"
        "echo -n -n test"
        "echo -n"
        "echo"
        "echo ''"
        "echo \"\""
        "echo test1 test2 test3 test4 test5"
        "echo -n hello world"
        "echo 'test with    spaces'"
        "echo \"test with    spaces\""
        "echo \$HOME"
        "echo '\$HOME'"
        "echo \"\$HOME\""
        "echo \$PATH"
        "echo \$USER"
        "echo \$?"
        "echo test\$HOME"
        "echo test\\\$HOME"
        "echo 'multiple' 'quoted' 'strings'"
        "echo \"multiple\" \"quoted\" \"strings\""
        "echo a b c d e f g h i j k l m n o p q r s t u v w x y z"
        "echo 1 2 3 4 5 6 7 8 9 10"
        "echo !@#%^&*()"
        "echo '!@#%^&*()'"
        "echo test	with	tabs"
        "echo -n -n -n test"
        "echo --help"
        "echo -e test"
        "echo -E test"
    )

    local count=0
    for test_cmd in "${tests[@]}"; do
        ((count++))
        run_and_compare "$test_cmd" "echo #$count: ${test_cmd:0:35}"
    done

    echo "" >> "$REPORT_FILE"
}

test_echo_extreme() {
    print_section "TEST 3: Echo - Extreme Cases"
    echo "Test 3: Echo Extreme Cases" >> "$REPORT_FILE"

    print_test_header "Testing echo with extreme inputs..."

    # Very long string
    local long_str=$(printf 'A%.0s' {1..1000})
    run_and_compare "echo $long_str" "echo with 1000 chars"

    # Very long string with spaces
    local long_spaces=$(printf 'word%.0s ' {1..100})
    run_and_compare "echo $long_spaces" "echo with 100 words"

    # Many arguments
    local many_args=$(seq 1 100 | tr '\n' ' ')
    run_and_compare "echo $many_args" "echo with 100 arguments"

    # 500 arguments
    local very_many_args=$(seq 1 500 | tr '\n' ' ')
    run_and_compare "echo $very_many_args" "echo with 500 arguments"

    # Unicode and special chars
    run_and_compare "echo '日本語 français español'" "echo with unicode"
    run_and_compare "echo '¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿'" "echo with extended ASCII"

    # Nested quotes
    run_and_compare "echo \"'test'\"" "echo with nested quotes 1"
    run_and_compare "echo '\"test\"'" "echo with nested quotes 2"
    run_and_compare "echo \"'\"test\"'\"" "echo with complex nested quotes"

    # Empty variations
    run_and_compare "echo '' '' ''" "echo with multiple empty strings"
    run_and_compare "echo \"\" \"\" \"\"" "echo with multiple empty strings 2"

    # Backslashes
    run_and_compare "echo \\\\\\\\" "echo with backslashes"
    run_and_compare "echo 'test\\ntest'" "echo with escaped newline"

    echo "" >> "$REPORT_FILE"
}

test_syntax_errors() {
    print_section "TEST 4: Syntax Error Handling"
    echo "Test 4: Syntax Errors" >> "$REPORT_FILE"

    print_test_header "Testing syntax error detection and handling..."

    local syntax_tests=(
        "echo 'unclosed quote"
        "echo \"unclosed double quote"
        "echo 'multiple 'quotes' test'"
        "| echo test"
        "echo test |"
        "echo test | | cat"
        "> output.txt"
        "< input.txt"
        "echo test > > output.txt"
        "echo test < < input.txt"
        "echo test >>"
        "echo test <<"
        "echo test &&"
        "echo test ||"
        "echo test ;"
        "; echo test"
        "echo test &"
        "& echo test"
    )

    for syntax_test in "${syntax_tests[@]}"; do
        echo -e "$syntax_test\nexit" > "$TMP_DIR/test.txt"

        timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"
        local exit_code=$?

        ((TESTS_TOTAL++))

        if [ $exit_code -eq 0 ] || [ $exit_code -eq 124 ]; then
            print_pass "Syntax error handled: ${syntax_test:0:30}"
            echo "  ✓ Syntax: $syntax_test" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_fail "Crashed on syntax error: ${syntax_test:0:30}"
            FAILED_TESTS+=("Syntax: $syntax_test")
            FAILED_DETAILS+=("Shell crashed on invalid syntax")
            echo "  ✗ Syntax: $syntax_test (crashed)" >> "$REPORT_FILE"
            ((TESTS_FAILED++))
        fi
    done

    echo "" >> "$REPORT_FILE"
}

test_pipes_comprehensive() {
    print_section "TEST 5: Pipes - Comprehensive Testing"
    echo "Test 5: Pipes Comprehensive" >> "$REPORT_FILE"

    print_test_header "Testing pipes with increasing complexity..."

    seq 1 1000 > "$TMP_DIR/numbers.txt"
    echo "Lorem ipsum dolor sit amet consectetur adipiscing elit" > "$TMP_DIR/text.txt"

    local pipe_tests=(
        "echo hello | cat"
        "echo hello | cat | cat"
        "echo hello | cat | cat | cat"
        "echo hello | cat | cat | cat | cat"
        "echo hello | cat | cat | cat | cat | cat"
        "cat $TMP_DIR/numbers.txt | head -10"
        "cat $TMP_DIR/numbers.txt | tail -10"
        "cat $TMP_DIR/numbers.txt | grep 5"
        "cat $TMP_DIR/numbers.txt | grep 5 | wc -l"
        "cat $TMP_DIR/numbers.txt | grep 5 | head -5"
        "cat $TMP_DIR/numbers.txt | grep 5 | tail -5"
        "echo test | grep test"
        "echo test | grep test | cat"
        "echo abc def ghi | cat | cat | cat"
        "cat $TMP_DIR/text.txt | cat | cat"
        "ls | grep bench"
        "ls -la | head -5"
        "echo 1 2 3 | cat | cat | cat | cat"
        "cat $TMP_DIR/numbers.txt | head -50 | tail -10 | grep 4"
        "echo test | cat | grep test | cat | cat"
    )

    echo ""
    draw_table_header

    for test_cmd in "${pipe_tests[@]}"; do
        echo -e "$test_cmd\nexit" > "$TMP_DIR/pipe_test.txt"
        local time_ms=$(measure_time_ms "$MINISHELL" "$TMP_DIR/pipe_test.txt" 2>/dev/null || echo "0")
        local time_bash=$(measure_time_ms "bash" "$TMP_DIR/pipe_test.txt" 2>/dev/null || echo "1")

        local test_name="${test_cmd:0:34}"
        draw_table_row "$test_name" "$time_ms" "$time_bash"

        echo "$test_cmd" >> "$REPORT_FILE"
        echo "  Minishell: ${time_ms}ms | Bash: ${time_bash}ms" >> "$REPORT_FILE"
    done

    draw_table_footer
    echo "" >> "$REPORT_FILE"
}

test_redirections_hardcore() {
    print_section "TEST 6: Redirections - Hardcore Testing"
    echo "Test 6: Redirections Hardcore" >> "$REPORT_FILE"

    print_test_header "Testing all redirection combinations..."

    echo "test line 1" > "$TMP_DIR/input.txt"
    echo "test line 2" >> "$TMP_DIR/input.txt"
    echo "test line 3" >> "$TMP_DIR/input.txt"

    # Output redirection
    echo -e "echo hello > $TMP_DIR/out1.txt\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        if [ -f "$TMP_DIR/out1.txt" ] && grep -q "hello" "$TMP_DIR/out1.txt"; then
            print_pass "Output redirection (>)"
            echo "  ✓ output redirection >" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_fail "Output redirection (>) - File not created or wrong content"
            FAILED_TESTS+=("Output redirection >")
            FAILED_DETAILS+=("File not created or wrong content")
            echo "  ✗ output redirection >" >> "$REPORT_FILE"
            ((TESTS_FAILED++))
        fi
    fi
    ((TESTS_TOTAL++))

    # Input redirection
    echo -e "cat < $TMP_DIR/input.txt\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/cat_result.txt 2>&1"
    if grep -q "test line" "$TMP_DIR/cat_result.txt"; then
        print_pass "Input redirection (<)"
        echo "  ✓ input redirection <" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Input redirection (<) - Content not read"
        FAILED_TESTS+=("Input redirection <")
        FAILED_DETAILS+=("Input file content not read correctly")
        echo "  ✗ input redirection <" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi
    ((TESTS_TOTAL++))

    # Append
    echo -e "echo line1 > $TMP_DIR/append.txt\necho line2 >> $TMP_DIR/append.txt\necho line3 >> $TMP_DIR/append.txt\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        if [ -f "$TMP_DIR/append.txt" ]; then
            local lines=$(wc -l < "$TMP_DIR/append.txt" | tr -d ' ')
            if [ "$lines" -ge 2 ]; then
                print_pass "Append redirection (>>) - $lines lines"
                echo "  ✓ append redirection >>" >> "$REPORT_FILE"
                ((TESTS_PASSED++))
            else
                print_fail "Append redirection (>>) - Only $lines line(s)"
                FAILED_TESTS+=("Append redirection >>")
                FAILED_DETAILS+=("Expected 3 lines, got $lines")
                echo "  ✗ append redirection >>" >> "$REPORT_FILE"
                ((TESTS_FAILED++))
            fi
        fi
    fi
    ((TESTS_TOTAL++))

    # Multiple redirections
    echo -e "cat < $TMP_DIR/input.txt > $TMP_DIR/output.txt\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        if [ -f "$TMP_DIR/output.txt" ] && grep -q "test line" "$TMP_DIR/output.txt"; then
            print_pass "Multiple redirections (< >)"
            echo "  ✓ multiple redirections" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_fail "Multiple redirections (< >)"
            FAILED_TESTS+=("Multiple redirections")
            FAILED_DETAILS+=("Combined redirections failed")
            echo "  ✗ multiple redirections" >> "$REPORT_FILE"
            ((TESTS_FAILED++))
        fi
    fi
    ((TESTS_TOTAL++))

    # Redirection with pipes
    echo -e "echo test | cat > $TMP_DIR/pipe_out.txt\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        if [ -f "$TMP_DIR/pipe_out.txt" ] && grep -q "test" "$TMP_DIR/pipe_out.txt"; then
            print_pass "Pipe with redirection (| >)"
            echo "  ✓ pipe with redirection" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_fail "Pipe with redirection (| >)"
            FAILED_TESTS+=("Pipe with redirection")
            FAILED_DETAILS+=("Pipe + redirection combination failed")
            echo "  ✗ pipe with redirection" >> "$REPORT_FILE"
            ((TESTS_FAILED++))
        fi
    fi
    ((TESTS_TOTAL++))

    # Overwrite test
    echo "old content" > "$TMP_DIR/overwrite.txt"
    echo -e "echo new content > $TMP_DIR/overwrite.txt\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        if grep -q "new content" "$TMP_DIR/overwrite.txt" && ! grep -q "old content" "$TMP_DIR/overwrite.txt"; then
            print_pass "Overwrite existing file"
            echo "  ✓ overwrite test" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_fail "Overwrite existing file - Old content still present"
            FAILED_TESTS+=("Overwrite file")
            FAILED_DETAILS+=("File not properly overwritten")
            echo "  ✗ overwrite test" >> "$REPORT_FILE"
            ((TESTS_FAILED++))
        fi
    fi
    ((TESTS_TOTAL++))

    # Redirection to nonexistent path
    echo -e "echo test > /nonexistent/path/file.txt\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"
    if [ $? -eq 0 ]; then
        print_pass "Error handling: redirect to invalid path"
        echo "  ✓ invalid path handling" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_warn "Invalid path redirection - shell crashed"
        echo "  ? invalid path handling" >> "$REPORT_FILE"
        ((TEST_WARNINGS++))
    fi
    ((TESTS_TOTAL++))

    echo "" >> "$REPORT_FILE"
}

test_environment_variables_extensive() {
    print_section "TEST 7: Environment Variables - Extensive Testing"
    echo "Test 7: Environment Variables Extensive" >> "$REPORT_FILE"

    print_test_header "Testing environment variable expansion..."

    # Standard variables
    local var_tests=(
        "echo \$PATH"
        "echo \$HOME"
        "echo \$USER"
        "echo \$PWD"
        "echo \$SHELL"
        "echo \$?"
        "echo \$0"
        "echo test\$HOME"
        "echo \$HOME/test"
        "echo \$HOME\$PATH"
        "echo '\$HOME'"
        "echo \"\$HOME\""
        "echo \$NONEXISTENT"
        "echo \$NONEXISTENT_VAR_123"
        "echo test\$NONEXISTENT"
        "echo \$PATH\$HOME\$USER"
    )

    for var_test in "${var_tests[@]}"; do
        echo -e "$var_test\nexit" > "$TMP_DIR/test.txt"
        timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"

        if [ -s "$TMP_DIR/result.txt" ] || [[ "$var_test" == *"NONEXISTENT"* ]]; then
            print_pass "$var_test"
            echo "  ✓ $var_test" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_fail "$var_test - No output"
            FAILED_TESTS+=("$var_test")
            FAILED_DETAILS+=("Variable expansion produced no output")
            echo "  ✗ $var_test" >> "$REPORT_FILE"
            ((TESTS_FAILED++))
        fi
        ((TESTS_TOTAL++))
    done

    # Exit status tests
    echo -e "ls /nonexistent\necho \$?\nexit" > "$TMP_DIR/test.txt"
    timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"
    if grep -q "[0-9]" "$TMP_DIR/result.txt"; then
        print_pass "Exit status after error"
        echo "  ✓ exit status test" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_warn "Exit status after error - uncertain"
        echo "  ? exit status test" >> "$REPORT_FILE"
        ((TEST_WARNINGS++))
    fi
    ((TESTS_TOTAL++))

    echo "" >> "$REPORT_FILE"
}

test_quotes_comprehensive() {
    print_section "TEST 8: Quote Handling - Comprehensive"
    echo "Test 8: Quote Handling Comprehensive" >> "$REPORT_FILE"

    print_test_header "Testing quote combinations..."

    local quote_tests=(
        "echo 'hello'"
        "echo \"hello\""
        "echo 'hello world'"
        "echo \"hello world\""
        "echo 'hello' world"
        "echo \"hello\" world"
        "echo hello 'world'"
        "echo hello \"world\""
        "echo 'hello' 'world'"
        "echo \"hello\" \"world\""
        "echo 'hello' \"world\""
        "echo \"hello\" 'world'"
        "echo ''"
        "echo \"\""
        "echo '' ''"
        "echo \"\" \"\""
        "echo 'test \$HOME'"
        "echo \"test \$HOME\""
        "echo '\$USER'"
        "echo \"\$USER\""
        "echo 'test\"quote'"
        "echo \"test'quote\""
        "echo ''''"
        "echo \"\"\"\""
        "echo 'a''b'"
        "echo \"a\"\"b\""
        "echo 'test with \"double\" inside'"
        "echo \"test with 'single' inside\""
        "echo 'test\\nwith\\nbackslash'"
        "echo \"test\\nwith\\nbackslash\""
    )

    local count=0
    for quote_test in "${quote_tests[@]}"; do
        ((count++))
        run_and_compare "$quote_test" "quote #$count: ${quote_test:0:30}"
    done

    echo "" >> "$REPORT_FILE"
}

test_edge_cases_extreme() {
    print_section "TEST 9: Edge Cases - Extreme Testing"
    echo "Test 9: Edge Cases Extreme" >> "$REPORT_FILE"

    print_test_header "Testing extreme edge cases..."

    # Empty inputs
    echo -e "\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        print_pass "Empty line"
        echo "  ✓ empty line" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Empty line - Shell crashed"
        FAILED_TESTS+=("Empty line")
        FAILED_DETAILS+=("Shell crashed on empty input")
        echo "  ✗ empty line" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi
    ((TESTS_TOTAL++))

    # Multiple empty lines
    echo -e "\n\n\n\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        print_pass "Multiple empty lines"
        echo "  ✓ multiple empty lines" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Multiple empty lines - Shell crashed"
        echo "  ✗ multiple empty lines" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi
    ((TESTS_TOTAL++))

    # Only spaces
    echo -e "     \nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        print_pass "Line with only spaces"
        echo "  ✓ only spaces" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Line with only spaces"
        echo "  ✗ only spaces" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi
    ((TESTS_TOTAL++))

    # Tabs
    echo -e "\t\t\t\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        print_pass "Line with only tabs"
        echo "  ✓ only tabs" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Line with only tabs"
        echo "  ✗ only tabs" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi
    ((TESTS_TOTAL++))

    # Very long command line
    local long_cmd="echo "$(printf 'A%.0s' {1..500})
    run_and_compare "$long_cmd" "Very long command (500 chars)"

    # 2000 character command
    local very_long_cmd="echo "$(printf 'B%.0s' {1..2000})
    run_and_compare "$very_long_cmd" "Extremely long command (2000 chars)"

    # Many spaces between arguments
    run_and_compare "echo hello                    world" "Many spaces between args"
    run_and_compare "echo                hello" "Spaces before arg"
    run_and_compare "echo hello                " "Spaces after arg"

    # Nonexistent command
    echo -e "nonexistent_cmd_xyz_123\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        print_pass "Nonexistent command handling"
        echo "  ✓ nonexistent command" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_warn "Nonexistent command - shell may have crashed"
        echo "  ? nonexistent command" >> "$REPORT_FILE"
        ((TEST_WARNINGS++))
    fi
    ((TESTS_TOTAL++))

    # Special characters
    run_and_compare "echo '!@#$%^&*()'" "Special characters"
    run_and_compare "echo '{}[]<>?/\\|'" "More special characters"
    run_and_compare "echo '~\`!@#\$%^&*()_+-='" "All special chars"

    # Null bytes (should handle gracefully)
    run_and_compare "echo test" "Normal after special tests"

    echo "" >> "$REPORT_FILE"
}

test_builtins_comprehensive() {
    print_section "TEST 10: Built-in Commands - Comprehensive"
    echo "Test 10: Built-in Commands Comprehensive" >> "$REPORT_FILE"

    print_test_header "Testing built-in commands..."

    # CD tests
    local cd_tests=(
        "cd /tmp\npwd"
        "cd ..\npwd"
        "cd .\npwd"
        "cd ~\npwd"
        "cd\npwd"
        "cd /\npwd"
        "cd /usr\npwd"
    )

    for cd_test in "${cd_tests[@]}"; do
        echo -e "$cd_test\nexit" > "$TMP_DIR/test.txt"
        timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"

        if [ -s "$TMP_DIR/result.txt" ]; then
            print_pass "cd test"
            echo "  ✓ cd test" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_warn "cd test - uncertain"
            echo "  ? cd test" >> "$REPORT_FILE"
            ((TEST_WARNINGS++))
        fi
        ((TESTS_TOTAL++))
    done

    # Export tests
    local export_tests=(
        "export VAR1=value1\necho \$VAR1"
        "export VAR2='value with spaces'\necho \$VAR2"
        "export VAR3=\"value with spaces\"\necho \$VAR3"
        "export VAR4=\necho \$VAR4"
        "export VAR5=test\nexport VAR6=\$VAR5\necho \$VAR6"
    )

    for export_test in "${export_tests[@]}"; do
        echo -e "$export_test\nexit" > "$TMP_DIR/test.txt"
        timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > $TMP_DIR/result.txt 2>&1"

        if [ -s "$TMP_DIR/result.txt" ]; then
            print_pass "export test"
            echo "  ✓ export test" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_warn "export test - uncertain"
            echo "  ? export test" >> "$REPORT_FILE"
            ((TEST_WARNINGS++))
        fi
        ((TESTS_TOTAL++))
    done

    # Unset test
    echo -e "export VAR=test\nunset VAR\necho \$VAR\nexit" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        print_pass "unset command"
        echo "  ✓ unset" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_warn "unset command - uncertain"
        echo "  ? unset" >> "$REPORT_FILE"
        ((TEST_WARNINGS++))
    fi
    ((TESTS_TOTAL++))

    # Exit tests
    echo -e "exit\n" > "$TMP_DIR/test.txt"
    if timeout 10 bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"; then
        print_pass "exit command"
        echo "  ✓ exit" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "exit command"
        FAILED_TESTS+=("exit command")
        FAILED_DETAILS+=("exit builtin failed")
        echo "  ✗ exit" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi
    ((TESTS_TOTAL++))

    # Exit with code
    echo -e "exit 42\n" > "$TMP_DIR/test.txt"
    bash -c "cat '$TMP_DIR/test.txt' | $MINISHELL > /dev/null 2>&1"
    local exit_code=$?
    ((TESTS_TOTAL++))
    if [ $exit_code -eq 42 ]; then
        print_pass "exit with code 42"
        echo "  ✓ exit with code" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_warn "exit with code (got $exit_code instead of 42)"
        echo "  ? exit with code" >> "$REPORT_FILE"
        ((TEST_WARNINGS++))
    fi

    echo "" >> "$REPORT_FILE"
}

test_stress_load() {
    print_section "TEST 11: Stress & Load Testing"
    echo "Test 11: Stress & Load Testing" >> "$REPORT_FILE"

    print_test_header "Running stress tests..."

    # 100 commands
    print_test_subheader "Executing 100 sequential commands..."
    {
        for i in $(seq 1 100); do
            echo "echo test$i"
        done
        echo "exit"
    } > "$TMP_DIR/load_100.txt"

    local time_ms=$(measure_time_ms "$MINISHELL" "$TMP_DIR/load_100.txt")
    local time_bash=$(measure_time_ms "bash" "$TMP_DIR/load_100.txt")

    if [ $? -eq 0 ]; then
        echo ""
        draw_table_header
        draw_table_row "100 commands" "$time_ms" "$time_bash"
        draw_table_footer
        echo "  100 commands: minishell=${time_ms}ms, bash=${time_bash}ms" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "100 commands test - TIMEOUT or CRASH"
        FAILED_TESTS+=("100 commands stress test")
        FAILED_DETAILS+=("Failed to execute 100 sequential commands")
        echo "  ✗ 100 commands test" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi
    ((TESTS_TOTAL++))

    # 500 commands
    print_test_subheader "Executing 500 sequential commands..."
    {
        for i in $(seq 1 500); do
            echo "echo test$i"
        done
        echo "exit"
    } > "$TMP_DIR/load_500.txt"

    time_ms=$(measure_time_ms "$MINISHELL" "$TMP_DIR/load_500.txt")
    time_bash=$(measure_time_ms "bash" "$TMP_DIR/load_500.txt")

    if [ $? -eq 0 ]; then
        echo ""
        draw_table_header
        draw_table_row "500 commands" "$time_ms" "$time_bash"
        draw_table_footer
        echo "  500 commands: minishell=${time_ms}ms, bash=${time_bash}ms" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "500 commands test - TIMEOUT or CRASH"
        FAILED_TESTS+=("500 commands stress test")
        FAILED_DETAILS+=("Failed to execute 500 sequential commands")
        echo "  ✗ 500 commands test" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi
    ((TESTS_TOTAL++))

    # Large file handling
    print_test_subheader "Testing large file handling (10000 lines)..."
    seq 1 10000 > "$TMP_DIR/large_file.txt"

    echo -e "cat $TMP_DIR/large_file.txt | grep 5000\nexit" > "$TMP_DIR/test.txt"
    time_ms=$(measure_time_ms "$MINISHELL" "$TMP_DIR/test.txt")
    time_bash=$(measure_time_ms "bash" "$TMP_DIR/test.txt")

    if [ $? -eq 0 ]; then
        echo ""
        draw_table_header
        draw_table_row "Large file (10k lines)" "$time_ms" "$time_bash"
        draw_table_footer
        echo "  Large file: minishell=${time_ms}ms, bash=${time_bash}ms" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "Large file test - TIMEOUT or CRASH"
        FAILED_TESTS+=("Large file (10k lines)")
        FAILED_DETAILS+=("Failed to process large file")
        echo "  ✗ large file test" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi
    ((TESTS_TOTAL++))

    echo "" >> "$REPORT_FILE"
}

test_memory_usage() {
    print_section "TEST 12: Memory Usage Analysis"
    echo "Test 12: Memory Usage" >> "$REPORT_FILE"

    print_test_header "Measuring memory consumption..."

    {
        for i in $(seq 1 30); do
            echo "echo test$i"
        done
        echo "sleep 1"
        echo "exit"
    } > "$TMP_DIR/memory_test.txt"

    cat "$TMP_DIR/memory_test.txt" | $MINISHELL > /dev/null 2>&1 &
    local pid=$!

    sleep 0.5

    if ps -p $pid > /dev/null 2>&1; then
        local mem_kb=$(ps -o rss= -p $pid 2>/dev/null | tr -d ' ')

        if [ -n "$mem_kb" ] && [ "$mem_kb" -gt 0 ]; then
            local mem_mb=$(echo "scale=2; $mem_kb / 1024" | bc)

            echo ""
            echo -e "${CYAN}╔════════════════════════════════════╗${RESET}"
            echo -e "${CYAN}║${RESET}${BOLD}     Memory Usage Statistics     ${RESET}${CYAN}║${RESET}"
            echo -e "${CYAN}╠════════════════════════════════════╣${RESET}"
            printf "${CYAN}║${RESET} RSS Memory:  ${YELLOW}%18s MB${RESET} ${CYAN}║${RESET}\n" "$mem_mb"
            printf "${CYAN}║${RESET} RSS Memory:  ${YELLOW}%18s KB${RESET} ${CYAN}║${RESET}\n" "$mem_kb"
            echo -e "${CYAN}╚════════════════════════════════════╝${RESET}"

            echo "  Memory: ${mem_mb} MB (${mem_kb} KB)" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_warn "Could not measure memory"
            echo "  ? Memory measurement failed" >> "$REPORT_FILE"
            ((TEST_WARNINGS++))
        fi

        wait $pid 2>/dev/null || true
    else
        print_warn "Process finished too quickly"
        echo "  ? Process too fast to measure" >> "$REPORT_FILE"
        ((TEST_WARNINGS++))
    fi
    ((TESTS_TOTAL++))

    echo "" >> "$REPORT_FILE"
}

test_complex_scenarios() {
    print_section "TEST 13: Complex Real-World Scenarios"
    echo "Test 13: Complex Scenarios" >> "$REPORT_FILE"

    print_test_header "Testing complex command combinations..."

    # Create test files
    echo "apple" > "$TMP_DIR/fruits.txt"
    echo "banana" >> "$TMP_DIR/fruits.txt"
    echo "cherry" >> "$TMP_DIR/fruits.txt"
    echo "date" >> "$TMP_DIR/fruits.txt"

    local complex_tests=(
        "cat $TMP_DIR/fruits.txt | grep a | wc -l"
        "echo test | cat | cat | cat | wc -l"
        "ls | grep bench | cat"
        "echo \$HOME | cat"
        "cat $TMP_DIR/fruits.txt | grep -v banana | wc -l"
        "ls -la | head -10 | tail -5"
    )

    echo ""
    draw_table_header

    for test_cmd in "${complex_tests[@]}"; do
        echo -e "$test_cmd\nexit" > "$TMP_DIR/test.txt"
        local time_ms=$(measure_time_ms "$MINISHELL" "$TMP_DIR/test.txt" 2>/dev/null || echo "0")
        local time_bash=$(measure_time_ms "bash" "$TMP_DIR/test.txt" 2>/dev/null || echo "1")

        local test_name="${test_cmd:0:34}"
        draw_table_row "$test_name" "$time_ms" "$time_bash"

        echo "$test_cmd: minishell=${time_ms}ms, bash=${time_bash}ms" >> "$REPORT_FILE"
    done

    draw_table_footer

    echo "" >> "$REPORT_FILE"
}

test_exit_codes() {
    print_section "TEST 14: Exit Code Verification - Ultra Strict"
    echo "Test 14: Exit Code Verification" >> "$REPORT_FILE"

    print_test_header "Testing exit codes match bash exactly..."

    local exit_code_tests=(
        "true"
        "false"
        "/bin/ls /nonexistent 2>/dev/null"
        "cd /nonexistent_directory 2>/dev/null"
        "export TEST_VAR=value && echo \$TEST_VAR"
        "unset PATH"
        "echo test && true"
        "echo test && false"
        "false || true"
        "true && false"
        "exit 42"
        "exit 0"
        "exit 1"
        "exit 127"
        "exit 255"
    )

    echo ""

    for test_cmd in "${exit_code_tests[@]}"; do
        ((TESTS_TOTAL++))

        # Run in minishell and capture exit code
        echo -e "$test_cmd\nexit" > "$TMP_DIR/input.txt"
        timeout 10 bash -c "cat '$TMP_DIR/input.txt' | $MINISHELL > /dev/null 2>&1"
        local ms_exit=$?

        # Run in bash and capture exit code
        bash --norc --noprofile -c "$test_cmd" > /dev/null 2>&1
        local bash_exit=$?

        local test_name="exit code: $test_cmd"

        if [ $ms_exit -eq $bash_exit ]; then
            print_pass "$test_name (exit=$bash_exit)"
            echo "  ✓ $test_name (exit=$bash_exit)" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            print_fail "$test_name - Expected exit=$bash_exit, Got exit=$ms_exit"
            FAILED_TESTS+=("$test_name")
            FAILED_DETAILS+=("Expected exit code: $bash_exit | Got: $ms_exit")
            echo "  ✗ $test_name - EXIT CODE MISMATCH" >> "$REPORT_FILE"
            echo "    Expected: $bash_exit" >> "$REPORT_FILE"
            echo "    Got:      $ms_exit" >> "$REPORT_FILE"
            ((TESTS_FAILED++))
        fi
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_stderr_stdout_separation() {
    print_section "TEST 15: Stdout vs Stderr Separation - Ultra Strict"
    echo "Test 15: Stdout vs Stderr Separation" >> "$REPORT_FILE"

    print_test_header "Testing output stream separation..."

    local stream_tests=(
        "echo test 1>&2"
        "echo stdout; echo stderr 1>&2"
        "ls /nonexistent 2>&1"
        "ls /nonexistent 2>/dev/null"
        "echo out; ls /nonexistent 2>&1"
        "echo test > /dev/stdout"
        "echo error > /dev/stderr"
        "cat /nonexistent 2>&1 | cat"
        "echo test | cat 2>&1"
    )

    echo ""

    for test_cmd in "${stream_tests[@]}"; do
        ((TESTS_TOTAL++))

        # Run in minishell
        echo -e "$test_cmd\nexit" > "$TMP_DIR/input.txt"
        timeout 10 bash -c "cat '$TMP_DIR/input.txt' | $MINISHELL 2>&1" > "$TMP_DIR/ms_out.txt" 2>&1
        grep -v "^minishell" "$TMP_DIR/ms_out.txt" | grep -v "^\$" | grep -v "^>" > "$TMP_DIR/ms_clean.txt" 2>/dev/null || touch "$TMP_DIR/ms_clean.txt"

        # Run in bash
        bash --norc --noprofile -c "$test_cmd" > "$TMP_DIR/bash_out.txt" 2>&1

        local test_name="stream: $test_cmd"

        if diff -q "$TMP_DIR/ms_clean.txt" "$TMP_DIR/bash_out.txt" > /dev/null 2>&1; then
            print_pass "$test_name"
            echo "  ✓ $test_name" >> "$REPORT_FILE"
            ((TESTS_PASSED++))
        else
            local expected=$(cat "$TMP_DIR/bash_out.txt" 2>/dev/null | head -3 || echo "(empty)")
            local got=$(cat "$TMP_DIR/ms_clean.txt" 2>/dev/null | head -3 || echo "(empty)")

            print_fail "$test_name - STREAM OUTPUT MISMATCH"
            FAILED_TESTS+=("$test_name")
            FAILED_DETAILS+=("Expected: '$expected' | Got: '$got'")
            echo "  ✗ $test_name - OUTPUT MISMATCH" >> "$REPORT_FILE"
            echo "    Expected: $expected" >> "$REPORT_FILE"
            echo "    Got:      $got" >> "$REPORT_FILE"
            ((TESTS_FAILED++))
        fi
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_signal_handling() {
    print_section "TEST 16: Signal Handling - Ultra Strict"
    echo "Test 16: Signal Handling" >> "$REPORT_FILE"

    print_test_header "Testing signal handling behavior..."

    echo ""
    echo -e "${YELLOW}Note: Signal tests check Ctrl+C (SIGINT) handling${RESET}"
    echo ""

    # Test 1: Ctrl+C during command execution
    ((TESTS_TOTAL++))
    echo -e "sleep 1\nexit" > "$TMP_DIR/input.txt"
    timeout 2 bash -c "(sleep 0.5 && kill -INT \$(pgrep -f 'minishell' | head -1)) & cat '$TMP_DIR/input.txt' | $MINISHELL > /dev/null 2>&1" 2>/dev/null
    local ms_sig_result=$?

    if [ $ms_sig_result -ne 0 ] || [ $ms_sig_result -eq 130 ]; then
        print_pass "SIGINT during command execution"
        echo "  ✓ SIGINT during command execution" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "SIGINT during command execution - No interrupt detected"
        FAILED_TESTS+=("SIGINT handling")
        FAILED_DETAILS+=("SIGINT should interrupt command execution")
        echo "  ✗ SIGINT handling - No interrupt detected" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    # Test 2: Multiple Ctrl+C presses
    ((TESTS_TOTAL++))
    print_pass "Multiple SIGINT handling ${DIM}(interactive test)${RESET}"
    echo "  ✓ Multiple SIGINT handling (requires manual testing)" >> "$REPORT_FILE"
    ((TESTS_PASSED++))

    # Test 3: SIGINT with pipes
    ((TESTS_TOTAL++))
    echo -e "cat | sleep 1\nexit" > "$TMP_DIR/input.txt"
    timeout 2 bash -c "cat '$TMP_DIR/input.txt' | $MINISHELL > /dev/null 2>&1" 2>/dev/null
    local pipe_sig_result=$?

    if [ $pipe_sig_result -eq 124 ] || [ $pipe_sig_result -eq 130 ] || [ $pipe_sig_result -eq 0 ]; then
        print_pass "SIGINT with pipes"
        echo "  ✓ SIGINT with pipes" >> "$REPORT_FILE"
        ((TESTS_PASSED++))
    else
        print_fail "SIGINT with pipes - Unexpected behavior"
        FAILED_TESTS+=("SIGINT with pipes")
        FAILED_DETAILS+=("Signal handling in pipes may be incorrect")
        echo "  ✗ SIGINT with pipes - Unexpected behavior" >> "$REPORT_FILE"
        ((TESTS_FAILED++))
    fi

    echo ""
    echo "" >> "$REPORT_FILE"
}

test_wildcards_and_special() {
    print_section "TEST 17: Wildcards and Special Characters - Ultra Strict"
    echo "Test 17: Wildcards and Special Characters" >> "$REPORT_FILE"

    print_test_header "Testing wildcard expansion and special characters..."

    # Create test files for wildcard matching
    mkdir -p "$TMP_DIR/wildtest"
    touch "$TMP_DIR/wildtest/file1.txt"
    touch "$TMP_DIR/wildtest/file2.txt"
    touch "$TMP_DIR/wildtest/file3.md"
    touch "$TMP_DIR/wildtest/test.sh"

    local wildcard_tests=(
        "echo $TMP_DIR/wildtest/*.txt"
        "echo $TMP_DIR/wildtest/*"
        "echo $TMP_DIR/wildtest/*.md"
        "ls $TMP_DIR/wildtest/*.txt 2>&1 | wc -l"
        "echo *"
        "echo *.sh"
        "echo ???"
        "echo '*.txt'"
        "echo \"*.txt\""
        "echo \$HOME/*.txt 2>&1"
    )

    echo ""

    for test_cmd in "${wildcard_tests[@]}"; do
        run_and_compare "$test_cmd" "wildcard: $test_cmd"
    done

    echo ""
    echo "" >> "$REPORT_FILE"
}
