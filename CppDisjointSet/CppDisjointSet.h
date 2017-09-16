#pragma once

#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int MAXN = 1000;

template <typename Ty>
class DisjointSet {
public:

	DisjointSet ( ){ }

	~DisjointSet ( ){ }
	
	void Insert (Ty item) {
		ID[item] = ID.size();
		Parent.push_back (-1);				// Insert as a new set
	}

	int Find (Ty item) {
		int root = ID[item];
		while ( Parent[root] > 0 ) {
			root = Parent[root];
		}
		int trail = ID[item];
		while ( Parent[trail] > 0 ) {
			int tmp = Parent[trail];
			Parent[trail] = root;
			trail = tmp;
		}
		return root;
	}

	int Find_Recursive (int node) {
		if ( Parent[node] > 0 )
			return Find_Recursive (Parent[node]);
		else
			return node;
	}

	void Union (Ty s1, Ty s2) {								// Union By Size
		int root1 = Find (s1), root2 = Find (s2);
		if ( Parent[root1] < Parent[root2] ){		// s1 has more items than s2
			Parent[root1] += Parent[root2];
			Parent[root2] = root1;
		} else {
			Parent[root2] += Parent[root1];
			Parent[root1] = root2;
		}
		return;
	}

	bool isConnected (Ty s1, Ty s2)  {
		return Find (s1) == Find (s2);
	}

	void Clear ( ) {
		Parent.clear ( );
		ID.clear ( );
	}

	void Print ( ) const{
		for each ( auto i in Parent ) {
			cout << i << " ";
		}
		cout << endl;
	}

	static bool isPrime (int n) {
		int m = sqrt (n);
		if ( n < 2 || n> 2 && !( n & 1 ) ) return false;
		for ( int i = 2; i <= m; i++ ) 
			if ( n % i == 0 ) return false;
		return true;
	}

	static int NextPrime (int n) {
		if ( n <= 2 ) return 2;
		if ( !( n & 1 ) ) n++;
		while ( !isPrime (n) ) n += 2;
		return n;
	}
	
private:

	vector<int> Parent;						// if Root is a root node, then Parent[Root] = -size
	map<Ty, int> ID;								// Parent[ID] is nagative -> root;

};
