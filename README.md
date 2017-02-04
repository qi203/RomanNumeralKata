# RomanNumeralKata
There is a tester.sh file in the directory that can be run to see the results. (./tester.sh)
Or the commands can be executed in the following order: 1) make, 2) ./tests/check_calc
If for some reason autoreconf -install and ./configure commands are run, there is a need to add a Library to a Makefile
In that case cd tests and search for line with LIBS
Append to the end of line '-lsubunit'
