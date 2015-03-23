INCLUDE = -I./ -I./ext/Fit -I./ext/Tick
CXXFLAG = -Wall -Wextra -std=c++14

build:
	clang++ ${CXXFLAG} ${INCLUDE} test.cpp -o test

clean:
	rm test
