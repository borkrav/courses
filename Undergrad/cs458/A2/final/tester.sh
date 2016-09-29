#!/bin/bash

cp cds.py ./input
cd ./input

echo censored-domain-input.log
./cds.py < censored-domain-input.log | diff - censored-domain-output.log 
echo censored-hosts-input.log
./cds.py < censored-hosts-input.log | diff - censored-hosts-output.log 
echo content-filter-URL-input-2.log
./cds.py < content-filter-URL-input-2.log | diff - content-filter-URL-output-2.log
echo content-filter-payload-input.log
./cds.py < content-filter-payload-input.log | diff - content-filter-payload-output.log
echo sample-input-1.log
./cds.py < sample-input-1.log | diff - sample-output-1.log
echo sample-input-2.log
./cds.py < sample-input-2.log | diff - sample-output-2.log
echo sample-input-3.log
./cds.py < sample-input-3.log | diff - sample-output-3.log
echo sample-input-4.log
./cds.py < sample-input-4.log | diff - sample-output-4.log
echo sample-input-5.log
./cds.py < sample-input-5.log | diff - sample-output-5.log

