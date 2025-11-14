#!/bin/bash

# Test script for memory leaks in minishell

echo "Creating test input..."
cat << 'EOF' > /tmp/minishell_test_input
ls
pwd
echo hello
exit
EOF

echo "Running minishell with test input..."
cat /tmp/minishell_test_input | ./minishell &
PID=$!

echo "Waiting for minishell to process commands (PID: $PID)..."
sleep 2

echo ""
echo "=== Checking for memory leaks ==="
leaks $PID 2>&1 | head -30

# Cleanup
wait $PID 2>/dev/null || true
rm -f /tmp/minishell_test_input

echo ""
echo "Test complete"
