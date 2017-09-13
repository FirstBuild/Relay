#!/bin/bash
#xcrun llvm-cov gcov -f -b ./objs/Relay.gcda
exec xcrun llvm-cov gcov "$@"

