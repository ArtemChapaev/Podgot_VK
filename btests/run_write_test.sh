#!/usr/bin/env bash

PROG_PATH=${1}  # ./full_test.out
ROOT=$(dirname $(realpath $0))

CHECK_MEM_ARG="--memcheck"

VALGRIND_LOG="valgrind.log"
NO_LOST_PATTERN="All heap blocks were freed -- no leaks are possible"
NO_ERROR_PATTERN="ERROR SUMMARY: 0 errors"

WRITE_TEST_F_NAME="write_test.dat"

function check_mem() {
	RECEIVED=$(echo "${1}" | eval "valgrind --tool=memcheck --leak-check=summary --log-file=${VALGRIND_LOG} ${PROG_PATH}")

	NO_LOST=$(grep "${NO_LOST_PATTERN}" ${VALGRIND_LOG})
	NO_ERROR=$(grep "${NO_ERROR_PATTERN}" ${VALGRIND_LOG})
	if [ -z "${NO_LOST}" ] || [ -z "${NO_ERROR}" ]; then
		echo -e "TEST ${test} FAILED\n"

		cat ${VALGRIND_LOG}
		echo -e "\n\nRUN: valgrind --tool=memcheck --leak-check=full ./test.out\n\n"

		exit 1
	fi
}

rm -f $WRITE_TEST_F_NAME
touch $WRITE_TEST_F_NAME

if [[ ${2} == ${CHECK_MEM_ARG} ]]; then
	check_mem "${IN}"
else
	eval "${PROG_PATH}"
fi

diff -uN $WRITE_TEST_F_NAME $ROOT/${WRITE_TEST_F_NAME}.gold
if [[ "$?" != "0" ]]; then
  echo "Files mismatches"
  	exit 1
fi

echo "***** TEST SUCCEED *****"
