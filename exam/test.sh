#!/bin/bash
for i in $(seq 1 40);
do
        diff -w <(./algo2 input$i.txt) output$i.txt;
done
