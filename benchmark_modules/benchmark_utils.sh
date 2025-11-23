#!/bin/bash

# ============================================================================ #
#                              UTILITY FUNCTIONS                               #
# ============================================================================ #

check_minishell() {
    if [ ! -f "$MINISHELL" ]; then
        print_fail "Minishell executable not found!"
        echo -e "${YELLOW}  Run 'make' first to compile the project.${RESET}"
        exit 1
    fi

    if [ ! -x "$MINISHELL" ]; then
        print_fail "Minishell is not executable!"
        exit 1
    fi
}

init_report() {
    mkdir -p "$REPORT_DIR"
    mkdir -p "$TMP_DIR"

    cat > "$REPORT_FILE" << EOF
╔══════════════════════════════════════════════════════════════════════════╗
║                  MINISHELL PERFORMANCE REPORT                            ║
║                  Date: $(date)                           ║
╚══════════════════════════════════════════════════════════════════════════╝

EOF
}

cleanup() {
    rm -rf "$TMP_DIR"
    rm -f /tmp/minishell_test_* 2>/dev/null
}

# ============================================================================ #
#                            MEASUREMENT FUNCTIONS                             #
# ============================================================================ #

measure_time_ms() {
    local shell=$1
    local input_file=$2

    local start=$(perl -MTime::HiRes=time -e 'printf "%.0f\n", time()*1000')

    if [ "$shell" = "$MINISHELL" ]; then
        timeout 10 bash -c "cat '$input_file' | $shell > /dev/null 2>&1" || return 1
    else
        timeout 10 bash -c "cat '$input_file' | bash --norc --noprofile > /dev/null 2>&1" || return 1
    fi

    local end=$(perl -MTime::HiRes=time -e 'printf "%.0f\n", time()*1000')
    echo $((end - start))
}

run_and_compare() {
    local cmd=$1
    local test_name=$2
    local show_output=${3:-1}

    ((TESTS_TOTAL++))

    # Update category counters
    if [ -n "$CURRENT_CATEGORY_NUM" ]; then
        ((CATEGORY_TOTAL["$CURRENT_CATEGORY_NUM"]++))
    fi

    echo -e "$cmd\nexit" > "$TMP_DIR/input.txt"

    timeout 10 bash -c "cat '$TMP_DIR/input.txt' | $MINISHELL 2>&1" > "$TMP_DIR/minishell_out.txt" 2>&1
    local ms_exit=$?

    echo "$cmd" | bash --norc --noprofile > "$TMP_DIR/bash_out.txt" 2>&1
    local bash_exit=$?

    grep -v "^minishell" "$TMP_DIR/minishell_out.txt" | grep -v "^\$" | grep -v "^>" > "$TMP_DIR/minishell_clean.txt" 2>/dev/null || touch "$TMP_DIR/minishell_clean.txt"

    if [ $ms_exit -eq 124 ]; then
        print_fail "$test_name - ${RED}${BOLD}TIMEOUT${RESET}"
        FAILED_TESTS+=("$test_name")
        FAILED_DETAILS+=("TIMEOUT after 10 seconds")
        echo "  ✗ $test_name - TIMEOUT" >> "$REPORT_FILE"
        ((TESTS_FAILED++))

        # Update category counters
        if [ -n "$CURRENT_CATEGORY_NUM" ]; then
            ((CATEGORY_FAILED["$CURRENT_CATEGORY_NUM"]++))
            CATEGORY_FAILED_TESTS["$CURRENT_CATEGORY_NUM"]+="$test_name|"
        fi
        return 1
    fi

    # ULTRA-STRICT MODE: Any difference from bash is a FAILURE
    if diff -q "$TMP_DIR/minishell_clean.txt" "$TMP_DIR/bash_out.txt" > /dev/null 2>&1; then
        print_pass "$test_name"
        echo "  ✓ $test_name" >> "$REPORT_FILE"
        ((TESTS_PASSED++))

        # Update category counters
        if [ -n "$CURRENT_CATEGORY_NUM" ]; then
            ((CATEGORY_PASSED["$CURRENT_CATEGORY_NUM"]++))
        fi
        return 0
    else
        local expected=$(cat "$TMP_DIR/bash_out.txt" 2>/dev/null | head -5 || echo "(empty)")
        local got=$(cat "$TMP_DIR/minishell_clean.txt" 2>/dev/null | head -5 || echo "(empty)")

        print_fail "$test_name - ${RED}${BOLD}OUTPUT MISMATCH${RESET}"
        if [ $show_output -eq 1 ]; then
            print_error_detail "$test_name" "$expected" "$got"
        fi

        FAILED_TESTS+=("$test_name")
        FAILED_DETAILS+=("Expected: '$expected' | Got: '$got'")

        echo "  ✗ $test_name - OUTPUT MISMATCH" >> "$REPORT_FILE"
        echo "    Expected: $expected" >> "$REPORT_FILE"
        echo "    Got:      $got" >> "$REPORT_FILE"
        ((TESTS_FAILED++))

        # Update category counters
        if [ -n "$CURRENT_CATEGORY_NUM" ]; then
            ((CATEGORY_FAILED["$CURRENT_CATEGORY_NUM"]++))
            CATEGORY_FAILED_TESTS["$CURRENT_CATEGORY_NUM"]+="$test_name|"
        fi
        return 1
    fi
}
