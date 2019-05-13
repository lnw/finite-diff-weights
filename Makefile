
#CXX=clang++
CXX=g++

FLAGS=-O2 -std=c++14 -Wunused -Wshadow # -g -Wall

finite-diff-weights: finite-diff-weights.cc auxiliary.hh Makefile
	$(CXX) $(FLAGS) $< -o $@

clean:

distclean: clean
	rm -f finite-diff-weights

