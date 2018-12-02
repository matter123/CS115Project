#include <iostream>
#include "test_driver.h"

template <class Generator>
void runTests(Generator g) {
	TestDriver::testAlgorithms(0x0, 20, g);  // N=2^0
	TestDriver::testAlgorithms(0x1, 20, g);  // N=2^1
	TestDriver::testAlgorithms(0x2, 20, g);  // N=2^2
	TestDriver::testAlgorithms(0x3, 20, g);  // N=2^3
	TestDriver::testAlgorithms(0x4, 20, g);  // N=2^4
	TestDriver::testAlgorithms(0x5, 20, g);  // N=2^5
	TestDriver::testAlgorithms(0x6, 20, g);  // N=2^6
	TestDriver::testAlgorithms(0x7, 20, g);  // N=2^7
	TestDriver::testAlgorithms(0x8, 20, g);  // N=2^8
	TestDriver::testAlgorithms(0x9, 20, g);  // N=2^9
	TestDriver::testAlgorithms(0xA, 20, g);  // N=2^10
	TestDriver::testAlgorithms(0xB, 20, g);  // N=2^11
	TestDriver::testAlgorithms(0xC, 20, g);  // N=2^12
	TestDriver::testAlgorithms(0xD, 20, g);  // N=2^13
	TestDriver::testAlgorithms(0xE, 20, g);  // N=2^14
	TestDriver::testAlgorithms(0xF, 20, g);  // N=2^15
	TestDriver::testAlgorithms(0x10, 20, g); // N=2^16
	TestDriver::testAlgorithms(0x11, 20, g); // N=2^17
	TestDriver::testAlgorithms(0x12, 20, g); // N=2^18
	TestDriver::testAlgorithms(0x13, 20, g); // N=2^19
	TestDriver::testAlgorithms(0x14, 20, g); // N=2^20
	TestDriver::testAlgorithms(0x15, 20, g); // N=2^21
	TestDriver::testAlgorithms(0x16, 20, g); // N=2^22
	TestDriver::testAlgorithms(0x17, 20, g); // N=2^23
	TestDriver::testAlgorithms(0x18, 20, g); // N=2^24
}

int main(int argc, char const *argv[]) {
	TestDriver::sortAlgorithms();
	std::cout << "unsorted vector" << std::endl;
	runTests(TestDriver::randomNumber);
	std::cout << "partially sorted vector" << std::endl;
	runTests(TestDriver::partiallySorted);
	std::cout << "sorted vector" << std::endl;
	runTests(TestDriver::sorted);
	return 0;
}
