CXXFLAGS?=-std=c++17 -g -O2 -fwrapv
ALGORITHMS=$(patsubst %.cpp,%.o,$(wildcard algorithms/*.cpp))
in_set: main.o in_set.o test_driver.o $(ALGORITHMS)
	$(CXX) $(LDFLAGS) -o $@ $^
clean:
	@-rm in_set
	@-rm *.o
	@-rm algorithms/*.o
