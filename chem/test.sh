#!/bin/bash
for i in $(seq 1 20);
do
	time diff -w <(./a.out input$i.txt) output$i.txt;
	echo  "$i Done!"
done

