#include"Crypt.h"
#include<iostream>
#include"BMP24.h"
#include<stdio.h>
using namespace std;
bool isSame(const char* a,const char* b,int p,int len) {
	for (int i = p;i <= p + len - 1;++i) {
		if (a[i] !=b[i]) {
			return false;
		}
	}
	return true;
}
int main(int argc,char** argv) {
	if (argc < 3) {
		cout << "Invalid input" << endl;
		return 0;
	}
	if (isSame(argv[1], "i", 0, 1)) {
		FILE* fp;
		fp = fopen(argv[3], "rb");
		if (fp == nullptr) {
			cout << "file open failed" << endl;
			return 0;
		}
		fseek(fp, 0, SEEK_END);
		int bytes = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		if (bytes > 0xffff) {
			cout << "file too large" << endl;
			fclose(fp);
			return 0;
		}
		char* data = new char[bytes];
		fread(data, 1, bytes, fp);
		fclose(fp);
		BMP24 img;
		int ret;
		ret=img.load(argv[2]);
		if (ret == -1) {
			cout << "image open failed" << endl;
			delete[] data;
			return 0;
		}
		ret=img.insertMsg(data, bytes);
		if (ret < 0) {
			cout << "insert failed" << endl;
			cout << "error: " << ret << endl;
		}
		string str;
		int p = 0;
		char* arg2 = argv[2];
		while (arg2[p] != 0) {
			str.push_back(arg2[p]);
			++p;
		}
		str = str + ".HideMessage.bmp";
		ret = img.save(str.c_str());
		if (ret < 0) {
			cout << "save image failed" << endl;
			delete[] data;
			return 0;
		}
		delete[] data;
	}
	else if (isSame(argv[1], "e", 0, 1)) {
		FILE* fp;
		fp = fopen(argv[3], "wb");
		if (fp == nullptr) {
			cout << "file open failed" << endl;
			return 0;
		}
		int ret;
		BMP24 img;
		ret=img.load(argv[2]);
		if (ret == -1) {
			cout << "image open failed" << endl;
			fclose(fp);
			return 0;
		}
		int bufBytes = img.msgBytes();
		char* buf = new char[bufBytes];
		img.extractMsg(buf, bufBytes);
		fwrite(buf, 1, bufBytes, fp);
		fclose(fp);
		delete[] buf;
	}
	else {
		cout << "Invalid input" << endl;
		return 0;
	}
	return 0;
}