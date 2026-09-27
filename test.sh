# hand written
# create test cases from tests.txt
python test/textio.py
cat ./test/input.txt | ./build/out > test/textout.txt
# run the python script that extracts the output only
python test/outputextract.py
diff ./test/correctout.txt ./test/onlyout.txt > ./test/result.txt
# the rest of this is handled in this python file
# I just did not want to handle proccess spawning and pipes in python
python test/testresults.py