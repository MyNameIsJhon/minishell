#!/bin/bash

echo "=== Test d'expansion de variables ==="
echo ""

# Test 1: Variable simple
echo "Test 1: echo \$USER"
echo "echo \$USER" | ./minishell

# Test 2: Variable avec path
echo ""
echo "Test 2: echo \$HOME"
echo "echo \$HOME" | ./minishell

# Test 3: Exit status
echo ""
echo "Test 3: echo \$?"
echo "echo \$?" | ./minishell

# Test 4: Double quotes (devrait être expansé)
echo ""
echo "Test 4: echo \"\$USER\""
echo "echo \"\$USER\"" | ./minishell

# Test 5: Single quotes (NE devrait PAS être expansé)
echo ""
echo "Test 5: echo '\$USER'"
echo "echo '\$USER'" | ./minishell

# Test 6: Mélange
echo ""
echo "Test 6: echo Hello \$USER from \$HOME"
echo "echo Hello \$USER from \$HOME" | ./minishell

# Test 7: Variable inexistante
echo ""
echo "Test 7: echo \$NOTEXIST"
echo "echo \$NOTEXIST" | ./minishell

echo ""
echo "=== Tests terminés ==="
