#! /bin/bash

CLANG_FORMAT=clang-format-16

find allocator core executors -name '*pp' -type f | xargs $CLANG_FORMAT -i
