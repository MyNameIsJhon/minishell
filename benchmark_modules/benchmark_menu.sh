#!/bin/bash

# ============================================================================ #
#                        MENU & INTERACTION FUNCTIONS                          #
# ============================================================================ #

browse_results_by_category() {
    if [ ${#CATEGORY_NAMES[@]} -eq 0 ]; then
        clear
        print_header
        echo -e "${YELLOW}${BOLD}No test results available yet.${RESET}"
        echo -e "${DIM}Run some tests first, then browse results by category.${RESET}\n"
        echo -ne "${DIM}Press Enter to continue...${RESET}"
        read
        return
    fi

    while true; do
        clear
        print_header
        echo -e "${CYAN}${BOLD}╔════════════════════════════════════════════════════════════════════════════════════╗${RESET}"
        echo -e "${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}                       BROWSE RESULTS BY CATEGORY                                 ${RESET}${CYAN}${BOLD}║${RESET}"
        echo -e "${CYAN}${BOLD}╠════════════════════════════════════════════════════════════════════════════════════╣${RESET}"
        echo -e "${CYAN}${BOLD}║${RESET} ${WHITE}${BOLD}#  │ Category Name                              │ Status    │ Pass Rate          ${RESET}${CYAN}${BOLD}║${RESET}"
        echo -e "${CYAN}${BOLD}╠════════════════════════════════════════════════════════════════════════════════════╣${RESET}"

        # Get all category numbers and sort them
        local cat_nums=($(printf '%s\n' "${!CATEGORY_NAMES[@]}" | sort -n))

        for cat_num in "${cat_nums[@]}"; do
            local cat_name="${CATEGORY_NAMES[$cat_num]}"
            local passed=${CATEGORY_PASSED[$cat_num]:-0}
            local failed=${CATEGORY_FAILED[$cat_num]:-0}
            local total=${CATEGORY_TOTAL[$cat_num]:-0}

            local percentage=0
            if [ $total -gt 0 ]; then
                percentage=$((passed * 100 / total))
            fi

            # Truncate category name to fit (increased from 30 to 42)
            cat_name="${cat_name:0:42}"

            local status_icon="✓"
            local status_color=$GREEN
            if [ $failed -gt 0 ]; then
                status_icon="✗"
                status_color=$RED
            fi

            printf "${CYAN}${BOLD}║${RESET} ${YELLOW}%2d${RESET} │ %-42s │ ${status_color}%-9s${RESET} │ " "$cat_num" "$cat_name" "$status_icon $failed fail"

            # Color code percentage
            local pct_color=$GREEN
            if [ $percentage -lt 100 ]; then pct_color=$YELLOW; fi
            if [ $percentage -lt 80 ]; then pct_color=$RED; fi

            printf "${pct_color}%d/%d (%3d%%)${RESET}       ${CYAN}${BOLD}║${RESET}\n" $passed $total $percentage
        done

        echo -e "${CYAN}${BOLD}╚════════════════════════════════════════════════════════════════════════════════════╝${RESET}"
        echo ""
        echo -e "${DIM}Enter category number to view details, or 'm' to return to main menu${RESET}"
        echo -ne "${BOLD}${CYAN}➤ Your choice: ${RESET}"
        read -r choice

        # Check if return to menu
        if [[ "$choice" == "m" ]] || [[ "$choice" == "menu" ]]; then
            return
        fi

        # Check if valid category number
        if [[ "$choice" =~ ^[0-9]+$ ]] && [ -n "${CATEGORY_NAMES[$choice]}" ]; then
            show_category_details "$choice"
        else
            echo -e "${RED}Invalid choice. Press Enter to try again...${RESET}"
            read
        fi
    done
}

show_category_details() {
    local cat_num=$1
    local cat_name="${CATEGORY_NAMES[$cat_num]}"
    local passed=${CATEGORY_PASSED[$cat_num]:-0}
    local failed=${CATEGORY_FAILED[$cat_num]:-0}
    local total=${CATEGORY_TOTAL[$cat_num]:-0}
    local failed_tests="${CATEGORY_FAILED_TESTS[$cat_num]:-}"

    clear
    print_header
    echo -e "${BLUE}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    printf "${BLUE}${BOLD}║${RESET} ${YELLOW}${BOLD}TEST #%2d${RESET} ${CYAN}│${RESET} %-58s ${BLUE}${BOLD}║${RESET}\n" "$cat_num" "$cat_name"
    echo -e "${BLUE}${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${BLUE}${BOLD}║${RESET}                                                                          ${BLUE}${BOLD}║${RESET}"
    printf "${BLUE}${BOLD}║${RESET}   ${WHITE}Total Tests:${RESET}      ${CYAN}${BOLD}%-6d${RESET}                                             ${BLUE}${BOLD}║${RESET}\n" $total
    printf "${BLUE}${BOLD}║${RESET}   ${GREEN}Tests Passed:${RESET}     ${GREEN}${BOLD}%-6d${RESET}                                             ${BLUE}${BOLD}║${RESET}\n" $passed
    printf "${BLUE}${BOLD}║${RESET}   ${RED}Tests Failed:${RESET}     ${RED}${BOLD}%-6d${RESET}                                             ${BLUE}${BOLD}║${RESET}\n" $failed

    local percentage=0
    if [ $total -gt 0 ]; then
        percentage=$((passed * 100 / total))
    fi

    local pct_color=$GREEN
    if [ $percentage -lt 100 ]; then pct_color=$YELLOW; fi
    if [ $percentage -lt 80 ]; then pct_color=$RED; fi

    printf "${BLUE}${BOLD}║${RESET}   ${WHITE}Success Rate:${RESET}     ${pct_color}${BOLD}%-3d%%${RESET}                                               ${BLUE}${BOLD}║${RESET}\n" $percentage
    echo -e "${BLUE}${BOLD}║${RESET}                                                                          ${BLUE}${BOLD}║${RESET}"
    echo -e "${BLUE}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"

    # Show failed tests if any
    if [ $failed -gt 0 ] && [ -n "$failed_tests" ]; then
        echo ""
        echo -e "${RED}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
        echo -e "${RED}${BOLD}║${RESET}${WHITE}${BOLD}                        FAILED TESTS                                     ${RESET}${RED}${BOLD}║${RESET}"
        echo -e "${RED}${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"

        # Split failed tests by delimiter
        IFS='|' read -ra failed_array <<< "$failed_tests"
        local count=1
        for test in "${failed_array[@]}"; do
            if [ -n "$test" ]; then
                printf "${RED}${BOLD}║${RESET} ${YELLOW}%2d.${RESET} %-66s ${RED}${BOLD}║${RESET}\n" "$count" "$test"
                ((count++))
            fi
        done

        echo -e "${RED}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
    else
        echo ""
        echo -e "${GREEN}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
        echo -e "${GREEN}${BOLD}║${RESET}  ${WHITE}${BOLD}✓ All tests in this category PASSED!${RESET}                                ${GREEN}${BOLD}║${RESET}"
        echo -e "${GREEN}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
    fi

    echo ""
    echo -ne "${DIM}Press Enter to return to category list...${RESET}"
    read
}

# ============================================================================ #
#                            INTERACTIVE MODE                                  #
# ============================================================================ #

interactive_mode() {
    clear
    print_header
    echo -e "${CYAN}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}                       INTERACTIVE TEST MODE                              ${RESET}${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}Test your own commands and compare outputs side-by-side${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}                                                                          ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${DIM}Commands:${RESET}                                                                ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}'quit'${RESET} or ${WHITE}'exit'${RESET} - Return to main menu                              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}'clear'${RESET}        - Clear screen                                       ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}Any command${RESET}   - Test it!                                           ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
    echo ""

    local test_count=0
    local match_count=0
    local diff_count=0

    while true; do
        echo ""
        echo -ne "${BOLD}${CYAN}➤ Enter command${RESET} ${DIM}(or 'quit' to exit)${RESET}: "
        read -r user_cmd

        # Check for exit commands
        if [[ "$user_cmd" == "quit" ]] || [[ "$user_cmd" == "exit" ]]; then
            echo ""
            echo -e "${GREEN}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
            echo -e "${GREEN}${BOLD}║${RESET}                    INTERACTIVE SESSION SUMMARY                           ${GREEN}${BOLD}║${RESET}"
            echo -e "${GREEN}${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
            printf "${GREEN}${BOLD}║${RESET}   ${WHITE}Commands tested:${RESET}  %3d                                                 ${GREEN}${BOLD}║${RESET}\n" $test_count
            printf "${GREEN}${BOLD}║${RESET}   ${GREEN}Matches:${RESET}          %3d                                                 ${GREEN}${BOLD}║${RESET}\n" $match_count
            printf "${GREEN}${BOLD}║${RESET}   ${RED}Differences:${RESET}      %3d                                                 ${GREEN}${BOLD}║${RESET}\n" $diff_count
            echo -e "${GREEN}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
            echo ""
            echo -ne "${DIM}Press Enter to return to menu...${RESET}"
            read
            return
        fi

        # Clear screen command
        if [[ "$user_cmd" == "clear" ]]; then
            clear
            print_header
            echo -e "${CYAN}Interactive Test Mode${RESET} - Commands tested: ${WHITE}$test_count${RESET}"
            continue
        fi

        # Skip empty commands
        if [[ -z "$user_cmd" ]]; then
            continue
        fi

        ((test_count++))

        echo ""
        echo -e "${YELLOW}${BOLD}════════════════════════════════════════════════════════════════════════════${RESET}"
        echo -e "${YELLOW}${BOLD}Testing:${RESET} ${WHITE}$user_cmd${RESET}"
        echo -e "${YELLOW}${BOLD}════════════════════════════════════════════════════════════════════════════${RESET}"

        # Execute with bash
        local bash_out=$(mktemp)
        local bash_err=$(mktemp)
        bash -c "$user_cmd" > "$bash_out" 2> "$bash_err"
        local bash_exit=$?
        local bash_stdout=$(cat "$bash_out")
        local bash_stderr=$(cat "$bash_err")

        # Execute with minishell
        local ms_out=$(mktemp)
        local ms_err=$(mktemp)
        echo "$user_cmd" | $MINISHELL > "$ms_out" 2> "$ms_err"
        local ms_exit=$?
        local ms_stdout=$(cat "$ms_out")
        local ms_stderr=$(cat "$ms_err")

        # Display side by side
        echo ""
        echo -e "${CYAN}${BOLD}╔════════════════════════════════╦════════════════════════════════╗${RESET}"
        echo -e "${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}          BASH OUTPUT           ${RESET}${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}       MINISHELL OUTPUT        ${RESET}${CYAN}${BOLD}║${RESET}"
        echo -e "${CYAN}${BOLD}╠════════════════════════════════╬════════════════════════════════╣${RESET}"

        # Split outputs into lines and display side by side
        IFS=$'\n' read -rd '' -a bash_lines <<< "$bash_stdout"
        IFS=$'\n' read -rd '' -a ms_lines <<< "$ms_stdout"

        local max_lines=${#bash_lines[@]}
        if [ ${#ms_lines[@]} -gt $max_lines ]; then
            max_lines=${#ms_lines[@]}
        fi

        if [ $max_lines -eq 0 ]; then
            echo -e "${CYAN}${BOLD}║${RESET} ${DIM}(no output)${RESET}                    ${CYAN}${BOLD}║${RESET} ${DIM}(no output)${RESET}                    ${CYAN}${BOLD}║${RESET}"
        else
            for ((i=0; i<max_lines; i++)); do
                local bash_line="${bash_lines[$i]:-}"
                local ms_line="${ms_lines[$i]:-}"

                # Truncate lines to fit
                bash_line="${bash_line:0:30}"
                ms_line="${ms_line:0:30}"

                # Color code based on match
                if [[ "$bash_line" == "$ms_line" ]]; then
                    printf "${CYAN}${BOLD}║${RESET} ${GREEN}%-30s${RESET} ${CYAN}${BOLD}║${RESET} ${GREEN}%-30s${RESET} ${CYAN}${BOLD}║${RESET}\n" "$bash_line" "$ms_line"
                else
                    printf "${CYAN}${BOLD}║${RESET} ${YELLOW}%-30s${RESET} ${CYAN}${BOLD}║${RESET} ${YELLOW}%-30s${RESET} ${CYAN}${BOLD}║${RESET}\n" "$bash_line" "$ms_line"
                fi
            done
        fi

        echo -e "${CYAN}${BOLD}╠════════════════════════════════╬════════════════════════════════╣${RESET}"

        # Exit codes
        local exit_color_bash=$GREEN
        local exit_color_ms=$GREEN
        if [ $bash_exit -ne $ms_exit ]; then
            exit_color_bash=$RED
            exit_color_ms=$RED
        fi

        printf "${CYAN}${BOLD}║${RESET} ${WHITE}Exit Code:${RESET} ${exit_color_bash}%-16d${RESET} ${CYAN}${BOLD}║${RESET} ${WHITE}Exit Code:${RESET} ${exit_color_ms}%-16d${RESET} ${CYAN}${BOLD}║${RESET}\n" $bash_exit $ms_exit
        echo -e "${CYAN}${BOLD}╚════════════════════════════════╩════════════════════════════════╝${RESET}"

        # Check if stderr is present
        if [[ -n "$bash_stderr" ]] || [[ -n "$ms_stderr" ]]; then
            echo ""
            echo -e "${YELLOW}${BOLD}STDERR Output:${RESET}"
            echo -e "${CYAN}${BOLD}╔════════════════════════════════╦════════════════════════════════╗${RESET}"
            echo -e "${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}             BASH               ${RESET}${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}          MINISHELL             ${RESET}${CYAN}${BOLD}║${RESET}"
            echo -e "${CYAN}${BOLD}╠════════════════════════════════╬════════════════════════════════╣${RESET}"

            IFS=$'\n' read -rd '' -a bash_err_lines <<< "$bash_stderr"
            IFS=$'\n' read -rd '' -a ms_err_lines <<< "$ms_stderr"

            local max_err_lines=${#bash_err_lines[@]}
            if [ ${#ms_err_lines[@]} -gt $max_err_lines ]; then
                max_err_lines=${#ms_err_lines[@]}
            fi

            if [ $max_err_lines -eq 0 ]; then
                echo -e "${CYAN}${BOLD}║${RESET} ${DIM}(no errors)${RESET}                    ${CYAN}${BOLD}║${RESET} ${DIM}(no errors)${RESET}                    ${CYAN}${BOLD}║${RESET}"
            else
                for ((i=0; i<max_err_lines; i++)); do
                    local bash_err_line="${bash_err_lines[$i]:-}"
                    local ms_err_line="${ms_err_lines[$i]:-}"
                    bash_err_line="${bash_err_line:0:30}"
                    ms_err_line="${ms_err_line:0:30}"
                    printf "${CYAN}${BOLD}║${RESET} ${RED}%-30s${RESET} ${CYAN}${BOLD}║${RESET} ${RED}%-30s${RESET} ${CYAN}${BOLD}║${RESET}\n" "$bash_err_line" "$ms_err_line"
                done
            fi

            echo -e "${CYAN}${BOLD}╚════════════════════════════════╩════════════════════════════════╝${RESET}"
        fi

        # Overall result
        echo ""
        if [[ "$bash_stdout" == "$ms_stdout" ]] && [ $bash_exit -eq $ms_exit ]; then
            echo -e "${GREEN}${BOLD}✓ MATCH${RESET} - Outputs and exit codes are identical!"
            ((match_count++))
        else
            echo -e "${RED}${BOLD}✗ DIFFERENCE${RESET} - Outputs or exit codes differ!"
            ((diff_count++))
        fi

        # Cleanup temp files
        rm -f "$bash_out" "$bash_err" "$ms_out" "$ms_err"
    done
}

# ============================================================================ #
#                                    MENU                                      #
# ============================================================================ #

show_help() {
    clear
    print_header
    echo -e "${CYAN}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}                           HELP & SHORTCUTS                               ${RESET}${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}${BOLD}Navigation:${RESET}                                                              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}1-37${RESET}     Run individual test category                                ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}m${RESET}        Return to main menu                                        ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}h${RESET}        Show this help                                             ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}                                                                          ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}${BOLD}Quick Actions:${RESET}                                                           ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}a${RESET}        Run ALL tests (800+ tests)                                 ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}q${RESET}        Quick test (essential features only - ~50 tests)          ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}b${RESET}        Basic tests only (tests 1-17)                             ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}n${RESET}        New/Advanced tests only (tests 18-37)                     ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}                                                                          ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}${BOLD}Interactive Mode:${RESET}                                                        ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}i${RESET}        Test your own commands (side-by-side comparison)          ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}                                                                          ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}${BOLD}Reports & Info:${RESET}                                                          ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}c${RESET}        Browse results by category                                 ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}r${RESET}        View last report                                           ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}s${RESET}        Show summary of current session                            ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}l${RESET}        List all test categories                                   ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}                                                                          ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}${BOLD}Exit:${RESET}                                                                    ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}   ${WHITE}x${RESET}        Exit benchmark                                             ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
    echo ""
    echo -ne "${DIM}Press Enter to continue...${RESET}"
    read
}

show_categories_list() {
    clear
    print_header
    echo -e "${CYAN}${BOLD}╔════════════════════════════════════════════════════════════════════════════════════╗${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}                          ALL TEST CATEGORIES                                     ${RESET}${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╠════════════════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${WHITE}${BOLD}#  │ Category Name                              │ Tests │ Level                  ${RESET}${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╠════════════════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}01${RESET} │ Startup Performance                        │  ${DIM}30${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}02${RESET} │ Echo - Hardcore                             │  ${DIM}34${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}03${RESET} │ Echo - Extreme                              │  ${DIM}13${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}04${RESET} │ Syntax Errors                               │  ${DIM}18${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}05${RESET} │ Pipes - Comprehensive                       │  ${DIM}20${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}06${RESET} │ Redirections - Hardcore                     │  ${DIM} 8${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}07${RESET} │ Environment Variables                       │  ${DIM}18${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}08${RESET} │ Quote Handling                              │  ${DIM}30${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}09${RESET} │ Edge Cases                                  │  ${DIM}14${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}10${RESET} │ Builtins - Comprehensive                    │  ${DIM}14${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}11${RESET} │ Stress & Load                               │  ${DIM} 3${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}12${RESET} │ Memory Usage                                │  ${DIM} 1${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}13${RESET} │ Real-World Scenarios                        │  ${DIM} 6${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}14${RESET} │ Exit Codes                                  │  ${DIM}15${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}15${RESET} │ Stdout/Stderr Separation                    │  ${DIM} 9${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}16${RESET} │ Signal Handling                             │  ${DIM} 3${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${CYAN}17${RESET} │ Wildcards & Special                         │  ${DIM}10${RESET}   │ ${GREEN}Basic${RESET}                  ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╠════════════════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}18${RESET} │ Heredoc - Comprehensive                     │  ${DIM} 5${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}19${RESET} │ Exit Codes - Ultra Strict                   │  ${DIM}10${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}20${RESET} │ Variable Expansion - Advanced               │  ${DIM}20${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}21${RESET} │ Quote Handling - Edge Cases                 │  ${DIM}26${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}22${RESET} │ Pipes - Extreme Multi-Pipe                  │  ${DIM}10${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}23${RESET} │ Redirections - Advanced                     │  ${DIM} 7${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}24${RESET} │ Pipes + Redirections - Combined             │  ${DIM} 7${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}25${RESET} │ Builtins - Edge Cases                       │  ${DIM}30${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}26${RESET} │ Command Not Found                           │  ${DIM} 6${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${YELLOW}27${RESET} │ Paths with Spaces                           │  ${DIM} 8${RESET}   │ ${YELLOW}Advanced${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╠════════════════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}28${RESET} │ Echo - Ultra Extended                       │  ${DIM}50${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}29${RESET} │ Pipes - Ultra Comprehensive                 │  ${DIM}50${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}30${RESET} │ Redirections - Ultra Complete               │  ${DIM}40${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}31${RESET} │ Variables - Ultra Extended                  │  ${DIM}60${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}32${RESET} │ Builtins - Ultra Comprehensive              │  ${DIM}70${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}33${RESET} │ Quotes - Ultra Extended                     │  ${DIM}50${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}34${RESET} │ Wildcards - Ultra Complete                  │  ${DIM}40${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}35${RESET} │ Error Handling - Comprehensive              │  ${DIM}30${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}36${RESET} │ Mixed Complex Commands                      │  ${DIM}40${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${RED}37${RESET} │ Stress Testing Extended                     │  ${DIM}20${RESET}   │ ${RED}Ultra   ${RESET}              ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╚════════════════════════════════════════════════════════════════════════════════════╝${RESET}"
    echo ""
    echo -ne "${DIM}Press Enter to continue...${RESET}"
    read
}

show_menu() {
    print_header
    echo -e "${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    echo -e "${BOLD}║${RESET}${WHITE}${BOLD}                         MAIN MENU                                        ${RESET}${BOLD}║${RESET}"
    echo -e "${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${BOLD}║${RESET}                                                                          ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}  ${GREEN}${BOLD}🚀 QUICK START${RESET}                                                          ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[a]${RESET} Run ALL tests (37 categories, 800+ tests)                      ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[q]${RESET} Quick Test (essential features, ~50 tests)                     ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[b]${RESET} Basic Tests only (tests 1-17)                                  ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[n]${RESET} Advanced Tests only (tests 18-37)                              ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}                                                                          ${BOLD}║${RESET}"
    echo -e "${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${BOLD}║${RESET}  ${YELLOW}${BOLD}📋 INDIVIDUAL TESTS${RESET}                                                      ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${DIM}Enter 1-37 to run a specific test category${RESET}                       ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[l]${RESET} List all 37 test categories                                    ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}                                                                          ${BOLD}║${RESET}"
    echo -e "${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${BOLD}║${RESET}  ${BLUE}${BOLD}🎮 INTERACTIVE MODE${RESET}                                                      ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[i]${RESET} Test your own commands (side-by-side comparison)              ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}                                                                          ${BOLD}║${RESET}"
    echo -e "${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${BOLD}║${RESET}  ${MAGENTA}${BOLD}📊 REPORTS & INFO${RESET}                                                        ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[c]${RESET} Browse results by category                                     ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[r]${RESET} View last report                                               ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[s]${RESET} Show current session summary                                   ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[h]${RESET} Help & keyboard shortcuts                                      ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}                                                                          ${BOLD}║${RESET}"
    echo -e "${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${BOLD}║${RESET}  ${RED}${BOLD}❌ EXIT${RESET}                                                                  ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}   ${CYAN}${BOLD}[x]${RESET} Exit benchmark                                                 ${BOLD}║${RESET}"
    echo -e "${BOLD}║${RESET}                                                                          ${BOLD}║${RESET}"
    echo -e "${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
    echo ""
    echo -e "${DIM}Tip: Press 'h' for help and keyboard shortcuts${RESET}"
    echo ""
    echo -ne "${BOLD}${CYAN}➤ Your choice: ${RESET}"
}

run_quick_test() {
    TESTS_PASSED=0
    TESTS_FAILED=0
    TESTS_TOTAL=0
    TEST_WARNINGS=0
    FAILED_TESTS=()
    FAILED_DETAILS=()
    QUIET_MODE=1
    TOTAL_TESTS_PLANNED=100

    clear
    print_banner
    echo -e "${CYAN}${BOLD}Starting QUICK TEST MODE...${RESET}"
    echo -e "${YELLOW}Testing essential features only (~100 tests)${RESET}\n"
    sleep 1

    # Essential tests
    test_echo_hardcore
    test_pipes_comprehensive
    test_redirections_hardcore
    test_builtins_comprehensive
    test_exit_codes

    QUIET_MODE=0
    echo ""
    clear
    print_banner
    show_summary
    show_failed_tests
}

run_basic_tests() {
    TESTS_PASSED=0
    TESTS_FAILED=0
    TESTS_TOTAL=0
    TEST_WARNINGS=0
    FAILED_TESTS=()
    FAILED_DETAILS=()
    QUIET_MODE=1
    TOTAL_TESTS_PLANNED=250

    clear
    print_banner
    echo -e "${CYAN}${BOLD}Starting BASIC TESTS...${RESET}"
    echo -e "${YELLOW}Running tests 1-17 (~250 tests)${RESET}\n"
    sleep 1

    test_startup_performance
    test_echo_hardcore
    test_echo_extreme
    test_syntax_errors
    test_pipes_comprehensive
    test_redirections_hardcore
    test_environment_variables_extensive
    test_quotes_comprehensive
    test_edge_cases_extreme
    test_builtins_comprehensive
    test_stress_load
    test_memory_usage
    test_complex_scenarios
    test_exit_codes
    test_stderr_stdout_separation
    test_signal_handling
    test_wildcards_and_special

    QUIET_MODE=0
    echo ""
    clear
    print_banner
    show_summary
    show_failed_tests
}

run_advanced_tests() {
    TESTS_PASSED=0
    TESTS_FAILED=0
    TESTS_TOTAL=0
    TEST_WARNINGS=0
    FAILED_TESTS=()
    FAILED_DETAILS=()
    QUIET_MODE=1
    TOTAL_TESTS_PLANNED=550

    clear
    print_banner
    echo -e "${CYAN}${BOLD}Starting ADVANCED TESTS...${RESET}"
    echo -e "${YELLOW}Running tests 18-37 (Advanced + Ultra - ~550 tests)${RESET}\n"
    sleep 1

    test_heredoc_comprehensive
    test_exit_codes_ultra_strict
    test_variable_expansion_advanced
    test_quotes_edge_cases
    test_pipes_extreme
    test_redirections_advanced
    test_pipes_and_redirections_combined
    test_builtins_edge_cases
    test_command_not_found
    test_paths_with_spaces
    test_echo_ultra_extended
    test_pipes_ultra
    test_redirections_ultra
    test_variables_ultra
    test_builtins_ultra
    test_quotes_ultra
    test_wildcards_ultra
    test_error_handling
    test_mixed_complex
    test_stress_extended

    QUIET_MODE=0
    echo ""
    clear
    print_banner
    show_summary
    show_failed_tests
}

run_test() {
    case $1 in
        1) test_startup_performance ;;
        2) test_echo_hardcore ;;
        3) test_echo_extreme ;;
        4) test_syntax_errors ;;
        5) test_pipes_comprehensive ;;
        6) test_redirections_hardcore ;;
        7) test_environment_variables_extensive ;;
        8) test_quotes_comprehensive ;;
        9) test_edge_cases_extreme ;;
        10) test_builtins_comprehensive ;;
        11) test_stress_load ;;
        12) test_memory_usage ;;
        13) test_complex_scenarios ;;
        14) test_exit_codes ;;
        15) test_stderr_stdout_separation ;;
        16) test_signal_handling ;;
        17) test_wildcards_and_special ;;
        18) test_heredoc_comprehensive ;;
        19) test_exit_codes_ultra_strict ;;
        20) test_variable_expansion_advanced ;;
        21) test_quotes_edge_cases ;;
        22) test_pipes_extreme ;;
        23) test_redirections_advanced ;;
        24) test_pipes_and_redirections_combined ;;
        25) test_builtins_edge_cases ;;
        26) test_command_not_found ;;
        27) test_paths_with_spaces ;;
        28) test_echo_ultra_extended ;;
        29) test_pipes_ultra ;;
        30) test_redirections_ultra ;;
        31) test_variables_ultra ;;
        32) test_builtins_ultra ;;
        33) test_quotes_ultra ;;
        34) test_wildcards_ultra ;;
        35) test_error_handling ;;
        36) test_mixed_complex ;;
        37) test_stress_extended ;;
        q)
            run_quick_test
            ;;
        b)
            run_basic_tests
            ;;
        n)
            run_advanced_tests
            ;;
        a)
            TESTS_PASSED=0
            TESTS_FAILED=0
            TESTS_TOTAL=0
            TEST_WARNINGS=0
            FAILED_TESTS=()
            FAILED_DETAILS=()
            QUIET_MODE=1

            clear
            print_banner
            echo -e "${CYAN}${BOLD}Starting ALL TESTS (37 categories, 800+ tests)...${RESET}"
            echo -e "${YELLOW}Running in quiet mode - showing progress bar only${RESET}\n"
            sleep 1

            test_startup_performance
            test_echo_hardcore
            test_echo_extreme
            test_syntax_errors
            test_pipes_comprehensive
            test_redirections_hardcore
            test_environment_variables_extensive
            test_quotes_comprehensive
            test_edge_cases_extreme
            test_builtins_comprehensive
            test_stress_load
            test_memory_usage
            test_complex_scenarios
            test_exit_codes
            test_stderr_stdout_separation
            test_signal_handling
            test_wildcards_and_special
            test_heredoc_comprehensive
            test_exit_codes_ultra_strict
            test_variable_expansion_advanced
            test_quotes_edge_cases
            test_pipes_extreme
            test_redirections_advanced
            test_pipes_and_redirections_combined
            test_builtins_edge_cases
            test_command_not_found
            test_paths_with_spaces
            test_echo_ultra_extended
            test_pipes_ultra
            test_redirections_ultra
            test_variables_ultra
            test_builtins_ultra
            test_quotes_ultra
            test_wildcards_ultra
            test_error_handling
            test_mixed_complex
            test_stress_extended

            # Disable quiet mode and show results
            QUIET_MODE=0
            echo ""
            clear
            print_banner
            show_summary

            echo ""
            echo -e "${CYAN}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
            echo -e "${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}                       NAVIGATION OPTIONS                                 ${RESET}${CYAN}${BOLD}║${RESET}"
            echo -e "${CYAN}${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
            echo -e "${CYAN}${BOLD}║${RESET}  ${CYAN}${BOLD}[c]${RESET} Browse results by category                                     ${CYAN}${BOLD}║${RESET}"
            echo -e "${CYAN}${BOLD}║${RESET}  ${CYAN}${BOLD}[f]${RESET} Show all failed tests                                          ${CYAN}${BOLD}║${RESET}"
            echo -e "${CYAN}${BOLD}║${RESET}  ${CYAN}${BOLD}[m]${RESET} Return to main menu                                            ${CYAN}${BOLD}║${RESET}"
            echo -e "${CYAN}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
            echo ""
            echo -ne "${BOLD}${CYAN}➤ Your choice: ${RESET}"
            read -r nav_choice

            case $nav_choice in
                c)
                    browse_results_by_category
                    ;;
                f)
                    clear
                    print_header
                    show_failed_tests
                    echo -ne "${DIM}Press Enter to continue...${RESET}"
                    read
                    ;;
                *)
                    # Return to menu
                    ;;
            esac
            ;;
        *) return ;;
    esac

    if [ "$1" != "a" ]; then
        echo ""
        echo -e "${GREEN}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
        echo -e "${GREEN}${BOLD}║                         ✓ TEST COMPLETED                                 ║${RESET}"
        echo -e "${GREEN}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
        echo -e "${CYAN}Report saved to: ${YELLOW}${REPORT_FILE}${RESET}\n"
    fi

    echo -ne "${DIM}Press Enter to continue...${RESET}"
    read
}

