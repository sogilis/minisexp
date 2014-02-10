#!/bin/sh
(set -v -e -x
make
./minisexp <test.sx >test.ll
cat test.ll
llvm-as <test.ll >test.bc

llc test.bc -o test.S
clang test.S -o test

lli test.bc

)
