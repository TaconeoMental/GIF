#!/bin/bash
file_name=$1
file_out=$2
#grep '^\s*#\s*include' $file_name > /tmp/include.c
grep '^\s*#\s*\(include\|pragma\)' $file_name > /tmp/include.c
grep -Pv '^\s*#\s*(include|pragma)\b' $file_name > /tmp/code.c
gcc -I. -w -E $file_name | grep -v ^# > /tmp/preprocessed.c
sed -n '/./p' /tmp/include.c > $file_out
sed -n '/./p' /tmp/preprocessed.c  >> $file_out
#bat $file_out
#rm $file_out
