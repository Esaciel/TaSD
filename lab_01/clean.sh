#!/bin/bash

dir=$(dirname "$(readlink -f "$0")")
cd "$dir" || exit 3

rm -f ./*.exe ./*.o ./*.gcov ./*.gcda ./*.gcno
