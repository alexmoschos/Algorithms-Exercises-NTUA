#!/bin/bash
for i in $(seq 1 23);
do
        time diff -w <(./a.out < input$i.txt) output$i.txt;
done
