#!/bin/bash

# ============================================================================ #
#                           USER INTERFACE FUNCTIONS                           #
# ============================================================================ #

print_banner() {
    clear
    echo -e "${CYAN}${BOLD}"
    cat << 'EOF'
╔══════════════════════════════════════════════════════════════════════════╗
║                                                                          ║
║      ███╗   ███╗██╗███╗   ██╗██╗███╗   ██╗███████╗██╗  ██╗███████╗     ║
║      ████╗ ████║██║████╗  ██║██║████╗  ██║██╔════╝██║  ██║██╔════╝     ║
║      ██╔████╔██║██║██╔██╗ ██║██║██╔██╗ ██║███████╗███████║█████╗       ║
║      ██║╚██╔╝██║██║██║╚██╗██║██║██║╚██╗██║╚════██║██╔══██║██╔══╝       ║
║      ██║ ╚═╝ ██║██║██║ ╚████║██║██║ ╚████║███████║██║  ██║███████╗     ║
║      ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚══════╝     ║
║                                                                          ║
║                ULTRA-STRICT BENCHMARK v4.0 - 800+ Tests!                 ║
║             37 Test Categories | Every difference = FAILURE              ║
║                                                                          ║
╚══════════════════════════════════════════════════════════════════════════╝
EOF
    echo -e "${RESET}"
}

print_header() {
    echo -e "${CYAN}${BOLD}"
    echo "╔══════════════════════════════════════════════════════════════════════════╗"
    echo "║               MINISHELL ULTRA-STRICT BENCHMARK v4.0                      ║"
    echo "╚══════════════════════════════════════════════════════════════════════════╝"
    echo -e "${RESET}"
}

animate_loading() {
    local text="$1"
    local duration=${2:-2}

    echo -ne "${CYAN}${BOLD}$text${RESET} "

    for i in $(seq 1 $duration); do
        echo -ne "${YELLOW}▓${RESET}"
        sleep 0.15
    done

    echo -e " ${GREEN}✓${RESET}"
}

show_test_intro() {
    clear
    print_banner

    echo -e "${CYAN}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    echo -e "${CYAN}${BOLD}║${RESET}${WHITE}${BOLD}                  INITIALIZING BENCHMARK SUITE                           ${RESET}${CYAN}${BOLD}║${RESET}"
    echo -e "${CYAN}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}\n"

    animate_loading "Loading test configurations..." 3
    animate_loading "Preparing test environment..." 4
    animate_loading "Validating minishell binary..." 3
    animate_loading "Initializing test categories..." 4

    echo ""
    echo -e "${GREEN}${BOLD}✓ Ready to begin testing!${RESET}"
    echo -e "${CYAN}${BOLD}27 Test Categories${RESET} ${DIM}|${RESET} ${YELLOW}${BOLD}400+ Individual Tests${RESET} ${DIM}|${RESET} ${MAGENTA}${BOLD}Ultra-Strict Mode${RESET}\n"

    sleep 1
}

