#pragma once

#include <fstream>
#include "BitStream.h"

struct cmp
{
	bool operator() (const HuffNode * a, const HuffNode * b)
	{
		return (a->freq > b->freq);
	}
};


/////////////////////////////////////////////////////////////////////////////
// Function : generateFrequencyTable
// Parameters : filePath - the path to the file to open
// Return : unsigned int* - a dynamically allocated frequency table 
// Notes : [256] contains the total count of characters in the file
/////////////////////////////////////////////////////////////////////////////
unsigned int* generateFrequencyTable(const char* filePath){
	unsigned int* FreqTable = new unsigned int[257];
	for (int i = 0; i < 257; i++)
		FreqTable[i] = 0;

	ifstream bin;
	bin.open(filePath, ios_base::binary);
	if (bin.is_open()){
		while (true){
			char a;
			bin.read((char*)&a, 1);
			if (bin.eof())
				break;
			FreqTable[a]++;
			FreqTable[256]++;

		}
		bin.close();
	}
	
	return FreqTable;
}

/////////////////////////////////////////////////////////////////////////////
// Function : generateLeafList
// Parameters : freqTable - the frequency table to be used to generate leaf 
//			nodes
// Return : vector<HuffNode*> - a vector containing the leaf nodes
/////////////////////////////////////////////////////////////////////////////
vector<HuffNode*> generateLeafList(unsigned int* freqTable){
	vector<HuffNode*> leafList;

	for (short i = 0; i < 256; i++){
		if (freqTable[i] != 0){
			HuffNode* leaf = new HuffNode;
			leaf->freq = freqTable[i];
			leaf->value = i;
			leaf->parent = NULL;
			leaf->left = NULL;
			leaf->right = NULL;

			leafList.push_back(leaf);

			//delete leaf;
		}
	}
	return leafList;
}

/////////////////////////////////////////////////////////////////////////////
// Function : generateHuffmanTree
// Parameters : leafList - the leaf nodes that will appear in our huffman 
//			tree
// Return : HuffNode* - the root of the generated tree
/////////////////////////////////////////////////////////////////////////////
HuffNode* generateHuffmanTree(vector<HuffNode*>& leafList){
	priority_queue <HuffNode *, vector<HuffNode *>, cmp> prior;

	for (unsigned int i = 0; i < leafList.size(); i++)
		prior.push(leafList[i]);

	while (prior.size() > 1){
		HuffNode*parent = new HuffNode;
	
		parent->left = NULL;
		parent->right = NULL;
		parent->parent = NULL;

		HuffNode* node1;
		HuffNode *node2;
		node1 = prior.top();
		prior.pop();
		node2 = prior.top();
		prior.pop();

		parent->left = node1;
		parent->right = node2;
		parent->value = -1;
		parent->freq = node1->freq + node2->freq;

		node1->parent = parent;
		node2->parent = parent;

		prior.push(parent);
	}

	return prior.top();
}

/////////////////////////////////////////////////////////////////////////////
// Function : generateEncodingTable
// Parameters : leafList - a vector containing all the leaves in the tree
// Return : vector<int>* - a dynamically-allocated array of 256 vectors
// Notes : each index in the encoding table corresponds to an index in the 
//			frequency table
/////////////////////////////////////////////////////////////////////////////
vector<int>* generateEncodingTable(vector<HuffNode*>& leafList){
	vector<int>* vecArray = new vector<int>[256];
	
	for (unsigned int i = 0; i < leafList.size(); ++i){
		HuffNode* parent;
		HuffNode* current;
		parent = leafList[i]->parent;
		current = leafList[i];
		while (parent != NULL){
			if (parent->left == current){
				auto iter = vecArray[leafList[i]->value].begin();
				vecArray[leafList[i]->value].insert(iter, 0);
			}
			else{
				auto iter = vecArray[leafList[i]->value].begin();
				vecArray[leafList[i]->value].insert(iter, 1);
			}
			current = parent;
			parent = parent->parent;
		}
	}
	return vecArray;
}

void RecursiveClear(HuffNode * remov){

	if (remov == NULL){
		return;
	}
	else{
		RecursiveClear(remov->left);
		RecursiveClear(remov->right);
		delete remov;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Function : cleanup
// Notes : clean up any dynamic memory allocated by other functions
/////////////////////////////////////////////////////////////////////////////
void cleanup(unsigned int* freqTable, HuffNode* huffTree, vector<int>* encodingTable){
	RecursiveClear(huffTree);
	huffTree = NULL;

	delete[] freqTable;
	delete[] encodingTable;


}

/////////////////////////////////////////////////////////////////////////////
// Function : writeHuffmanFile
// Parameters : 	inputFilePath - the path of the file to open for input
//			outputFilePath - the path of the file to open for output
//			freqTable - the frequency table
//			encodingTable - the encoding table
// Notes : open the input file, read characters one at a time, while 
//		streaming bitcodes to the output file
/////////////////////////////////////////////////////////////////////////////
void writeHuffmanFile(const char* inputFilePath, const char* outputFilePath,
	unsigned int* freqTable, vector<int>* encodingTable){
	ifstream bin;
	BitOStream bout(outputFilePath, (char*)freqTable, 1028);
	bin.open(inputFilePath);
	if (bin.is_open()){
		while (true){
			//while (!bin.eof()){
			char a ;
			bin.read((char*)&a, 1);
			if (bin.eof())
				break;
			bout << encodingTable[a];
		}
		bout.close();
		bin.close();
	}
	//cleanup(freqTable, NULL, encodingTable);
}

/////////////////////////////////////////////////////////////////////////////
// Function : decodeHuffmanFile
// Parameters :	inputFilePath - the file to open and decode
//			outputFilePath - the decoded mesasge, written to a file
/////////////////////////////////////////////////////////////////////////////
void decodeHuffmanFile(const char* inputFilePath, const char* outputFilePath){
	unsigned int* freqTable = new unsigned int[257];
	BitIStream bin(inputFilePath, (char*)freqTable, 1028);
	ofstream bout(outputFilePath);
	
	vector<HuffNode*> leafList;
	leafList = generateLeafList(freqTable);
	HuffNode* root;
	root = generateHuffmanTree(leafList);
	HuffNode* current = root;
	while (!bin.eof()){
		int a;
		bin >> a;
		if (a)
			current = current->right;
		else
			current = current->left;
		
		if (current->value != -1){
			bout << (char)current->value;
			current = root;
		}
	}

	bout.close();
	bin.close();

	cleanup(freqTable, root, NULL);
}