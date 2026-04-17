#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
FINDF="$SCRIPT_DIR/../findf"

PASS=0
FAIL=0

if [ ! -x "$FINDF" ]; then
    echo "ERROR: binary not found or not executable at $FINDF"
    echo "Run 'make' first."
    exit 1
fi

TEST_DIR=$(mktemp -d)
trap 'rm -rf "$TEST_DIR"' EXIT

# Create test fixture
mkdir -p "$TEST_DIR/subdir"
touch "$TEST_DIR/alpha.txt"
touch "$TEST_DIR/beta.log"
touch "$TEST_DIR/subdir/gamma.txt"
touch "$TEST_DIR/subdir/delta.log"

check() {
    local desc="$1" expected="$2" actual="$3"
    if echo "$actual" | grep -qF "$expected"; then
        echo "PASS: $desc"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $desc"
        echo "  expected to find: $expected"
        echo "  actual output:    $actual"
        FAIL=$((FAIL + 1))
    fi
}

check_absent() {
    local desc="$1" absent="$2" actual="$3"
    if echo "$actual" | grep -qF "$absent"; then
        echo "FAIL: $desc (unexpected string present: $absent)"
        FAIL=$((FAIL + 1))
    else
        echo "PASS: $desc"
        PASS=$((PASS + 1))
    fi
}

check_empty() {
    local desc="$1" actual="$2"
    if [ -z "$actual" ]; then
        echo "PASS: $desc"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $desc (expected empty output, got: $actual)"
        FAIL=$((FAIL + 1))
    fi
}

check_exit() {
    local desc="$1" expected_code="$2" actual_code="$3"
    if [ "$actual_code" -eq "$expected_code" ]; then
        echo "PASS: $desc"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $desc (expected exit $expected_code, got $actual_code)"
        FAIL=$((FAIL + 1))
    fi
}

# --- Basic listing ---
OUT=$("$FINDF" "$TEST_DIR")
check "basic listing includes alpha.txt" "alpha.txt" "$OUT"
check "basic listing includes beta.log" "beta.log" "$OUT"

# --- Recursive traversal ---
check "recursive listing includes subdir/gamma.txt" "gamma.txt" "$OUT"
check "recursive listing includes subdir path" "subdir" "$OUT"

# --- -name option ---
OUT=$("$FINDF" "$TEST_DIR" -name alpha.txt)
check "-name finds alpha.txt" "alpha.txt" "$OUT"
check_absent "-name alpha.txt does not show beta.log" "beta.log" "$OUT"

OUT=$("$FINDF" "$TEST_DIR" -name gamma.txt)
check "-name finds gamma.txt in subdir" "gamma.txt" "$OUT"

OUT=$("$FINDF" "$TEST_DIR" -name nosuchfile_xyzzy.txt)
check_empty "-name with no match produces empty output" "$OUT"

# --- -mmin option ---
RECENT="$TEST_DIR/recent.txt"
touch "$RECENT"
OUT=$("$FINDF" "$TEST_DIR" -mmin -1)
check "-mmin -1 finds recently touched file" "recent.txt" "$OUT"

OLD="$TEST_DIR/old.txt"
touch -t "$(date -d '2 minutes ago' +%Y%m%d%H%M.%S)" "$OLD"
OUT=$("$FINDF" "$TEST_DIR" -mmin +1)
check "-mmin +1 finds file touched 2 minutes ago" "old.txt" "$OUT"

# --- -inum option ---
INODE_FILE="$TEST_DIR/inode_test.txt"
touch "$INODE_FILE"
INODE=$(stat -c '%i' "$INODE_FILE")
OUT=$("$FINDF" "$TEST_DIR" -inum "$INODE")
check "-inum finds file by inode" "inode_test.txt" "$OUT"

OUT=$("$FINDF" "$TEST_DIR" -inum 9999999999)
check_empty "-inum with wrong inode produces empty output" "$OUT"

# --- -delete option ---
DEL_FILE="$TEST_DIR/to_delete.txt"
touch "$DEL_FILE"
"$FINDF" "$TEST_DIR" -name to_delete.txt -delete > /dev/null 2>&1 || true
if [ ! -f "$DEL_FILE" ]; then
    echo "PASS: -delete removes matched file"
    PASS=$((PASS + 1))
else
    echo "FAIL: -delete did not remove the file"
    FAIL=$((FAIL + 1))
fi

# --- Exit codes ---
"$FINDF" "$TEST_DIR" -badopt foo > /dev/null 2>&1 || EXIT_BAD=$?
check_exit "bad option returns exit code 1" 1 "${EXIT_BAD:-0}"

"$FINDF" /nonexistent_dir_xyzzy_99 > /dev/null 2>&1 || EXIT_NODIR=$?
check_exit "nonexistent directory returns exit code 2" 2 "${EXIT_NODIR:-0}"

# --- Summary ---
echo ""
echo "Results: $PASS passed, $FAIL failed out of $((PASS + FAIL)) tests"
[ "$FAIL" -eq 0 ] && exit 0 || exit 1
