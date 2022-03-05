#include "BMP24.h"
int BMP24::load(const std::string& path)
{
	FILE* fp;
	fp = fopen(path.c_str(), "rb");
	if (fp == nullptr) {
		return -1;
	}
	fread(&header, 1, 14, fp);
	fread(&info, 1, 40, fp);
	int colBytes = info.biWidth * 3;
	colBytes += 4 - colBytes % 4;
	matBytes = info.biHeight * colBytes;
	mat = new unsigned char[matBytes];
	fread(mat, 1, matBytes, fp);
	fclose(fp);
	return 1;
}

int BMP24::save(const std::string& path)
{
	FILE* fp;
	fp = fopen(path.c_str(), "wb");
	if (fp == nullptr) {
		return - 1;
	}
	fwrite(&header, 1, 14, fp);
	fwrite(&info, 1, 40, fp);
	fwrite(mat, 1, matBytes, fp);
	fclose(fp);
	return 1;
}

int BMP24::insertMsg(const char* data, unsigned short bytes)
{
	if ((matBytes - 16) < bytes * 8) {
		return -1;
	}
	int ret;
	ret=insert((char*)&bytes, 2, 0);
	if (ret < 0) {
		return ret;
	}
	ret=insert(data, bytes, 16);
	if (ret < 0) {
		return ret;
	}
	return 0;
}

int BMP24::extractMsg(char* buf, unsigned bufSize)
{
	int ret;
	unsigned short bytes=0;
	ret = extract((char*)&bytes, 2, 0, 2);
	if (ret < 0) {
		return ret;
	}
	ret = extract(buf, bufSize, 16, bytes);
	return 0;
}

int BMP24::msgBytes()
{
	unsigned short bytes;
	extract((char*)&bytes, 2, 0, 2);
	return bytes;
}

int BMP24::insert(const char* data,unsigned bytes,int begin)
{
	if ((matBytes-begin) < bytes*8) {
		return -1;
	}
	int matPos = begin;
	int dataPos = 0;
	char curChar;
	while (dataPos < bytes) {
		curChar = data[dataPos];
		for (int i = 0;i < 8;++i) {
			if ((curChar | (1 << i) )== curChar) {
				mat[matPos] = mat[matPos] | 0x1;
			}
			else {
				mat[matPos] = mat[matPos] & 0xfe;
			}
			++matPos;
		}
		++dataPos;
	}
	return 1;
}

int BMP24::extract(char* buf, unsigned bufSize,int begin,int bytes)
{
	if (matBytes < bytes * 8) {
		return -1;
	}
	if (bufSize < bytes) {
		return -2;
	}
	char curChar;
	int bufPos=0;
	int matPos = begin;
	for (int i = 0;i < bytes;++i) {
		for (int j = 0;j < 8;++j) {
			if ((mat[matPos] | 0x1) == mat[matPos]) {
				curChar = curChar | (1 << j);
			}
			else {
				curChar = curChar & (0xff - (1 << j));
			}
			++matPos;
		}
		buf[bufPos] = curChar;
		++bufPos;
	}
	return 1;
}

BMP24::BMP24()
{
	mat = nullptr;
}

BMP24::BMP24(const std::string& path)
{
	load(path.c_str());
}

BMP24::~BMP24()
{
	if (mat != nullptr) {
		delete[] mat;
	}
}
