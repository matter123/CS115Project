CXXFLAGS?=-std=c++17 -g -O2
ALGORITHMS=$(patsubst %.cpp,%.o,$(wildcard algorithms/*.cpp))
algorithm_test: main.o sort_algo.o test_driver.o $(ALGORITHMS)
	$(CXX) $(LDFLAGS) -o $@ $^
clean:
	@-rm algorithm_test
	@-rm *.o
	@-rm algorithms/*.o
