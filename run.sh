#!/bin/bash

# Read commands from a text file and execute them line by line

COMMANDS_FILE="commands.txt"

if [ -f "$COMMANDS_FILE" ]; then
    while IFS= read -r command; do
        eval "$command"
    done < "$COMMANDS_FILE"
else
    echo "Commands file not found!"
fi