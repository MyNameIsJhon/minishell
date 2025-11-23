#!/bin/bash

# ============================================================================ #
#                  BENCHMARK CONFIGURATION & GLOBAL VARIABLES                  #
# ============================================================================ #

# Colors
BOLD='\033[1m'
DIM='\033[2m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
RED='\033[0;31m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
WHITE='\033[1;37m'
BG_GREEN='\033[42m'
BG_RED='\033[41m'
BG_YELLOW='\033[43m'
RESET='\033[0m'

# Configuration
MINISHELL="./minishell"
REPORT_DIR="benchmark_reports"
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
REPORT_FILE="${REPORT_DIR}/benchmark_${TIMESTAMP}.txt"
TMP_DIR="/tmp/minishell_bench_$$"

# Counters
TESTS_PASSED=0
TESTS_FAILED=0
TESTS_TOTAL=0
TEST_WARNINGS=0

# Error tracking
declare -a FAILED_TESTS
declare -a FAILED_DETAILS

# Performance tracking
declare -a PERF_TIMES_MS
declare -a PERF_TIMES_BASH

# Category-based result tracking
declare -A CATEGORY_NAMES
declare -A CATEGORY_PASSED
declare -A CATEGORY_FAILED
declare -A CATEGORY_TOTAL
declare -A CATEGORY_FAILED_TESTS
CURRENT_CATEGORY=""
CURRENT_CATEGORY_NUM=0

# Display mode
QUIET_MODE=0
TOTAL_TESTS_PLANNED=800
