#!/bin/bash

# Read commands from a text file and execute them line by line

if [ -z "$1" ]; then
  echo "Please provide a filename as an argument."
  exit 1
fi

while IFS= read -r line; do
  echo "Executing: $line"
  eval "$line"
done < "$1"