print_section() {
    local title="$1"
    local width=74
    local title_len=${#title}
    local padding=$(( (width - title_len - 2) / 2 ))

    # Extract test number from "TEST X: Description" format and initialize category
    if [[ "$title" =~ TEST[[:space:]]+([0-9]+):[[:space:]]*(.+) ]]; then
        local test_num="${BASH_REMATCH[1]}"
        local test_desc="${BASH_REMATCH[2]}"
        # Remove leading/trailing whitespace
        test_num=$(echo "$test_num" | tr -d '[:space:]')
        test_desc=$(echo "$test_desc" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
        print_category_header "$test_desc" "$test_num"
    fi

    # Only show section header in verbose mode
    if [ $QUIET_MODE -eq 1 ]; then
        return
    fi

    echo ""
    echo -e "${BLUE}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    printf "${BLUE}${BOLD}║${RESET}${WHITE}${BOLD}%*s%s%*s${RESET}${BLUE}${BOLD}║${RESET}\n" $padding "" "$title" $((width - title_len - padding)) ""
    echo -e "${BLUE}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
    echo ""
}

print_section_with_stats() {
    local title="$1"
    local current="$2"
    local total="$3"

    echo ""
    echo -e "${BLUE}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    printf "${BLUE}${BOLD}║${RESET} ${YELLOW}${BOLD}%s${RESET}  ${DIM}│${RESET}  ${CYAN}Category %2d/%2d${RESET}  ${DIM}│${RESET}  " "$title" "$current" "$total"

    local percentage=0
    if [ $TESTS_TOTAL -gt 0 ] && [ $TESTS_PASSED -gt 0 ]; then
        percentage=$((TESTS_PASSED * 100 / TESTS_TOTAL))
    fi

    printf "${GREEN}✓ %d${RESET} ${RED}✗ %d${RESET}  ${DIM}│${RESET}  ${MAGENTA}%d%%${RESET} " $TESTS_PASSED $TESTS_FAILED $percentage

    # Calculate remaining space
    local title_len=${#title}
    local stats_len=48  # Approximate length of stats
    local total_len=$((title_len + stats_len))
    local padding=$((72 - total_len))

    printf "%${padding}s${BLUE}${BOLD}║${RESET}\n" ""
    echo -e "${BLUE}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
    echo ""
}

print_test_header() {
    echo -e "${YELLOW}${BOLD}▸ $1${RESET}"
}

print_test_subheader() {
    echo -e "${DIM}  → $1${RESET}"
}

print_pass() {
    if [ $QUIET_MODE -eq 1 ]; then
        show_live_progress_bar
        return
    fi
    echo -e "${GREEN}  ✓${RESET} $1"
}

print_fail() {
    if [ $QUIET_MODE -eq 1 ]; then
        show_live_progress_bar
        return
    fi
    echo -e "${RED}  ✗${RESET} $1"
}

print_warn() {
    echo -e "${YELLOW}  ⚠${RESET} $1"
}

print_info() {
    echo -e "${CYAN}  ℹ${RESET} $1"
}

print_error_detail() {
    local test_name="$1"
    local expected="$2"
    local got="$3"

    echo -e "${RED}${BOLD}    ┌─ Error Details:${RESET}"
    echo -e "${RED}    │${RESET} ${DIM}Expected:${RESET} ${expected:0:60}"
    echo -e "${RED}    │${RESET} ${DIM}Got:     ${RESET} ${got:0:60}"
    echo -e "${RED}    └─${RESET}"
}

print_progress_bar() {
    local current=$1
    local total=$2
    local width=50
    local percentage=$((current * 100 / total))
    local filled=$((width * current / total))
    local empty=$((width - filled))

    # Color based on percentage
    local bar_color=$GREEN
    if [ $percentage -lt 100 ]; then
        bar_color=$YELLOW
    fi
    if [ $percentage -lt 80 ]; then
        bar_color=$YELLOW
    fi
    if [ $percentage -lt 60 ]; then
        bar_color=$RED
    fi

    printf "\r${CYAN}Progress: [${RESET}"
    printf "${bar_color}%${filled}s${RESET}" | tr ' ' '█'
    printf "${DIM}%${empty}s${RESET}" | tr ' ' '░'
    printf "${CYAN}] ${WHITE}${BOLD}%3d%%${RESET} ${DIM}(%d/%d)${RESET}" $percentage $current $total
}

print_category_header() {
    local category="$1"
    local test_num="$2"

    # Clean and validate test number
    test_num=$(echo "$test_num" | tr -d '[:space:]')

    # Initialize category tracking
    CURRENT_CATEGORY="$category"
    CURRENT_CATEGORY_NUM="$test_num"
    CATEGORY_NAMES["$test_num"]="$category"
    CATEGORY_PASSED["$test_num"]=0
    CATEGORY_FAILED["$test_num"]=0
    CATEGORY_TOTAL["$test_num"]=0
    CATEGORY_FAILED_TESTS["$test_num"]=""

    if [ $QUIET_MODE -eq 1 ]; then
        show_live_progress_bar
        return
    fi

    echo ""
    echo -e "${BLUE}${BOLD}╔══════════════════════════════════════════════════════════════════════════╗${RESET}"
    printf "${BLUE}${BOLD}║${RESET} ${YELLOW}${BOLD}TEST #%2d${RESET} ${CYAN}│${RESET} %-58s ${BLUE}${BOLD}║${RESET}\n" "$test_num" "$category"
    echo -e "${BLUE}${BOLD}╚══════════════════════════════════════════════════════════════════════════╝${RESET}"
    echo ""
}

print_category_footer() {
    local passed=$1
    local failed=$2
    local total=$3
    local duration=$4

    if [ $QUIET_MODE -eq 1 ]; then
        return
    fi

    local percentage=0
    if [ $total -gt 0 ]; then
        percentage=$((passed * 100 / total))
    fi

    echo ""
    echo -e "${DIM}${BOLD}────────────────────────────────────────────────────────────────────────────${RESET}"
    printf "${DIM}│${RESET} "

    if [ $failed -eq 0 ]; then
        printf "${GREEN}${BOLD}✓ ALL PASSED${RESET}"
    else
        printf "${YELLOW}${BOLD}⚠ %d FAILED${RESET}" $failed
    fi

    printf " ${DIM}│${RESET} "
    printf "${CYAN}%d/%d tests${RESET}" $passed $total
    printf " ${DIM}│${RESET} "
    printf "${MAGENTA}%d%%${RESET}" $percentage

    if [ -n "$duration" ]; then
        printf " ${DIM}│${RESET} "
        printf "${YELLOW}%.2fs${RESET}" $duration
    fi

    echo ""
    echo -e "${DIM}${BOLD}────────────────────────────────────────────────────────────────────────────${RESET}"
}

print_live_stats() {
    local current_test=$1
    local total_tests=$2

    echo -e "\n${CYAN}${BOLD}╭─────────────────── LIVE STATISTICS ────────────────────╮${RESET}"
    printf "${CYAN}${BOLD}│${RESET} ${GREEN}✓ Passed:${RESET} %-6d ${CYAN}${BOLD}│${RESET} ${RED}✗ Failed:${RESET} %-6d ${CYAN}${BOLD}│${RESET} ${YELLOW}⚠ Warnings:${RESET} %-4d ${CYAN}${BOLD}│${RESET}\n" $TESTS_PASSED $TESTS_FAILED $TEST_WARNINGS

    local percentage=0
    if [ $TESTS_TOTAL -gt 0 ]; then
        percentage=$((TESTS_PASSED * 100 / TESTS_TOTAL))
    fi

    printf "${CYAN}${BOLD}│${RESET} ${WHITE}Total:${RESET} %-8d ${CYAN}${BOLD}│${RESET} ${MAGENTA}Success Rate:${RESET} %-6d%% ${CYAN}${BOLD}│${RESET} ${DIM}Progress: %d/%d${RESET}  ${CYAN}${BOLD}│${RESET}\n" $TESTS_TOTAL $percentage $current_test $total_tests
    echo -e "${CYAN}${BOLD}╰────────────────────────────────────────────────────────╯${RESET}\n"
}

show_live_progress_bar() {
    if [ $QUIET_MODE -eq 0 ]; then
        return
    fi

    local percentage=0
    if [ $TOTAL_TESTS_PLANNED -gt 0 ]; then
        percentage=$((TESTS_TOTAL * 100 / TOTAL_TESTS_PLANNED))
    fi

    local bar_width=40
    local filled=$((bar_width * TESTS_TOTAL / TOTAL_TESTS_PLANNED))
    if [ $filled -gt $bar_width ]; then filled=$bar_width; fi
    local empty=$((bar_width - filled))

    local success_rate=0
    if [ $TESTS_TOTAL -gt 0 ]; then
        success_rate=$((TESTS_PASSED * 100 / TESTS_TOTAL))
    fi

    # Choose color based on success rate
    local bar_color=$GREEN
    if [ $success_rate -lt 100 ]; then bar_color=$YELLOW; fi
    if [ $success_rate -lt 80 ]; then bar_color=$RED; fi

    # Truncate category name to fit (increased from 30 to 42)
    local cat_display="${CURRENT_CATEGORY:0:42}"

    # Clear and redraw (simple version)
    printf "\r\033[K"
    printf "${CYAN}[${RESET}%-42s${CYAN}]${RESET} [" "$cat_display"
    printf "${bar_color}%${filled}s${RESET}" | tr ' ' '█'
    printf "${DIM}%${empty}s${RESET}" | tr ' ' '░'
    printf "] ${WHITE}%3d%%${RESET} ${CYAN}%4d${RESET}/${CYAN}%d${RESET} ${GREEN}✓%4d${RESET} ${RED}✗%4d${RESET} ${MAGENTA}%3d%%${RESET}" \
        $percentage $TESTS_TOTAL $TOTAL_TESTS_PLANNED $TESTS_PASSED $TESTS_FAILED $success_rate
}

print_test_result_enhanced() {
    local status=$1
    local test_name=$2
    local details=$3

    if [ "$status" = "pass" ]; then
        printf "  ${GREEN}●${RESET} ${GREEN}✓${RESET} %-60s ${GREEN}${BOLD}PASS${RESET}\n" "$test_name"
    elif [ "$status" = "fail" ]; then
        printf "  ${RED}●${RESET} ${RED}✗${RESET} %-60s ${RED}${BOLD}FAIL${RESET}\n" "$test_name"
        if [ -n "$details" ]; then
            echo -e "${DIM}    └─ $details${RESET}"
        fi
    elif [ "$status" = "warn" ]; then
        printf "  ${YELLOW}●${RESET} ${YELLOW}⚠${RESET} %-60s ${YELLOW}${BOLD}WARN${RESET}\n" "$test_name"
    elif [ "$status" = "skip" ]; then
        printf "  ${DIM}●${RESET} ${DIM}⊘${RESET} %-60s ${DIM}${BOLD}SKIP${RESET}\n" "$test_name"
    fi
}

draw_success_rate_bar() {
    local passed=$1
    local total=$2
    local width=60

    if [ $total -eq 0 ]; then
        return
    fi

    local percentage=$((passed * 100 / total))
    local filled=$((width * passed / total))
    local empty=$((width - filled))

    local color=$GREEN
    if [ $percentage -lt 100 ]; then
        color=$YELLOW
    fi
    if [ $percentage -lt 80 ]; then
        color=$YELLOW
    fi
    if [ $percentage -lt 60 ]; then
        color=$RED
    fi

    echo -e "\n${WHITE}${BOLD}Success Rate Visualization:${RESET}"
    printf "  ["
    printf "${color}%${filled}s${RESET}" | tr ' ' '█'
    printf "${DIM}%${empty}s${RESET}" | tr ' ' '░'
    printf "] ${WHITE}${BOLD}%d%%${RESET}\n" $percentage
}

print_test_summary_box() {
    local category="$1"
    local passed=$2
    local total=$3
    local status_icon="✓"
    local status_color=$GREEN

    if [ $passed -lt $total ]; then
        status_icon="⚠"
        status_color=$YELLOW
    fi

    if [ $((passed * 100 / total)) -lt 60 ]; then
        status_icon="✗"
        status_color=$RED
    fi

    printf "  ${status_color}${BOLD}[%s]${RESET} %-50s ${CYAN}%3d${RESET}/${CYAN}%3d${RESET}\n" "$status_icon" "$category" $passed $total
}

draw_table_header() {
    echo -e "${CYAN}╔════════════════════════════════════╦══════════════╦══════════════╦═══════════╗${RESET}"
    echo -e "${CYAN}║${RESET}${BOLD}              Test Name             ${RESET}${CYAN}║${RESET}${BOLD}  Minishell   ${RESET}${CYAN}║${RESET}${BOLD}     Bash     ${RESET}${CYAN}║${RESET}${BOLD}   Ratio   ${RESET}${CYAN}║${RESET}"
    echo -e "${CYAN}╠════════════════════════════════════╬══════════════╬══════════════╬═══════════╣${RESET}"
}

draw_table_row() {
    local name="$1"
    local ms_time="$2"
    local bash_time="$3"
    local ratio=""

    if [ "$bash_time" != "N/A" ] && [ "$bash_time" -gt 0 ]; then
        ratio=$(echo "scale=2; $ms_time * 100 / $bash_time" | bc)"%"
    else
        ratio="N/A"
    fi

    printf "${CYAN}║${RESET} %-34s ${CYAN}║${RESET} ${YELLOW}%10s ms${RESET} ${CYAN}║${RESET} ${GREEN}%10s ms${RESET} ${CYAN}║${RESET} ${MAGENTA}%9s${RESET} ${CYAN}║${RESET}\n" \
        "$name" "$ms_time" "$bash_time" "$ratio"
}

draw_table_footer() {
    echo -e "${CYAN}╚════════════════════════════════════╩══════════════╩══════════════╩═══════════╝${RESET}"
}
