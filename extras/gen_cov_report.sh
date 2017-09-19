#!/bin/bash
# Generate the HTML coverate report
lcov --directory . --base-directory . --gcov-tool ./coverage.sh --capture -o cov.info
genhtml cov.info -o output

