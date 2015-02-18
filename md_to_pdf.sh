#!/bin/bash
# Creates pdf from markdown

echo "Creating $1.pdf"
pandoc $1 -o $1.pdf
echo "$1.pdf created"

