#!/bin/bash

rm tempTest

./gen $1  > tempTest


echo `/usr/bin/time -p ./a4 < tempTest`
