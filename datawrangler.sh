#! /bin/bash
previous=3302491484
min=1617631503388278
max=0

echo -e "start;end;measurement" >>condensed_measurements.csv

while IFS=";" read -r timestamp measurement
do
  if [ "$measurement" -ne "$previous" ]; then
    # append min max and timestamp to a new file
    echo -e "$min;$max;$previous" >> condensed_measurements.csv
    min=$timestamp
    max=$timestamp
    previous=$measurement
  else
    max=$timestamp
  fi
done < <(tail -n +2 measurements.csv)
echo -e "$min;$max;$previous" >> condensed_measurements.csv