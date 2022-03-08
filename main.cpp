#include"Crypt.h"
#include<iostream>
#include"BMP24.h"
#include<stdio.h>
#include<string>
using namespace std;
#define MAX_MESSAGE_SIZE 0xffff
bool isSame(const char* a,const char* b,int p,int len) {
	for (int i = p;i <= p + len - 1;++i) {
		if (a[i] !=b[i]) {
			return false;
		}
	}
	return true;
}
int loadFile(const char* path, char* buf) {
	FILE* fp;
	fp = fopen(path, "rb");
	if (fp == nullptr) {
		return -1;
	}
	fseek(fp, 0, SEEK_END);
	int bytes = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fread(buf, 1, bytes, fp);
	fclose(fp);
	return bytes;
}
int saveFile(const char* path, char* data, int bytes) {
	FILE* fp;
	fp = fopen(path, "wb");
	if (fp == nullptr) {
		return -1;
	}
	fwrite(data, 1, bytes, fp);
	fclose(fp);
}
class Buffer {
public:
	char* ptr;
	unsigned size;
	Buffer():ptr(nullptr),size(0){}
	Buffer(char* p,unsigned s):ptr(p),size(s) {}
	Buffer(int bytes) {
		ptr = new char[bytes];
		size = bytes;
	}
	~Buffer() {
		if (ptr != nullptr) {
			delete[] ptr;
		}
	}
	operator char* () { return ptr;}
};
int main(int argc,char** argv) {
	Buffer buf(MAX_MESSAGE_SIZE);
	if (argc ==1) {
		cout << "Invaild Input" << endl;
		return 0;
	}
	if (isSame(argv[1], "help", 0, 4)) {
		cout << "insert [image path] [text path] [image path]" << endl;
		cout << "extract [image path] [text path]" << endl;
		cout << "extract -p [image path]" << endl;
		cout << "encrypt [file path] [password]" << endl;
		cout << "decrypt [file path] [password]" << endl;
	}
	else if (isSame(argv[1], "insert", 0, 6)) {
		if (argc <5) {
			cout << "Invaild Input" << endl;
			return 0;
		}
		int ret = loadFile(argv[3],buf);
		if (ret < 0) {
			cout << "load text failed: " << ret << endl;
			return -1;
		}
		int msg_bytes = ret;
		BMP24 img;
		ret=img.load(argv[2]);
		if (ret < 0) {
			cout << "load image failed: " << ret << endl;
			return -1;
		}
		ret = img.insertMsg(buf, msg_bytes);
		if (ret < 0) {
			cout << "insert message failed: " << ret << endl;
			return -1;
		}
		ret = img.save(argv[4]);
		if (ret < 0) {
			cout << "save image failed: " << ret << endl;
			return -1;
		}
	}
	else if (isSame(argv[1], "extract", 0, 7)) {
		if (argc < 4) {
			cout << "Invaild Input" << endl;
			return 0;
		}
		if (isSame(argv[2], "-p", 0, 2)) {
			BMP24 img;
			int ret = img.load(argv[3]);
			if (ret < 0) {
				cout << "load image failed: " << ret << endl;
				return -1;
			}
			ret = img.extractMsg(buf.ptr, buf.size);
			if (ret < 0) {
				cout << "extract message failed: " << ret << endl;
				return -1;
			}
			int msg_bytes = ret;
			for (int i = 0;i < msg_bytes;i++) {
				printf("%c", buf.ptr[i]);
			}
			printf("\r\n");
		}else {
			BMP24 img;
			int ret = img.load(argv[2]);
			if (ret < 0) {
				cout << "load image failed: " << ret << endl;
				return -1;
			}
			ret = img.extractMsg(buf.ptr, buf.size);
			if (ret < 0) {
				cout << "extract failed: " << ret << endl;
				return -1;
			}
			int msg_bytes = ret;
			ret = saveFile(argv[3], buf, msg_bytes);
			if (ret < 0) {
				cout << "save file failed: " << ret << endl;
				return -1;
			}
		}
	}else if (isSame(argv[1], "encrypt", 0, 7)) {
		int ret = loadFile(argv[2], buf);
		if (ret < 0) {
			cout << "load file failed: " << ret << endl;
			return -1;
		}
		char* begin = argv[3];
		char* end = begin;
		while (*end != 0)++end;
		int psw_bytes = begin - end;
		Buffer output(ret);
		Crypt::Get().Encrypt(buf, ret, argv[3], psw_bytes, output);
		ret = saveFile(argv[2], output, output.size);
		if (ret < 0) {
			cout << "save file failed: " << ret << endl;
			return -1;
		}
	}
	else if (isSame(argv[1], "decrypt", 0, 7)) {
		int ret = loadFile(argv[2], buf);
		if (ret < 0) {
			cout << "load file failed: " << ret << endl;
			return -1;
		}
		char* begin = argv[3];
		char* end = begin;
		while (*end != 0)++end;
		int psw_bytes = begin - end;
		Buffer output(ret);
		Crypt::Get().Decrypt(buf, ret, argv[3], psw_bytes, output);
		ret = saveFile(argv[2], output, output.size);
		if (ret < 0) {
			cout << "save file failed: " << ret << endl;
			return -1;
		}
	}
	return 0;
}