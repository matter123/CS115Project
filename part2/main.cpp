#include "test_driver.h"

int main(int argc, char const *argv[]) {
	TestDriver::sortAlgorithms();
	TestDriver::testAlgorithms(0x0, 20);  // N=2^0
	TestDriver::testAlgorithms(0x1, 20);  // N=2^1
	TestDriver::testAlgorithms(0x2, 20);  // N=2^2
	TestDriver::testAlgorithms(0x3, 20);  // N=2^3
	TestDriver::testAlgorithms(0x4, 20);  // N=2^4
	TestDriver::testAlgorithms(0x5, 20);  // N=2^5
	TestDriver::testAlgorithms(0x6, 20);  // N=2^6
	TestDriver::testAlgorithms(0x7, 20);  // N=2^7
	TestDriver::testAlgorithms(0x8, 20);  // N=2^8
	TestDriver::testAlgorithms(0x9, 20);  // N=2^9
	TestDriver::testAlgorithms(0xA, 20);  // N=2^10
	TestDriver::testAlgorithms(0xB, 20);  // N=2^11
	TestDriver::testAlgorithms(0xC, 20);  // N=2^12
	TestDriver::testAlgorithms(0xD, 20);  // N=2^13
	TestDriver::testAlgorithms(0xE, 20);  // N=2^14
	TestDriver::testAlgorithms(0xF, 20);  // N=2^15
	TestDriver::testAlgorithms(0x10, 20); // N=2^16
	return 0;
}
