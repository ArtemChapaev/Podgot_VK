#!/usr/bin/env bash

PROG_PATH=${1}  # ./tests.out
ROOT=$(dirname $(realpath $0))

TST_F_NAME="test.dat"
U_TST_NAME="unit_test.dat"


rm -f $TST_F_NAME $U_TST_NAME
touch $TST_F_NAME $U_TST_NAME

eval "${PROG_PATH}"

for file in $TST_F_NAME $U_TST_NAME; do
	diff -uN $file $ROOT/${file}.gold
  if [[ "$?" != "0" ]]; then
    echo "Files mismatches"
  	exit 1
  fi
done

echo "***** TEST SUCCEED *****"
