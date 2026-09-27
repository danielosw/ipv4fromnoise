output: main.o
	mkdir -p build
	g++ main.cpp -o build/out
main.o: main.cpp
	g++ main.cpp
test: output
	python test/textio.py

clean:
	rm -rf build
	rm test/input.txt test/correctout.txt test/textout.txt test/onlyout.txt test/result.txt a.out 