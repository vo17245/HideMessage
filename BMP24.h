#pragma once
#include<iostream>
#include<string>
#include"BmpHeader.h"
#include"BmpInfo.h"
class BMP24
{
public:
	BmpHeader header;
	BmpInfo info;
	unsigned matBytes;
	unsigned char* mat;
	int load(const std::string& path);
	int save(const std::string& path);
	int insertMsg(const char* data, unsigned short bytes);
	int extractMsg(char* buf, unsigned bufSize);
	int msgBytes();
	BMP24();
	BMP24(const std::string& path);
	~BMP24();
private:
	int insert(const char* data, unsigned bytes, int begin);//begin：插入数据在mat中的起始位置
	int extract(char* buf, unsigned bufSize, int begin,int bytes);//begin: 开始提取的位置,bytes: 要提取的字节数
};

