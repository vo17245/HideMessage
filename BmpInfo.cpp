#include "BmpInfo.h"

void BmpInfo::print()
{
	std::cout << "biSize: " << biSize << std::endl;
	std::cout << "biWidth: " << biWidth << std::endl;
	std::cout << "biHeight: " << biHeight << std::endl;
	std::cout << "biPlanes: " << biPlanes << std::endl;
	std::cout << "biBitcount: " << biBitCount << std::endl;
	std::cout << "biCompression: " << biCompression << std::endl;
	std::cout << "biSizeImage: " << biSizeImage << std::endl;
	std::cout <<"biXPelsPerMeter: " << biXPelsPerMeter << std::endl;
	std::cout << "biYPelsPerMeter: " << biYPelsPerMeter << std::endl;
	std::cout << "biClrUsed: "<<biClrUsed << std::endl;
	std::cout << "biClrImportant: "<<biClrImportant << std::endl;
}
