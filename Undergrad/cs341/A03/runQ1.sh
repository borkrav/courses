#!/bin/bash

rm tempTest

./testGenerator $1  > tempTest


echo `/usr/bin/time -p ./a3 < tempTest`
echo `/usr/bin/time -p ./bruteForce < tempTest`
