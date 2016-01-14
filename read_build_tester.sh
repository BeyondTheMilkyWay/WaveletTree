#!/bin/bash

LANGUAGE=python

TEST_REPORT_DIR=testReport/$LANGUAGE
rm -rd $TEST_REPORT_DIR
mkdir -p $TEST_REPORT_DIR

# For each test case
for test_case in $(ls testCases/); do

  READ_OUT=$TEST_REPORT_DIR/$test_case.read.out
  BUILD_OUT=$TEST_REPORT_DIR/$test_case.build.out

  touch $READ_OUT
  touch $BUILD_OUT

  TOTAL_RUNS=10
  COUNTER=0
  while [  $COUNTER -lt $TOTAL_RUNS ]; do
    echo $test_case: $COUNTER

    # Call of program
    python python/src/TesterReadBuild.py  testCases/$test_case &&

    cat read.out >> $READ_OUT &&
    echo >> $READ_OUT &&
    cat build.out >> $BUILD_OUT &&
    echo >> $BUILD_OUT &&

    let COUNTER=COUNTER+1
  done

done
