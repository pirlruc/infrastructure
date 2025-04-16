#!/usr/bin/env bash
set -e

LLVM_MINGW_VERSION="20231128"
ARCHIVE_NAME="llvm-mingw-${LLVM_MINGW_VERSION}-ucrt-x86_64.zip"
DOWNLOAD_URL="https://github.com/mstorsjo/llvm-mingw/releases/download/${LLVM_MINGW_VERSION}/${ARCHIVE_NAME}"
INSTALL_DIR="$HOME/llvm-mingw"

echo "Downloading LLVM-MinGW..."
curl -L -o "$ARCHIVE_NAME" "$DOWNLOAD_URL"

mkdir -p "$INSTALL_DIR"

echo "Extracting LLVM-MinGW..."
unzip -q "$ARCHIVE_NAME" -d "$INSTALL_DIR"

export PATH="$INSTALL_DIR/llvm-mingw-${LLVM_MINGW_VERSION}-ucrt-x86_64/bin:$PATH"
echo "LLVM-MinGW setup complete."
