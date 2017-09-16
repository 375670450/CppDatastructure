#include "CppHashMap.h"
#include <iostream>


using namespace std;

int main ( ) {
	vector<int> arr = { 1, 13, 12, 21, 33, 34, 38, 27, 22, 32 };
	HashTable<int> H(arr.size());
	for ( size_t i = 0; i < arr.size()-1; i++ ) {
		H.Insert (arr[i]);
	}
	H.Print ( );
	system ("pause");
	return 0;
}