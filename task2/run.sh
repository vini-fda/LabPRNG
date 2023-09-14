#!/usr/bin/bash

seconds_a=$(date -d "2018-04-17 21:08:49 EDT" +%s)
seconds_b=$(date -d "2018-04-17 23:08:49 EDT" +%s)

echo "start: $seconds_a"
echo "end: $seconds_b"

./listing2 "$seconds_a" "$seconds_b"
