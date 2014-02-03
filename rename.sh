#!/bin/bash
#
#Place this file in a directory with DICOM files
#Replace (if needed) ${csv_original}
#Processed DICOM files will be moved to a ${done_dir}
#CSV for renamed files will be written to ${csv_renamed}
#
#AWK required for lowering case of $surname
#

done_dir="done"
csv_original="out.csv"
csv_renamed="out_renamed.csv"

echo "" > ${csv_renamed}
mkdir ${done_dir}

while IFS=, read fname id date surname pet                            
do
	new_surname=$(echo $surname | awk '{print tolower($0)}')
	new_fname="${id}_${new_surname}_$fname"
	echo "$fname -> $new_fname"
	mv "$fname" "${done_dir}/${new_fname}"
	echo "${id},${surname},${pet},${date},${new_fname}" >> $csv_renamed
done < $csv_original

