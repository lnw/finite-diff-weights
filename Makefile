
#CXX=clang++
CXX=g++

FLAGS=-O0 -std=c++14 -Wunused -Wshadow -g #-Wall


# build/%.o: %.cc $(HEADERS) Makefile
#	$(CXX) $(FLAGS) -c $< -o $@

finite-diff-weights: finite-diff-weights.cc Makefile
	$(CXX) $(FLAGS) $< -o $@

clean:

distclean: clean
	rm -f finite-diff-weights

