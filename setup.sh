#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

echo "=== findf setup ==="

for tool in g++ make; do
    command -v "$tool" > /dev/null 2>&1 || {
        echo "Error: '$tool' not found."
        echo "Install with: sudo apt-get install build-essential"
        exit 1
    }
done

echo "Building findf..."
make

echo ""
echo "Build successful."
echo "  Run:     ./findf <directory>"
echo "  Test:    make test"
echo "  Install: bash setup.sh --install"

if [ "${1:-}" = "--install" ]; then
    if [ "$(id -u)" -eq 0 ]; then
        make install PREFIX=/usr/local
        echo "Installed to /usr/local/bin/findf"
    else
        mkdir -p "$HOME/.local/bin"
        make install PREFIX="$HOME/.local"
        echo "Installed to $HOME/.local/bin/findf"
        if ! echo "$PATH" | grep -q "$HOME/.local/bin"; then
            echo "Note: add to your shell profile:"
            echo "  export PATH=\"\$HOME/.local/bin:\$PATH\""
        fi
    fi
fi
