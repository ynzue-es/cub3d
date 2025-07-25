#!/bin/bash

GOOD_DIR="maps/good"
BAD_DIR="maps/bad"
EXEC="./cub3d"

good_passed=0
good_failed=0
bad_passed=0
bad_failed=0

echo "=== Testing GOOD maps ==="
for file in "$GOOD_DIR"/*.cub; do
    echo -n "Testing $file... "
    output=$($EXEC "$file" 2>&1)
    if echo "$output" | grep -q "Error"; then
        echo "❌ FAILED (got Error)"
        ((good_failed++))
    else
        echo "✅ PASSED"
        ((good_passed++))
    fi
done

echo ""
echo "=== Testing BAD maps ==="
for file in "$BAD_DIR"/*.cub; do
    echo -n "Testing $file... "
    output=$($EXEC "$file" 2>&1)
    if echo "$output" | grep -q "Error"; then
        echo "✅ PASSED (Error found)"
        ((bad_passed++))
    else
        echo "❌ FAILED (no Error)"
        ((bad_failed++))
    fi
done

echo ""
echo "=== SUMMARY ==="
echo "GOOD maps passed: $good_passed"
echo "GOOD maps failed: $good_failed"
echo "BAD maps passed:  $bad_passed"
echo "BAD maps failed:  $bad_failed"

total_tests=$((good_passed + good_failed + bad_passed + bad_failed))
total_passed=$((good_passed + bad_passed))
total_failed=$((good_failed + bad_failed))

echo "Total tests: $total_tests"
echo "Total passed: $total_passed"
echo "Total failed: $total_failed"
