#!/bin/sh

# Problem 1: accept a binary string that represents an unsigned value that is divisible by 3.
egrep '^(0|1(01*0)*1)*$' input1.txt > output1.txt

###################################################################################
# 2 decimal places
# Problem 2: red pick-up truck
egrep '.*\b(red(\s\w+?\b){,2} (pickup|pick-up|pick up) truck|(pickup|pick-up|pick up) truck(\s\w+?\b){,2} red)\b.*\$?([0-9]{1,3},([0-9]{3},)*[0-9]{3}|[0-9]+)(.[0-9][0-9])?' input2.txt > output2.txt

#################################################################################
# backreferences
# Problem 3:
egrep '^[0-9]{2}(.|-|/)[A-Z][a-z]{2}\1[0-9]{4}$' input3.txt > output3.txt

#################################################################################
# https://www.geeksforgeeks.org/sed-command-in-linux-unix-with-examples/
# Problem 4: find suitable course
touch output4.txt
cp ee_classes.html test.html
cat test.html | sed 's/<div class="course-info expandable"/\n/g' | egrep '.*DEN@Viterbi.*' | egrep '.*<span class="units">\((4|3).0 units\).*' | egrep '.*\"EE-5[0-9]{2}\".*' | egrep -o 'EE [0-9]{3}:</strong>( \b(\w|-)+\b)+ <span class="units">\((4|3).0 units\)' | sed 's/<\/strong>//g' | sed 's/<span.*>//g' | sort -t '(' -k 2 > output4.txt

################################################################################
# Problem 5: identify comments
egrep '[/][/*](.*)[*/]?' input5.txt > output5.txt

#################################################################################
# https://www.cyberciti.biz/faq/unix-howto-read-line-by-line-from-file/
# Problem 6: identify the identication number given by the Country Utopia
touch output6.txt
> output6.txt
while IFS= read -r line
do 
  [[ $line =~ ^[a-z]{0,3}[0-9]{2,8}[A-Z]{3,}$ ]] && echo "VALID" >> output6.txt || echo "INVALID" >> output6.txt
done < input6.txt




















