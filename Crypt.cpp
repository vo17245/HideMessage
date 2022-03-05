#include "Crypt.h"

void Crypt::IEncrypt(char* data, int data_bytes, char* psw, int psw_bytes, char* output)
{
	for (int i = 0;i < data_bytes;i++) {
		output[i] = data[i] ^ psw[i % psw_bytes];
	}
}

void Crypt::IDecrypt(char* data, int data_bytes, char* psw, int psw_bytes, char* output)
{
	for (int i = 0;i < data_bytes;i++) {
		output[i] = data[i] ^ psw[i % psw_bytes];
	}
}
