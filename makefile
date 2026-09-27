output: main.o
	mkdir -p build
	g++ main.cpp -o build/out
main.o: main.cpp
	g++ main.cpp
test: output
	python test/runtests.py

clean:
	rm -rf build a.out
	