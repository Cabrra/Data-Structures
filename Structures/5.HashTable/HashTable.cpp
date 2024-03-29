////////////////////////////////////////////////////////////////////////////////////////////////
// File :			HashTable Test.cpp
// Author :			Rodney Stoeffler
// Created :		06.03.08
// Last Modified :	10.09.10
// Purpose :		Driver Program for the HTable class.
// Notes :			Property of Full Sail University, Data Structures Course.
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// LEAK DETECTION
////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
using namespace std;
#include "HTable.h"			// Include the Hash Table Class header

////////////////////////////////////////////////////////////////////////////////////////////////
// GLOBALS
////////////////////////////////////////////////////////////////////////////////////////////////
const unsigned int NUMHASHBUCKETS = 10;

////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	numHash
// Parameters :	v - the value to hash
// Return :		unsigned int - the hash result for the value specified
////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int numHash(const unsigned int& v)
{
	return v % NUMHASHBUCKETS;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	numHash2
// Parameters :	v - the value to hash
// Return :		unsigned int - the hash result for the value specified
////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int numHash2(const unsigned int& v)
{
	return v % 3;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// Return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
////////////////////////////////////////////////////////////////////////////////////////////////
// LEAK DETECTION
////////////////////////////////////////////////////////////////////////////////////////////////
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// this function call will set a breakpoint at the location of a leaked block
	// set the parameter to the identifier for a leaked block
	//_CrtSetBreakAlloc(166);

	cout << "**********************************************************************\n";
	cout << "**                              Hash Table:                         **\n";
	cout << "**********************************************************************\n\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// Declarations
	////////////////////////////////////////////////////////////////////////////////////////////
	HTable<unsigned int> hTable(NUMHASHBUCKETS, numHash);
	HTable<unsigned int> hTable2(3, numHash2);
	unsigned int testValues[11] = {5, 89, 2, 45, 37, 9000, 20, 73, 99, 1, 24};
	unsigned int reTestValues[14] = {5, 89, 29, 2, 45, 37, 9000, 0, 20, 73, 99, 1, 24, 66};
	unsigned int finalTestValues[11] = {0, 1, 2, 3, 4, 5, 10, 14, 20, 30, 32};
	int i;

	for(i = 0; i < 10; ++i)
		hTable2.insert(i);

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 1 - Constructor, insert, find and clear function tests
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 1 ***\n";
	cout << "Loading Hash Table 1 with values :\n";
	cout << "5 89 2 45 37 9000 20 73 99 1 24\n";
	for (i = 0; i < 11; ++i)
		hTable.insert(testValues[i]);
	cout << "Finding the given values, plus a couple of ones I didn't put in.. :\n";
	cout << "5 89 29 2 45 37 9000 0 20 73 99 1 24 66\n";
	for(i = 0; i < 14; ++i)
		cout << "The value " << reTestValues[i] << " was found in bucket : " << hTable.find(reTestValues[i]) << '\n';
	cout << "Clearing table..\n";
	hTable.clear();

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 2 - findAndRemove function test
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 2 ***\n";
	cout << "Testing insert, remove, and find..\n";	
	for(i = 0; i < 11; ++i)
	{
		hTable.insert(finalTestValues[i]);
		cout << "The value " << finalTestValues[i] << " was found in bucket : " << hTable.find(finalTestValues[i]) << '\n';
	}
	cout << "\nRemoving middle 5 numbers..\n\n";
	hTable.findAndRemove(3);
	hTable.findAndRemove(4);
	hTable.findAndRemove(5);
	hTable.findAndRemove(10);
	hTable.findAndRemove(14);
	hTable.findAndRemove(15);
	hTable2 = hTable;
	for(i = 0; i < 11; ++i)
		cout << "The value " << finalTestValues[i] << " was found in bucket : " << hTable2.find(finalTestValues[i]) << '\n';

	////////////////////////////////////////////////////////////////////////////////////////////
	// Complete
	////////////////////////////////////////////////////////////////////////////////////////////

	system("pause");
	return 0;
}