show_categories_summary() {
    echo ""
    echo -e "${CYAN}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}                    TEST CATEGORIES BREAKDOWN                             ${RESET}${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${DIM}Category                                         Status      Tests   Rate${RESET} ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"

    # This would be populated dynamically in a real implementation
    # For now, showing the structure

    echo -e "${CYAN}${BOLD}║${RESET} ${DIM}#01${RESET} Startup Performance                       ${GREEN}[✓]${RESET}      ${CYAN}30${RESET}     ${GREEN}100%${RESET} ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${DIM}#02${RESET} Echo - Hardcore                           ${GREEN}[✓]${RESET}      ${CYAN}34${RESET}     ${GREEN}100%${RESET} ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${DIM}#03${RESET} Echo - Extreme Cases                      ${GREEN}[✓]${RESET}      ${CYAN}13${RESET}     ${GREEN}100%${RESET} ${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET} ${DIM}...${RESET}                                                                      ${CYAN}${BOLD}║${RESET}"

    echo -e "${CYAN}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
    echo ""
}

show_failed_tests() {
    if [ ${#FAILED_TESTS[@]} -gt 0 ]; then
        print_section "FAILED TESTS DETAILS"

        echo -e "${RED}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
        echo -e "${RED}${BOLD}║${RESET}  ${WHITE}${BOLD}Found ${#FAILED_TESTS[@]} failed test(s) - Review required${RESET}                              ${RED}${BOLD}║${RESET}"
        echo -e "${RED}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}\n"

        for i in "${!FAILED_TESTS[@]}"; do
            echo -e "${RED}${BOLD}╭─ Test #$((i+1))${RESET}"
            echo -e "${RED}${BOLD}│${RESET} ${FAILED_TESTS[$i]}"
            echo -e "${RED}${BOLD}│${RESET} ${DIM}Details: ${FAILED_DETAILS[$i]}${RESET}"
            echo -e "${RED}${BOLD}╰─${RESET}"
            echo ""
        done
        echo "" >> "$REPORT_FILE"
        echo "╔══════════════════════════════════════════════════════════════════════════╗" >> "$REPORT_FILE"
        echo "║                        FAILED TESTS DETAILS                              ║" >> "$REPORT_FILE"
        echo "╚══════════════════════════════════════════════════════════════════════════╝" >> "$REPORT_FILE"
        echo "" >> "$REPORT_FILE"

        for i in "${!FAILED_TESTS[@]}"; do
            echo "$((i+1)). ${FAILED_TESTS[$i]}" >> "$REPORT_FILE"
            echo "   ${FAILED_DETAILS[$i]}" >> "$REPORT_FILE"
            echo "" >> "$REPORT_FILE"
        done
    else
        echo ""
        echo -e "${GREEN}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
        echo -e "${GREEN}${BOLD}║${RESET}  ${WHITE}${BOLD}✓ No Failed Tests - All tests passed successfully!${RESET}                   ${GREEN}${BOLD}║${RESET}"
        echo -e "${GREEN}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}\n"
    fi
}

show_summary() {
    print_section "FINAL SUMMARY"

    local pass_rate=0
    if [ $TESTS_TOTAL -gt 0 ]; then
        pass_rate=$((TESTS_PASSED * 100 / TESTS_TOTAL))
    fi

    local status_color=$GREEN
    local status_icon="✓"
    local status_text="EXCELLENT"
    local status_emoji="🎉"

    if [ $pass_rate -lt 100 ]; then
        status_color=$YELLOW
        status_icon="⚠"
        status_text="GOOD"
        status_emoji="👍"
    fi

    if [ $pass_rate -lt 80 ]; then
        status_color=$YELLOW
        status_icon="⚠"
        status_text="NEEDS WORK"
        status_emoji="⚠️"
    fi

    if [ $pass_rate -lt 60 ]; then
        status_color=$RED
        status_icon="✗"
        status_text="CRITICAL"
        status_emoji="❌"
    fi

    echo ""
    echo -e "${CYAN}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    echo -e "${CYAN}║${RESET}${BOLD}                        TEST EXECUTION SUMMARY                            ${RESET}${CYAN}║${RESET}"
    echo -e "${CYAN}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    echo -e "${CYAN}║${RESET}                                                                          ${CYAN}║${RESET}"
    printf "${CYAN}║${RESET}   ${BOLD}Total Tests:${RESET}      ${WHITE}${BOLD}%6d${RESET}                                              ${CYAN}║${RESET}\n" $TESTS_TOTAL
    printf "${CYAN}║${RESET}   ${GREEN}${BOLD}✓ Tests Passed:${RESET}   ${GREEN}${BOLD}%6d${RESET}  ${DIM}(${GREEN}%3d%%${RESET}${DIM})${RESET}                                   ${CYAN}║${RESET}\n" $TESTS_PASSED $pass_rate

    local fail_rate=0
    if [ $TESTS_TOTAL -gt 0 ]; then
        fail_rate=$((TESTS_FAILED * 100 / TESTS_TOTAL))
    fi
    printf "${CYAN}║${RESET}   ${RED}${BOLD}✗ Tests Failed:${RESET}   ${RED}${BOLD}%6d${RESET}  ${DIM}(${RED}%3d%%${RESET}${DIM})${RESET}                                   ${CYAN}║${RESET}\n" $TESTS_FAILED $fail_rate
    printf "${CYAN}║${RESET}   ${YELLOW}${BOLD}⚠ Warnings:${RESET}       ${YELLOW}${BOLD}%6d${RESET}                                              ${CYAN}║${RESET}\n" $TEST_WARNINGS
    echo -e "${CYAN}║${RESET}                                                                          ${CYAN}║${RESET}"
    echo -e "${CYAN}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"

    # Visual progress bar
    echo -e "${CYAN}║${RESET}   ${BOLD}Success Rate:${RESET}                                                        ${CYAN}║${RESET}"

    local bar_width=60
    local filled=$((bar_width * TESTS_PASSED / TESTS_TOTAL))
    local empty=$((bar_width - filled))

    local bar_color=$GREEN
    if [ $pass_rate -lt 100 ]; then bar_color=$YELLOW; fi
    if [ $pass_rate -lt 80 ]; then bar_color=$YELLOW; fi
    if [ $pass_rate -lt 60 ]; then bar_color=$RED; fi

    printf "${CYAN}║${RESET}   ["
    printf "${bar_color}%${filled}s${RESET}" | tr ' ' '█'
    printf "${DIM}%${empty}s${RESET}" | tr ' ' '░'
    printf "] ${WHITE}${BOLD}%3d%%${RESET}   ${CYAN}║${RESET}\n" $pass_rate

    echo -e "${CYAN}║${RESET}                                                                          ${CYAN}║${RESET}"
    echo -e "${CYAN}╠══════════════════════════════════════════════════════════════════════════╣${RESET}"
    printf "${CYAN}║${RESET}   ${BOLD}Overall Status:${RESET}     ${status_color}${BOLD}%-15s${RESET}  ${status_emoji}                            ${CYAN}║${RESET}\n" "$status_icon $status_text"
    echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"

    # Additional visual stats
    draw_success_rate_bar $TESTS_PASSED $TESTS_TOTAL

    echo "" >> "$REPORT_FILE"
    echo "╔══════════════════════════════════════════════════════════════════════════╗" >> "$REPORT_FILE"
    echo "║                           SUMMARY                                        ║" >> "$REPORT_FILE"
    echo "╚══════════════════════════════════════════════════════════════════════════╝" >> "$REPORT_FILE"
    echo "" >> "$REPORT_FILE"
    echo "Total tests:  $TESTS_TOTAL" >> "$REPORT_FILE"
    echo "Passed:       $TESTS_PASSED" >> "$REPORT_FILE"
    echo "Failed:       $TESTS_FAILED" >> "$REPORT_FILE"
    echo "Warnings:     $TEST_WARNINGS" >> "$REPORT_FILE"
    echo "Pass rate:    ${pass_rate}%" >> "$REPORT_FILE"
    echo "Status:       $status_text" >> "$REPORT_FILE"

    if [ $TESTS_FAILED -eq 0 ]; then
        echo ""
        echo -e "${GREEN}${BOLD}"
        cat << 'EOF'
╔══════════════════════════════════════════════════════════════════════════╗
║                                                                          ║
║          ███████╗██╗   ██╗ ██████╗ ██████╗███████╗███████╗███████╗      ║
║          ██╔════╝██║   ██║██╔════╝██╔════╝██╔════╝██╔════╝██╔════╝      ║
║          ███████╗██║   ██║██║     ██║     █████╗  ███████╗███████╗      ║
║          ╚════██║██║   ██║██║     ██║     ██╔══╝  ╚════██║╚════██║      ║
║          ███████║╚██████╔╝╚██████╗╚██████╗███████╗███████║███████║      ║
║          ╚══════╝ ╚═════╝  ╚═════╝ ╚═════╝╚══════╝╚══════╝╚══════╝      ║
║                                                                          ║
║                        🎉 ALL TESTS PASSED! 🎉                           ║
║                                                                          ║
║              Your minishell is performing EXCELLENTLY!                   ║
║                      Ready for production! 🚀                            ║
║                                                                          ║
╚══════════════════════════════════════════════════════════════════════════╝
EOF
        echo -e "${RESET}"

        echo "" >> "$REPORT_FILE"
        echo "🎉 ALL TESTS PASSED!" >> "$REPORT_FILE"
    elif [ $pass_rate -ge 80 ]; then
        echo ""
        echo -e "${YELLOW}${BOLD}"
        cat << 'EOF'
╔══════════════════════════════════════════════════════════════════════════╗
║                                                                          ║
║                         ⚠️  ALMOST THERE! ⚠️                              ║
║                                                                          ║
║                      SOME TESTS NEED ATTENTION                           ║
║                                                                          ║
║         Your minishell is looking good, but needs some fixes!            ║
║              Check the detailed report below. 👇                         ║
║                                                                          ║
╚══════════════════════════════════════════════════════════════════════════╝
EOF
        echo -e "${RESET}"

        echo "" >> "$REPORT_FILE"
        echo "⚠ Some tests failed - check details above" >> "$REPORT_FILE"
    else
        echo ""
        echo -e "${RED}${BOLD}"
        cat << 'EOF'
╔══════════════════════════════════════════════════════════════════════════╗
║                                                                          ║
║          ██████╗██████╗ ██╗████████╗██╗ ██████╗ █████╗ ██╗              ║
║         ██╔════╝██╔══██╗██║╚══██╔══╝██║██╔════╝██╔══██╗██║              ║
║         ██║     ██████╔╝██║   ██║   ██║██║     ███████║██║              ║
║         ██║     ██╔══██╗██║   ██║   ██║██║     ██╔══██║██║              ║
║         ╚██████╗██║  ██║██║   ██║   ██║╚██████╗██║  ██║███████╗         ║
║          ╚═════╝╚═╝  ╚═╝╚═╝   ╚═╝   ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝         ║
║                                                                          ║
║                   ❌ CRITICAL ISSUES DETECTED ❌                          ║
║                                                                          ║
║          Multiple tests failed. Immediate attention required!            ║
║               Review the detailed report below. 📋                       ║
║                                                                          ║
╚══════════════════════════════════════════════════════════════════════════╝
EOF
        echo -e "${RESET}"

        echo "" >> "$REPORT_FILE"
        echo "✗ Critical issues detected" >> "$REPORT_FILE"
    fi
}

view_report() {
    if [ -f "$REPORT_FILE" ]; then
        clear
        print_header
        print_section "Latest Report"
        cat "$REPORT_FILE" | head -150
        echo ""
        echo -e "${CYAN}Report location: ${YELLOW}${REPORT_FILE}${RESET}"
        echo -e "${DIM}(Showing first 150 lines - full report in file)${RESET}\n"
    else
        print_fail "No report found. Run a test first."
    fi
    echo -ne "${DIM}Press Enter to continue...${RESET}"
    read
}
