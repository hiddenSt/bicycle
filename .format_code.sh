#! /bin/bash

CLANG_FORMAT=clang-format-16

find core -name '*pp' -type f | xargs $CLANG_FORMAT -i
