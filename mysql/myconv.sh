#!/bin/bash

# Usage check
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <source.sql> <dest.sql>"
    exit 1
fi

# Arguments
SOURCE="$1"
DEST="$2"
SRC_COLLATION="utf8mb4_0900_ai_ci"
TGT_COLLATION="utf8mb4_general_ci"

# Check file existence
if [ ! -f "$SOURCE" ]; then
    echo "Error: File not found: $SOURCE"
    exit 1
fi

# Perform replacement using sed
sed "s/$SRC_COLLATION/$TGT_COLLATION/g" "$SOURCE" > "$DEST"

echo "Conversion completed successfully. Output saved to: $DEST"
