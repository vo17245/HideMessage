#pragma once
#include<iostream>
class BmpHeader {
public:
	short bfType;
	int bfSize;
	short bfReserved1;
	short bfReserved2;
	int bfOffBits;
	void print();//²âÊÔ´úÂë
};

