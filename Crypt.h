#pragma once
class Crypt
{
public:
	static Crypt& Get() {
		static Crypt instance;
		return instance;
	}
	static void Encrypt(char* data, int data_bytes, char* psw, int psw_bytes, char* output) {
		return Get().IEncrypt(data, data_bytes, psw, psw_bytes, output);
	}
	static void Decrypt(char* data, int data_bytes, char* psw, int psw_bytes, char* output) {
		return Get().IDecrypt(data, data_bytes, psw, psw_bytes, output);
	}
private:
	Crypt(){};
	void IEncrypt(char* data, int data_bytes, char* psw, int psw_bytes, char* output);
	void IDecrypt(char* data, int data_bytes, char* psw, int psw_bytes, char* output);
};

