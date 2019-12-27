#!/bin/bash
count=`cat count.txt`
count=$((count + 1))
tot=$(ls src/*.cpp | wc -l)
echo ""
echo -e "\e[0;36m>============== $count/$tot ==============<\e[0m"
echo $count > count.txt
