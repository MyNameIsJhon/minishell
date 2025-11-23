#!/bin/bash

# ============================================================================ #
#                  MINISHELL ULTRA-STRICT PERFORMANCE TESTER v3.0              #
#                              MODULAR VERSION                                 #
# ============================================================================ #

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
MODULES_DIR="$SCRIPT_DIR/benchmark_modules"

# Source all required modules
source "$MODULES_DIR/benchmark_config.sh"
source "$MODULES_DIR/benchmark_ui.sh"
source "$MODULES_DIR/benchmark_utils.sh"
source "$MODULES_DIR/benchmark_tests_basic.sh"
source "$MODULES_DIR/benchmark_tests_advanced.sh"
source "$MODULES_DIR/benchmark_tests_ultra.sh"
source "$MODULES_DIR/benchmark_menu.sh"

# Set up cleanup trap
trap cleanup EXIT INT TERM

# ============================================================================ #
#                              MAIN FUNCTION                                   #
# ============================================================================ #

main() {
    check_minishell
    init_report

    while true; do
        clear
        show_menu
        read -r choice

        case $choice in
            1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|31|32|33|34|35|36|37|a|q|b|n)
                clear
                run_test "$choice"
                ;;
            h)
                show_help
                ;;
            l)
                show_categories_list
                ;;
            i)
                interactive_mode
                ;;
            c)
                browse_results_by_category
                ;;
            r)
                view_report
                ;;
            s)
                clear
                print_header
                show_summary
                show_failed_tests
                echo -ne "${DIM}Press Enter to continue...${RESET}"
                read
                ;;
            m)
                # Return to menu (do nothing, just loop)
                ;;
            x)
                clear
                echo ""
                echo -e "${GREEN}${BOLD}"
                cat << 'EOF'
╔══════════════════════════════════════════════════════════════════════════╗
║                                                                          ║
║                 _____ _                 _    __   __            _        ║
║                |_   _| |__   __ _ _ __ | | _\ \ / /__  _   _  | |       ║
║                  | | | '_ \ / _` | '_ \| |/ /\ V / _ \| | | | | |       ║
║                  | | | | | | (_| | | | |   <  | | (_) | |_| | |_|       ║
║                  |_| |_| |_|\__,_|_| |_|_|\_\ |_|\___/ \__,_| (_)       ║
║                                                                          ║
║              Thank you for using Minishell Benchmark v4.0!               ║
║                    Happy coding! 🚀                                      ║
║                                                                          ║
╚══════════════════════════════════════════════════════════════════════════╝
EOF
                echo -e "${RESET}\n"
                exit 0
                ;;
            *)
                # Invalid choice - show brief error
                echo -e "${RED}Invalid choice. Press 'h' for help.${RESET}"
                sleep 1
                ;;
        esac
    done
}

main
