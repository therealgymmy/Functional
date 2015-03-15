build:
	clang++ -Wall -Wextra -std=c++1y -I./ test.cpp -o test

clean:
	rm test
