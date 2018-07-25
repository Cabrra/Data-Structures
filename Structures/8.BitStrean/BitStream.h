#pragma once

#include <vector>
#include <fstream>
using namespace std;

class BitOStream{
private:
	unsigned char buffer;
	int next;
	ofstream BoutFile;
public:
	BitOStream(const char* filePath, const char* headerChunk = NULL, int numberOfBytes = 0);
	~BitOStream();
	BitOStream& operator<<(vector<int> &bits);
	void close();
};

BitOStream::BitOStream(const char* filePath, const char* headerChunk, int numberOfBytes){
	buffer = 0;
	next = 7;
	BoutFile.open(filePath, ios_base::out | ios_base::binary);
	if (headerChunk != NULL){
		BoutFile.write((char*)headerChunk, numberOfBytes);
	}

}

BitOStream::~BitOStream(){
	BoutFile.close();
}

BitOStream& BitOStream::operator << (vector<int> &bits){
	for (unsigned int i = 0; i < bits.size(); i++){
		if (next == -1){
			next = 7;
			BoutFile.write((char*)&buffer, 1);
			buffer = 0;
		}
		if (bits[i])
			buffer |= (1 << next);
		next--;
	}
	return *this;
}

void BitOStream::close(){

	if (next < 7){
		BoutFile.write((char *)&buffer, 1);
	}
	BoutFile.close();
}


	class BitIStream {
	private:
		unsigned char buffer;
		int next;
		ifstream BinFile;
	public:
	BitIStream(const char* filePath, char* headerChunk = NULL, int numberOfBytes = 0);
	~BitIStream();
	BitIStream& operator>>(int &bit);
	bool eof();
	void close();
};

	BitIStream::BitIStream(const char* filePath, char* headerChunk, int numberOfBytes){
		BinFile.open(filePath, ios_base::in | ios_base::app | ios_base::binary);

		if (headerChunk != NULL){
			BinFile.read((char*)headerChunk, numberOfBytes);
		}
		buffer = 0;
		next = -1;
	}

	BitIStream::~BitIStream(){
		BinFile.close();
	}

	BitIStream& BitIStream::operator>>(int &bit){
		if (next == -1){
			next = 7;
			BinFile.read((char*)&buffer, 1);
		}
		
		if (buffer & (1 << next))
			bit = 1;
		else
			bit = 0;
		next--;


		return *this;
	}

	bool BitIStream::eof(){
		if (BinFile.eof() && (next == -1 || next == 6))
			return true;
		else
			return false;
	}

	void BitIStream::close(){
		BinFile.close();
	}