#! /bin/bash

echo -e "timestamp;measurement" >>short_measurements.csv

while IFS=";" read -r start end measurement
do
  echo -e "$start;$measurement" >> short_measurements.csv
done < <(tail -n +2 condensed_measurements.csv)