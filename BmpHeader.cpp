#include "BmpHeader.h"

void BmpHeader::print()
{
	std::cout << "bfType: " << bfType << std::endl;
	std::cout << "bfSize: " << bfSize << std::endl;
	std::cout << "bfReserved1: " << bfReserved1 << std::endl;
	std::cout << "bfReserved2: " << bfReserved2 << std::endl;
	std::cout << "bfOffBits: " << bfOffBits << std::endl;
}
