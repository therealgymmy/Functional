INCLUDE = -I./ -I./ext/Fit -I./ext/Tick
CXXFLAG = -Wall -Wextra -std=c++1y

build:
	clang++ ${CXXFLAG} ${INCLUDE} test.cpp -o test

clean:
	rm test
