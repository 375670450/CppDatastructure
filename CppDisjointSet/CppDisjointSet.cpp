#include "CppDisjointSet.h"
#include <string>


int main ( ) {
	string strs[] = { "asd", "zxc", "qwer" };
	DisjointSet<string> Set;
	for ( int i = 0; i < 3; i++ ) Set.Insert (strs[i]);
	Set.Print ( );
	Set.Union (strs[1], strs[2]);
	Set.Print ( );
	system ("pause");
	return 0;
}