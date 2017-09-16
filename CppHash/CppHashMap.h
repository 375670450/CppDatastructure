#pragma once
#include <functional>
#include <vector>
#include <list>

#define INITIALSIZE  (1<<8);
#define MAXFACTOR  0.75;		//	static member cannot be initialized in a declaration.


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//												HashTable													//				
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

template<typename T, typename HashFunc = std::hash<T> >
class HashTable {
private:

	
	struct Node {
		bool isUsed;
		T data;
	};

	const unsigned double MaxLoadFactor = MAXFACTOR;		//	static member cannot be initialized in a declaration.
	unsigned int TableSize;
	unsigned int Count;
	std::vector< Node > Table;

	int Hash (T key) {
		HashFunc getHash;
		return getHash (key) % TableSize;
	}

	void Resize ( ) {
		try {
			TableSize <<= 1;
			vector<Node> oldtbl = Table;
			Table.clear ( );
			Count = 0;
			Table.resize (TableSize);
			for ( int i = 0; i < oldtbl.size(); i++ ) {
				if( oldtbl[i].isUsed )	Insert (oldtbl[i].data);
			}
		} catch ( const std::exception& e ) {
			cout <<"Cannot Extend : " << e.what ( ) << endl;
		}
	}

	int FindPos (const T & key) {			// If key not exists , return -1
		int pos = Hash(key);
		while ( Table[pos].isUsed && Table[pos].data != key ) {
			pos = ProbeNext(pos);
		}
		if ( !Table[pos].isUsed ) {
			return -1;
		} else {
			return pos;
		}
	}

	int LinerProbe (int pos) {		// Probe method
		return pos + 1;
	}

public:

	HashTable (int InitialSize) {
		TableSize = InitialSize;
		Table.resize (TableSize);
		Count = 0;
		//InitialSize = 0;
	}

	bool Insert (const T & key) {			// If the key has existed, return false; else return true
		int pos = Hash (key);
		while ( Table[pos].isUsed && Table[pos].data != key ) {
			pos = LinerProbe (pos);
		}
		if ( Table[pos].data == key ) {
			return false;
		} else {
			Table[pos].isUsed = true;
			Table[pos].data = key;
			Count++;
			if ( Count > MaxLoadFactor * TableSize ) {
				Resize ( );
			}
			return true;
		}
	}
	
	bool Delete (const T & key) {			// If key not exists, return false; else delete it and return true
		int pos = FindPos(key);
		if ( pos == -1 ) {
			return -1;
		} else {
			int next = ProbeNext(pos);
			while ( Table[next].isUsed ) {
				Table[pos] = Table[next];
				pos = next;
				next = ProbeNext (pos);
			}
			Table[pos].isUsed = false;
			Count--;
		}
	}

	int Size ( ) {
		return Count;
	}

	void Print ( ) {
		for ( int i = 0; i < Table.size ( ); i++ ) {
			if ( Table[i].isUsed ) {
				cout << i << " " << Table[i].data << endl;
			}
		}
	}

	~HashTable ( ) { Table.clear ( ); }
};






//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//											HashMap															//				
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType> >
class HashMap {
	/*
	Use Separate Chaining to solve collisions
	*/

private:

	typedef std::pair<KeyType, ValueType> Pair;
	typedef std::list<Pair> NodeList;
	std::vector< NodeList > Table;

	unsigned double MaxLoadFactor;		//	static member cannot be initialized in a declaration.
	unsigned int TableSize;
	unsigned int Count;

	int Hash (KeyType key) {
		HashFunc getHash;
		return getHash (key) % TableSize;
	}

	void Resize ( ) {
		try {
			TableSize <<= 1;
			vector<NodeList> oldtbl = Table;
			Initial (TableSize);
			for ( int i = 0; i < oldtbl.size ( ); i++ ) {
				for ( auto it = oldtbl[i].begin ( ); it != oldtbl[i].end ( ); it++ ) {
					Insert (*it);
				}
			}
		} catch ( const std::exception& e ) {
			cout << "Cannot Extend Table : " << e.what ( ) << endl;
		}
	}

	int FindPos (const Pair & elem) {			// If key not exists , return -1
		int pos = Hash (elem.first);
		for ( auto it = Table[pos].begin ( ); it != Table[pos].end ( ); it++ ) {
			if ( it->second == elem.second ) return pos;
		}
		return -1;
	}

	void Initial (int Size) {
		TableSize = Size;
		Table.resize (TableSize);
		Count = 0;
	}

public:

	HashMap ( ) {
		MaxLoadFactor = MAXFACTOR;
		Initial (TableSize);
	}

	bool Insert (const Pair & elem) {			// If the key has existed, return false; else return true
		Table[Hash (elem.first)].push_back (elem);
		Count++;
		if ( Count > MaxLoadFactor * TableSize ) {
			Resize ( );
		}
		return true;
	}

	bool Delete (const Pair & elem) {			// If key not exists, return false; else delete it and return true
		int pos = Hash (elem.first);
		for ( auto it = Table[pos].begin(); it < Table[pos].end(); it++ ) {
			if ( it->second == elem.second ) {
				Table.erase (it);
				break;
			}
		}
	}

	int Size ( ) {
		return Count;
	}

	void Print ( ) {
		for ( int i = 0; i < Table.size(); i++ ) {
			if ( !Table[i].empty ( ) ) {
				cout << i << " : ";
				for ( auto it = Table[i].begin ( ); it != Table[i].end ( ); it++ ) {
					cout << it->first << "-" << it->second << " ";
				}
				cout << endl;
			}
		}
	}

	~HashMap ( ) { Table.clear ( ); }
};


