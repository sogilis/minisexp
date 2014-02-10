#!/bin/sh
(set -v -e -x
make
./minisexp <test.sx >test.ll
cat test.ll
llvm-as <test.ll >test.bc
lli test.bc
)
